/*
 * Tencent is pleased to support the open source community by making Blueking Container Service available.
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "watch.h"
#include "../../third-party/base64/base64.h"
#include "../error_code.h"

#define KEEP_ALIVE_INTERVALS_SEC 1
#define HEART_BEAT_INTERVALS_SEC 15
#define MAX_RETRY_COUNT 20

namespace bscp {

int Watcher::Subscribe(Callback callback, const std::string& app, AppOptions& opts)
{
    // NOTE: lack of de-duplication.
    if (opts.m_uid.empty())
    {
        opts.m_uid = m_options.m_fingerPrint;
    }

    auto subscriber = std::make_shared<Subscriber>();

    subscriber->m_app = app;
    subscriber->m_option = opts;
    subscriber->m_uid = opts.m_uid;
    subscriber->m_callback = callback;
    subscriber->m_currentReleaseID = 0;

    // merge labels, if key conflict, app value will overwrite client value.
    subscriber->m_labels = m_options.m_labels;
    for (const auto& iter : opts.m_labels)
    {
        subscriber->m_labels[iter.first] = iter.second;
    }

    m_subscribers.push_back(subscriber);

    return BSCP_CPP_SDK_OK;
}

int Watcher::StartWatch()
{
    // check the watch thread is associate with an active execution.
    if (m_watchThread.joinable() || m_keepAliveThread.joinable())
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to start watch multiple times without call stop watch.");
        return BSCP_CPP_SDK_START_WATCH_ERROR;
    }

    // building pbfs::SideWatchMeta request information need payload bytes.
    sfs::SideWatchPayload payload;

    for (const auto& iter : m_subscribers)
    {
        sfs::SideAppMeta app;

        app.m_app = iter->m_app;
        app.m_uid = iter->m_uid;
        app.m_labels = iter->m_labels;
        app.m_currentReleaseID = iter->m_currentReleaseID;
        app.m_currentCursorID = 0;

        payload.m_applications.push_back(app);
    }

    payload.m_bizID = m_options.m_bizID;

    // base64
    auto ret = payload.Marshal(m_payload);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to marshal payload. err-code(%d)", ret);
        return ret;
    }

    // call rpc function.
    auto req = std::make_shared<pbfs::SideWatchMeta>();

    // req api version.
    req->mutable_api_version()->set_major(BSCP_CPP_SDK_CURRENT_MAJOR_VERSION);
    req->mutable_api_version()->set_minor(BSCP_CPP_SDK_CURRENT_MINOR_VERSION);
    req->mutable_api_version()->set_patch(BSCP_CPP_SDK_CURRENT_PATCH_VERSION);

    // req payload.
    req->set_payload(m_payload);

    // context.
    m_clientContext = std::make_shared<grpc::ClientContext>();
    ret = SetContext(m_clientContext, m_options);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return ret;
    }

    ret = m_upstream->Watch(m_clientContext, req, m_reader);
    if (ret || GRPC_CHANNEL_READY != m_channel->GetState(true))
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to call grpc watch. err-code(%d)", ret);
        return ret;
    }

    // multi thread handle the return stream buffer, need to reconnect the channel.
    m_watchFlag = true;
    m_watchThread = std::thread(&Watcher::WatchFunc, this);

    m_keepAliveFlag = true;
    m_keepAliveThread = std::thread(&Watcher::KeepAliveFunc, this);

    return BSCP_CPP_SDK_OK;
}

int Watcher::StopWatch()
{
    // close the watch stream.
    m_watchFlag = false;
    m_keepAliveFlag = false;

    if (nullptr == m_reader)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "m_reader stream is nullptr.");
        return BSCP_CPP_SDK_OK;
    }

    m_clientContext->TryCancel();

    m_watchThread.join();
    m_keepAliveThread.join();

    // m_subscribers.clear();

    return BSCP_CPP_SDK_OK;
}

void Watcher::WatchFunc()
{
    while (m_watchFlag)
    {
        // try to read stream from reader in loop.
        pbfs::FeedWatchMessage feedWatchMessage;

        if (!m_channelAliveFlag || GRPC_CHANNEL_READY != m_channel->GetState(true))
        {
            // sleep 50ms;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        while (m_channelAliveFlag && m_reader->Read(&feedWatchMessage))
        {
            // prase the reader message.
            if (!IsApiVersionMatch(feedWatchMessage.api_version()))
            {
                LOG_WARN(m_options.m_feedAddrs[0], "api version is not matched.");
                // do nothing.
                break;
            }

            // find the match function to the message.
            // judge the type.
            int feedMessageType = feedWatchMessage.type();

            switch (feedMessageType)
            {
            case FEED_MESSAGE_TYPE_BOUNCE:
            {
                // send reconnect signal.
                LOG_INFO(m_options.m_feedAddrs[0], "receive a bounce signal from feed server.");
                m_reconnectSignal = true;
                m_channelAliveFlag = false;
            }
            break;

            case FEED_MESSAGE_TYPE_PUBLISH_RELEASE:
            {
                LOG_INFO(m_options.m_feedAddrs[0], "receive a release change signal from feed server.");
                sfs::ReleaseChangeEvent releaseChangeEvent;
                releaseChangeEvent.m_payload = feedWatchMessage.payload();
                releaseChangeEvent.m_rid = feedWatchMessage.rid();
                releaseChangeEvent.m_apiVersion = feedWatchMessage.api_version();

                // cache.
                // TODO: next version add.

                // run the callback function to handle the stream message.
                auto ret = OnReleaseChange(releaseChangeEvent);
                if (ret)
                {
                    LOG_ERROR(m_options.m_feedAddrs[0], "failed to call on release change. err-code(%d)", ret);
                }
            }
            break;

            default:
            {
                LOG_ERROR(m_options.m_feedAddrs[0], "receive an unknown signal");
            }
            break;
            }
        }
    }
}

bool Watcher::IsApiVersionMatch(const pbbase::Versioning& apiVersion)
{
    if (apiVersion.major() < BSCP_CPP_SDK_LEAST_MAJOR_VERSION)
    {
        return false;
    }

    if (apiVersion.major() == BSCP_CPP_SDK_LEAST_MAJOR_VERSION)
    {
        if (apiVersion.minor() < BSCP_CPP_SDK_LEAST_MINOR_VERSION)
        {
            return false;
        }

        if (apiVersion.minor() == BSCP_CPP_SDK_LEAST_MINOR_VERSION)
        {
            if (apiVersion.patch() < BSCP_CPP_SDK_LEAST_PATCH_VERSION)
            {
                return false;
            }
        }

        return true;
    }

    return true;
}

int Watcher::OnReleaseChange(const sfs::ReleaseChangeEvent& event)
{
    sfs::ReleaseChangePayload payload;

    auto ret = payload.Unmarshal(event.m_payload);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "fail to unmarshal payload. err-code(%d)", ret);
        return ret;
    }

    for (const auto& subscriber : m_subscribers)
    {
        if (subscriber->m_app != payload.m_instance.m_app || subscriber->m_uid != payload.m_instance.m_uid ||
            subscriber->m_labels != payload.m_instance.m_labels ||
            subscriber->m_currentReleaseID == payload.m_releaseMeta.m_releaseID)
        {
            continue;
        }

        LOG_INFO(m_options.m_feedAddrs[0], "subscriber matched.");

        // run callback function.
        subscriber->m_currentReleaseID = payload.m_releaseMeta.m_releaseID;

        // subscriber reset config items.
        Release release;
        release.m_releaseID = payload.m_releaseMeta.m_releaseID;
        release.m_kvItems = payload.m_releaseMeta.m_kvMetas;
        release.m_preHook = payload.m_releaseMeta.m_preHook;
        release.m_postHook = payload.m_releaseMeta.m_postHook;

        std::map<std::string, uint32_t> configItems;

        for (const auto& ci : payload.m_releaseMeta.m_ciMetas)
        {
            configItems[ci.m_configItemSpec.name()] = ci.m_commitID;

            ConfigItemFile configItemFile;
            configItemFile.m_fileData = ci;
            configItemFile.m_permission = ci.m_configItemSpec.permission();
            configItemFile.m_name = ci.m_configItemSpec.name();
            configItemFile.m_path = ci.m_configItemSpec.path();

            release.m_fileItems.push_back(configItemFile);
        }

        subscriber->m_currentConfigItems = configItems;

        auto ret = subscriber->m_callback(release);
        if (ret)
        {
            LOG_WARN(m_options.m_feedAddrs[0], "failed to call user watch callback function. err-code(%d)", ret);
            return BSCP_CPP_SDK_CALLBACK_ERROR;
        }

        LOG_INFO(m_options.m_feedAddrs[0], "success to call user callback function.");
    }

    return BSCP_CPP_SDK_OK;
}

int Watcher::Reconnect()
{
    // call rpc function.
    auto req = std::make_shared<pbfs::SideWatchMeta>();

    // req api version.
    req->mutable_api_version()->set_major(BSCP_CPP_SDK_CURRENT_MAJOR_VERSION);
    req->mutable_api_version()->set_minor(BSCP_CPP_SDK_CURRENT_MINOR_VERSION);
    req->mutable_api_version()->set_patch(BSCP_CPP_SDK_CURRENT_PATCH_VERSION);

    // req payload.
    req->set_payload(m_payload);

    // context.
    m_clientContext = std::make_shared<grpc::ClientContext>();
    auto ret = SetContext(m_clientContext, m_options);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return BSCP_CPP_SDK_RECONNECT_ERROR;
    }

    ret = m_upstream->Watch(m_clientContext, req, m_reader);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to call grpc watch. err-code(%d)", ret);
        return BSCP_CPP_SDK_RECONNECT_ERROR;
    }
    return BSCP_CPP_SDK_OK;
}

int Watcher::Heartbeat()
{
    // call rpc message.
    auto req = std::make_shared<pbfs::MessagingMeta>();

    // req api version.
    req->mutable_api_version()->set_major(BSCP_CPP_SDK_CURRENT_MAJOR_VERSION);
    req->mutable_api_version()->set_minor(BSCP_CPP_SDK_CURRENT_MINOR_VERSION);
    req->mutable_api_version()->set_patch(BSCP_CPP_SDK_CURRENT_PATCH_VERSION);

    // req payload.
    req->set_payload(m_payload);

    // req type.
    req->set_type(2);

    // req rid.
    req->set_rid(m_options.m_sideRid);

    // context.
    auto context = std::make_shared<grpc::ClientContext>();
    auto ret = SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return ret;
    }

    // resp.
    auto resp = std::make_shared<pbfs::MessagingResp>();
    ret = m_upstream->Messaging(context, req, resp);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to call grpc messaging. err-code(%d)", ret);
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

void Watcher::KeepAliveFunc()
{
    int count = 0;

    // NOTE: when the grpc channel is disconnect, record the retry count.
    uint64_t retryCount = 0;

    while (m_keepAliveFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(KEEP_ALIVE_INTERVALS_SEC));
        ++count;

        // proactive test and reconnect signal.
        if (GRPC_CHANNEL_READY != m_channel->GetState(true) || m_reconnectSignal)
        {
            m_channelAliveFlag = false;
            retryCount = 0;

            // wait grpc channel reconnect itself.
            while (++retryCount < MAX_RETRY_COUNT && GRPC_CHANNEL_READY != m_channel->GetState(true))
            {
                // NOTE: when the channel is disconnect, the programme will stay here indefinitely, need to jump out
                // after a certain number of tries.
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            // reconnect.
            while (++retryCount < MAX_RETRY_COUNT && BSCP_CPP_SDK_OK != Reconnect())
            {
                // time count.
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            if (retryCount >= MAX_RETRY_COUNT)
            {
                // jump out.
                LOG_ERROR("", "service anomaly, the number of reconnection has reached the limit.");
                continue;
            }

            // reset reconnect signal.
            m_reconnectSignal = false;

            m_channelAliveFlag = true;

            continue;
        }

        // check heart beat signal to reconnect
        if (count * KEEP_ALIVE_INTERVALS_SEC >= HEART_BEAT_INTERVALS_SEC)
        {
            // reset count.
            count = 0;

            // heartbeat.
            auto ret = Heartbeat();
            if (ret)
            {
                // TODO: add rules to reconnect channel.
            }
        }
    }
}

} // namespace bscp
