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

// grpc.
#include <grpcpp/grpcpp.h>

namespace bscp {

int Client::PullKvs(const std::string& app, std::vector<std::string>& match, const AppOptions& opts, Release& release)
{
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
    auto ret = SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return ret;
    }

    // resp.
    auto resp = std::make_shared<pbfs::PullKvMetaResp>();
    ret = m_upstream->PullKvMeta(context, req, resp);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to pull kv meta. err-code(%d)", ret);
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

int Client::Get(const std::string& app, const std::string& key, const AppOptions& opts, std::string& res)
{
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
    auto ret = SetContext(context, m_options);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return ret;
    }

    // resp.
    auto resp = std::make_shared<pbfs::GetKvValueResp>();
    ret = m_upstream->GetKvValue(context, req, resp);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to get kv value. err-code(%d)", ret);
        return ret;
    }

    // fill res;
    res = resp->value();

    return BSCP_CPP_SDK_OK;
}

int Client::AddWatcher(Callback callback, const std::string& app, AppOptions& opts)
{
    auto ret = m_watcher->Subscribe(callback, app, opts);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to add watcher. app(%s), err-code(%d)", app.c_str(), ret);
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

int Client::StartWatch()
{
    auto ret = m_watcher->StartWatch();
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to start watch. err-code(%d)", ret);
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

int Client::StopWatch()
{
    auto ret = m_watcher->StopWatch();
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to stop watch. err-code(%d)", ret);
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

int Client::InitialClient()
{
    if (m_options.m_feedAddrs.empty())
    {
        LOG_ERROR("", "feed server address is nullptr.");
        return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
    }

    if (m_options.m_fingerPrint.empty())
    {
        auto ret = bscp::GetMachineID(m_options.m_fingerPrint);
        if (ret)
        {
            LOG_ERROR(m_options.m_feedAddrs[0], "failed to get machine id.");
            return BSCP_CPP_SDK_CLIENT_INITIAL_ERROR;
        }
    }

    // create channel.
    m_channel = grpc::CreateChannel(m_options.m_feedAddrs[0], grpc::InsecureChannelCredentials());

    // initial upstream.
    m_upstream = std::make_shared<Upstream>(m_channel);
    LOG_INFO(m_options.m_feedAddrs[0], "success to initial upstream.");

    // initial cache.
    m_cache = std::make_shared<lru11::Cache<std::string, std::string>>(64, 0);
    LOG_INFO(m_options.m_feedAddrs[0], "success to initial cache.");

    // intial watcher.
    m_watcher = std::make_shared<Watcher>(m_options, m_channel, m_cache);
    LOG_INFO(m_options.m_feedAddrs[0], "success to initial watcher.");

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
    auto ret = SetContext(context, m_options, true);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to set grpc client context. err-code(%d)", ret);
        return ret;
    }

    // rpc call.
    ret = m_upstream->Handshake(context, hsMsg, hsRep);
    if (ret)
    {
        LOG_ERROR(m_options.m_feedAddrs[0], "failed to call grpc handshake. err-code(%d)", ret);
        return ret;
    }
    LOG_INFO(m_options.m_feedAddrs[0], "success to call handshake");

    LOG_INFO(m_options.m_feedAddrs[0], "success to initial bscp client");

    return BSCP_CPP_SDK_OK;
}

} // namespace bscp