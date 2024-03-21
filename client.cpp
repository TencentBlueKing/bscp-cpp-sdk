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

#include "client.h"

#include "internal/error_code.h"
#include "pkg/protocol/feed-server/feed_server.pb.h"

#ifdef __linux__
#include <unistd.h>
#endif

// keep alive thread.
#define KEEP_ALIVE_INTERVALS_SEC 1
#define HEART_BEAT_INTERVALS_SEC 10
#define MAX_RETRY_COUNT 3
#define MAX_HEARTBEAT_FAIL_COUNT 3

// watch thread.
#define WATCH_INTERVALS_MILLI_SEC 50

// cache.
#define CACHE_MAX_SIZE 64
#define CACHE_ELASTICITY 0

// feed message type.
#define FEED_MESSAGE_TYPE_BOUNCE 1
#define FEED_MESSAGE_TYPE_PUBLISH_RELEASE 2

namespace bscp {

Client::~Client()
{
    // close keep alive thread.
    m_keepAliveFlag = false;

    if (m_keepAliveThread.joinable())
    {
        m_keepAliveThread.join();
    }

    // close watch thread.
    m_watchFlag = false;

    if (m_watchThread.joinable())
    {
        m_watchThread.join();
    }
}

int Client::PullKvs(const std::string& app, std::vector<std::string>& match, const core::AppOptions& opts, Release& release)
{
    if (!m_initialFlag)
    {
        LOG_ERROR("client has not been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    if (!m_upstream)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // build req.
    auto req = std::make_shared<pbfs::PullKvMetaReq>();

    // biz_id.
    req->set_biz_id(m_options.m_bizID);

    // match.
    req->mutable_match()->CopyFrom({match.begin(), match.end()});

    // app_meta app.
    req->mutable_app_meta()->set_app(app);

    // app_meta uid.
    req->mutable_app_meta()->set_uid(m_options.m_uid);

    // app_meta labels.
    for (const auto& iter : m_options.m_labels)
    {
        req->mutable_app_meta()->mutable_labels()->insert({iter.first, iter.second});
    }

    // merge labels, if key conflict, app value will overwrite client value.
    for (const auto& iter : opts.m_labels)
    {
        (*req->mutable_app_meta()->mutable_labels())[iter.first] = iter.second;
    }

    // if opts.m_uid not null, assign value to req.
    if (!opts.m_uid.empty())
    {
        req->mutable_app_meta()->set_uid(opts.m_uid);
    }

    // context.
    auto context = std::make_shared<grpc::ClientContext>();
    auto ret = core::SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR("failed to set grpc client context. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    // resp.
    auto resp = std::make_shared<pbfs::PullKvMetaResp>();

    ret = m_upstream->PullKvMeta(context, req, resp);
    if (ret)
    {
        LOG_ERROR("failed to pull kv meta. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    // fill release.
    release.m_releaseID = resp->release_id();
    for (const auto& kv : resp->kv_metas())
    {
        sfs::KvMetaV1 kvItem;
        kvItem.m_key = kv.key();
        kvItem.m_kvType = kv.kv_type();
        kvItem.m_revision = kv.revision();
        kvItem.m_kvAttachment = kv.kv_attachment();

        release.m_kvItems.push_back(kvItem);
    }

    return BSCP_CPP_SDK_OK;
}

int Client::Get(const std::string& app, const std::string& key, const core::AppOptions& opts, std::string& value)
{
    if (!m_initialFlag)
    {
        LOG_ERROR("client has not been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    if (!m_upstream)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // build req.
    auto req = std::make_shared<pbfs::GetKvValueReq>();

    // biz_id.
    req->set_biz_id(m_options.m_bizID);

    // key.
    req->set_key(key);

    // app_meta app.
    req->mutable_app_meta()->set_app(app);

    // app_meta uid.
    req->mutable_app_meta()->set_uid(m_options.m_uid);

    // app_meta labels.
    for (const auto& iter : m_options.m_labels)
    {
        req->mutable_app_meta()->mutable_labels()->insert({iter.first, iter.second});
    }

    // merge labels, if key conflict, app value will overwrite client value.
    for (const auto& iter : opts.m_labels)
    {
        (*req->mutable_app_meta()->mutable_labels())[iter.first] = iter.second;
    }

    // if opts.m_uid not null, assign value to req.
    if (!opts.m_uid.empty())
    {
        req->mutable_app_meta()->set_uid(opts.m_uid);
    }

    // context.
    auto context = std::make_shared<grpc::ClientContext>();
    auto ret = core::SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR("failed to set grpc client context. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    // resp.
    auto resp = std::make_shared<pbfs::GetKvValueResp>();

    ret = m_upstream->GetKvValue(context, req, resp);
    if (ret)
    {
        LOG_ERROR("failed to get kv value. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    // fill value;
    value = resp->value();

    return BSCP_CPP_SDK_OK;
}

int Client::AddWatcher(const std::string& app, Callback callback, core::AppOptions& opts)
{
    if (!m_initialFlag)
    {
        LOG_ERROR("client has not been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

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

int Client::StartWatch()
{
    if (!m_initialFlag)
    {
        LOG_ERROR("client has not been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    if (!m_upstream)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // check the watch thread is associate with an active execution.
    if (m_watchThread.joinable())
    {
        LOG_ERROR("failed to start watch multiple times without call stop watch. upstream(%s)", m_loadBalancer->Get().c_str());
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
        LOG_ERROR("failed to marshal payload. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
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
    m_readerContext = std::make_shared<grpc::ClientContext>();
    ret = core::SetContext(m_readerContext, m_options);
    if (ret)
    {
        LOG_ERROR("failed to set grpc client context. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    ret = m_upstream->Watch(m_readerContext, req, m_reader);
    if (nullptr == m_reader || ret)
    {
        LOG_ERROR("failed to call grpc watch. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return BSCP_CPP_SDK_WATCH_ERROR;
    }

    // multi thread handle the return stream buffer, need to reconnect the channel.
    m_watchFlag = true;
    m_watchThread = std::thread(&Client::WatchFunc, this);

    return BSCP_CPP_SDK_OK;
}

int Client::StopWatch()
{
    if (!m_initialFlag)
    {
        LOG_ERROR("client has not been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    // close the watch stream.
    m_watchFlag = false;

    // close reader, the purpose of this call is let watch thread jump out of the read blocking.
    if (nullptr != m_readerContext)
    {
        m_readerContext->TryCancel();
    }

    if (m_watchThread.joinable())
    {
        m_watchThread.join();
    }
    m_payload.clear();

    return BSCP_CPP_SDK_OK;
}

int Client::Initialize()
{
    if (m_initialFlag)
    {
        LOG_WARN("client has been initialized");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    if (m_options.m_feedAddrs.empty())
    {
        LOG_ERROR("feed server address is empty");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    // initialize load balancer.
    m_loadBalancer = std::make_shared<lb::LoadBalancer>(lb::LoadStrategy::RR, m_options.m_feedAddrs);
    if (m_loadBalancer->Initialize())
    {
        LOG_ERROR("failed to initialize load balancer");
    }
    LOG_INFO("success to initialize load balancer. upstream(%s)", m_loadBalancer->Get().c_str());

    if (m_options.m_fingerPrint.empty())
    {
        auto ret = bscp::tools::GetMachineID(m_options.m_fingerPrint);
        if (ret)
        {
            LOG_ERROR("failed to get machine id");
            return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
        }
    }

    // create channel.
    m_channel = grpc::CreateChannel(m_loadBalancer->Get(), grpc::InsecureChannelCredentials());

    // initialize upstream.
    m_upstream = std::make_shared<core::Upstream>(m_channel);
    LOG_INFO("success to initialize upstream(%s)", m_loadBalancer->Get().c_str());

    // initialize cache.
    m_cache = std::make_shared<lru11::Cache<std::string, std::string>>(CACHE_MAX_SIZE, CACHE_ELASTICITY);
    LOG_INFO("success to initialize cache. upstream(%s)", m_loadBalancer->Get().c_str());

    // NOTE: now use handshake api as heartbeat.
    auto ret = Heartbeat();
    if (ret)
    {
        LOG_ERROR("failed to initialize bscp client");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }
    LOG_INFO("success to call handshake. upstream(%s)", m_loadBalancer->Get().c_str());

    // start keep alive thread.
    m_keepAliveFlag = true;
    m_keepAliveThread = std::thread(&Client::KeepAliveFunc, this);

    // set initial flag;
    m_initialFlag = true;

    LOG_INFO("success to initialize bscp client. upstream(%s)", m_loadBalancer->Get().c_str());

    return BSCP_CPP_SDK_OK;
}

void Client::WatchFunc()
{
    while (m_watchFlag)
    {
        // sleep to avoid cpu idling.
        ::usleep(WATCH_INTERVALS_MILLI_SEC * 1000);

        pbfs::FeedWatchMessage feedWatchMessage;

        // reconnect signal from bscp server, reader stream exception, m_reader ptr is invalid.
        while (!m_reconnectSignal && m_readerValidFlag && m_reader)
        {
            // if there is no data, this call will block here unless an exception occurs or receive data.
            auto ret = m_reader->Read(&feedWatchMessage);
            if (!ret)
            {
                // failed to call read, the reason may as follow:
                // 1. bscp server close proactively.
                // 2. bscp server anomaly.
                // 3. grpc client context time out.
                LOG_ERROR("failed to read the watch stream. upstream(%s)", m_loadBalancer->Get().c_str());
                m_readerValidFlag = false;

                break;
            }

            // handle the receive data.
            if (!IsApiVersionMatch(feedWatchMessage.api_version()))
            {
                LOG_WARN("api version is not matched. upstream(%s)", m_loadBalancer->Get().c_str());
                continue;
            }

            int feedMessageType = feedWatchMessage.type();

            switch (feedMessageType)
            {
            case FEED_MESSAGE_TYPE_BOUNCE:
            {
                // send reconnect signal.
                LOG_INFO("receive a bounce signal from feed server. upstream(%s)", m_loadBalancer->Get().c_str());
                m_reconnectSignal = true;
            }
            break;

            case FEED_MESSAGE_TYPE_PUBLISH_RELEASE:
            {
                LOG_INFO("receive a release change signal from feed server. upstream(%s)", m_loadBalancer->Get().c_str());
                sfs::ReleaseChangeEvent releaseChangeEvent;
                releaseChangeEvent.m_payload = feedWatchMessage.payload();
                releaseChangeEvent.m_rid = feedWatchMessage.rid();
                releaseChangeEvent.m_apiVersion = feedWatchMessage.api_version();

                // run the callback function to handle the stream message.
                auto ret = OnReleaseChange(releaseChangeEvent);
                if (ret)
                {
                    LOG_ERROR("failed to call on release change. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
                }
            }
            break;

            default:
            {
                LOG_ERROR("receive an unknown signal. upstream(%s)", m_loadBalancer->Get().c_str());
            }
            break;
            }
        }
    }
}

bool Client::IsApiVersionMatch(const pbbase::Versioning& apiVersion)
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

int Client::OnReleaseChange(const sfs::ReleaseChangeEvent& event)
{
    sfs::ReleaseChangePayload payload;

    auto ret = payload.Unmarshal(event.m_payload);
    if (ret)
    {
        LOG_ERROR("fail to unmarshal payload. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    for (const auto& subscriber : m_subscribers)
    {
        if (subscriber->m_app != payload.m_instance.m_app || subscriber->m_uid != payload.m_instance.m_uid ||
            subscriber->m_labels != payload.m_instance.m_labels || subscriber->m_currentReleaseID == payload.m_releaseMeta.m_releaseID)
        {
            continue;
        }

        LOG_INFO("subscriber matched. upstream(%s)", m_loadBalancer->Get().c_str());

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
            LOG_ERROR("failed to call user watch callback function. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
            return BSCP_CPP_SDK_CALLBACK_ERROR;
        }

        LOG_INFO("success to call user callback function. upstream(%s)", m_loadBalancer->Get().c_str());
    }

    return BSCP_CPP_SDK_OK;
}

int Client::Reconnect()
{
    auto ret = m_loadBalancer->Update();
    if (ret)
    {
        LOG_ERROR("failed to update upstream address. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    // create channel and upstream.
    auto channel = grpc::CreateChannel(m_loadBalancer->Get(), grpc::InsecureChannelCredentials());
    auto upstream = std::make_shared<core::Upstream>(channel);

    // call rpc function.
    auto req = std::make_shared<pbfs::SideWatchMeta>();

    // req api version.
    req->mutable_api_version()->set_major(BSCP_CPP_SDK_CURRENT_MAJOR_VERSION);
    req->mutable_api_version()->set_minor(BSCP_CPP_SDK_CURRENT_MINOR_VERSION);
    req->mutable_api_version()->set_patch(BSCP_CPP_SDK_CURRENT_PATCH_VERSION);

    // req payload.
    req->set_payload(m_payload);

    // context.
    auto context = std::make_shared<grpc::ClientContext>();
    ret = core::SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR("failed to set grpc client context. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return BSCP_CPP_SDK_RECONNECT_ERROR;
    }

    std::unique_ptr<grpc::ClientReader<pbfs::FeedWatchMessage>> reader;
    ret = upstream->Watch(context, req, reader);
    if (nullptr == reader || ret)
    {
        LOG_ERROR("failed to reconnect. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return BSCP_CPP_SDK_WATCH_ERROR;
    }

    // update channel upstream reader.
    m_channel = channel;
    m_upstream = upstream;
    m_readerContext = context;
    m_reader = std::move(reader);

    // call heartbeat because watch api return can not sure whether server is available.
    ret = Heartbeat();
    if (ret)
    {
        LOG_ERROR("failed to reconnect. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return BSCP_CPP_SDK_RECONNECT_ERROR;
    }

    LOG_INFO("success to reconnect to bscp server. upstream(%s)", m_loadBalancer->Get().c_str());

    return BSCP_CPP_SDK_OK;
}

int Client::Heartbeat()
{
    if (!m_upstream)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // call handshake rpc.
    auto hsMsg = std::make_shared<pbfs::HandshakeMessage>();

    pbbase::Versioning apiVersion;

    apiVersion.set_major(BSCP_CPP_SDK_CURRENT_MAJOR_VERSION);
    apiVersion.set_minor(BSCP_CPP_SDK_CURRENT_MINOR_VERSION);
    apiVersion.set_patch(BSCP_CPP_SDK_CURRENT_PATCH_VERSION);

    hsMsg->mutable_api_version()->CopyFrom(apiVersion);

    pbfs::SidecarSpec sidecarSpec;

    sidecarSpec.set_biz_id(m_options.m_bizID);
    sidecarSpec.mutable_version()->CopyFrom(apiVersion);

    hsMsg->mutable_spec()->CopyFrom(sidecarSpec);

    // rep.
    auto hsRep = std::make_shared<pbfs::HandshakeResp>();

    // context.
    auto context = std::make_shared<grpc::ClientContext>();
    auto ret = core::SetContext(context, m_options, true);
    if (ret)
    {
        LOG_ERROR("failed to set grpc client context. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    ret = m_upstream->Handshake(context, hsMsg, hsRep);
    if (ret)
    {
        LOG_ERROR("failed to call grpc handshake. err-code(%d), upstream(%s)", ret, m_loadBalancer->Get().c_str());
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

void Client::KeepAliveFunc()
{
    // NOTE: when the grpc channel is disconnect, record the retry count.
    uint16_t retryTimes = 0;
    uint16_t heartbeatFailTimes = 0;

    // keep the channel and relevant resources available.
    while (m_keepAliveFlag)
    {
        ::sleep(KEEP_ALIVE_INTERVALS_SEC);

        // the responsibilities of this thread are as follows:
        // 1. handle the reconnect and reader stream invalid signal from watch thread.
        // 2. send a heartbeat to server in order to keep channel alive.

        // handle the reconnect and reader stream invalid signal.
        if ((m_watchFlag && (m_reconnectSignal || !m_readerValidFlag)) || heartbeatFailTimes >= MAX_HEARTBEAT_FAIL_COUNT)
        {
            LOG_INFO("start reconnection, try to reconnect up to %d times. upstream(%s)", MAX_RETRY_COUNT, m_loadBalancer->Get().c_str());

            while (retryTimes < MAX_RETRY_COUNT && BSCP_CPP_SDK_OK != Reconnect())
            {
                ::sleep(1 << retryTimes);
                ++retryTimes;
            }

            if (retryTimes >= MAX_RETRY_COUNT)
            {
                LOG_ERROR("service anomaly, the number of reconnection has reached the limit");
                retryTimes = 0;
                continue;
            }

            // success to reconnect in here.
            if (m_watchFlag)
            {
                m_reconnectSignal = false;
                m_readerValidFlag = true;
            }

            heartbeatFailTimes = 0;
            retryTimes = 0;
            continue;
        }

        // send a heartbeat to server in order to keep channel alive.
        auto durationMS = static_cast<uint64_t>(
                              std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) -
                          m_lastHeartbeatTimeMS;

        if (durationMS >= (HEART_BEAT_INTERVALS_SEC * 1000))
        {
            LOG_INFO("send a heartbeat signal. upstream(%s)", m_loadBalancer->Get().c_str());
            // record heart beat time.
            m_lastHeartbeatTimeMS = static_cast<uint64_t>(
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());

            // heartbeat.
            auto ret = Heartbeat();
            if (ret)
            {
                if (++heartbeatFailTimes >= MAX_HEARTBEAT_FAIL_COUNT)
                {
                    LOG_ERROR("the service has been abnormal for more than %ds, heartbeat fail times(%d)",
                              (heartbeatFailTimes - 1) * HEART_BEAT_INTERVALS_SEC, heartbeatFailTimes);
                }
                continue;
            }
            else
            {
                // heartbeat success, reset heartbeat fail count.
                heartbeatFailTimes = 0;
                continue;
            }
        }
    }
}

} // namespace bscp