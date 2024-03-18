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

#include "upstream.h"

#include "internal/error_code.h"

namespace bscp {

int Upstream::Handshake(const std::shared_ptr<grpc::ClientContext>& context,
                        const std::shared_ptr<pbfs::HandshakeMessage>& message,
                        std::shared_ptr<pbfs::HandshakeResp>& resp)
{
    // validate input param.
    if (nullptr == message)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::HandshakeResp>();
    }

    grpc::Status status = m_stub->Handshake(context.get(), *message.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc handshake. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    // validate grpc response.
    if (!resp->has_api_version())
    {
        LOG_WARN("", "failed to call grpc handshake, invalided response.");
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::Messaging(const std::shared_ptr<grpc::ClientContext>& context,
                        const std::shared_ptr<pbfs::MessagingMeta>& meta, std::shared_ptr<pbfs::MessagingResp>& resp)
{
    // validate input param.
    if (nullptr == meta)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::MessagingResp>();
    }

    grpc::Status status = m_stub->Messaging(context.get(), *meta.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc messaging. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::Watch(const std::shared_ptr<grpc::ClientContext>& context,
                    const std::shared_ptr<pbfs::SideWatchMeta>& meta,
                    std::unique_ptr<grpc::ClientReader<pbfs::FeedWatchMessage>>& reader)
{
    // validate input param.
    if (nullptr == meta)
    {
        LOG_ERROR("", "the meta of the watch request is nullptr");
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // call handshake.

    // get the reader stream.
    reader = m_stub->Watch(context.get(), *meta.get());

    return BSCP_CPP_SDK_OK;
}

int Upstream::PullAppFileMeta(const std::shared_ptr<grpc::ClientContext>& context,
                              const std::shared_ptr<pbfs::PullAppFileMetaReq>& req,
                              std::shared_ptr<pbfs::PullAppFileMetaResp>& resp)
{
    // validate input param.
    if (nullptr == req)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::PullAppFileMetaResp>();
    }

    grpc::Status status = m_stub->PullAppFileMeta(context.get(), *req.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc pull app file meta. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::GetDownloadURL(const std::shared_ptr<grpc::ClientContext>& context,
                             const std::shared_ptr<pbfs::GetDownloadURLReq>& req,
                             std::shared_ptr<pbfs::GetDownloadURLResp>& resp)
{
    // validate input param.
    if (nullptr == req)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::GetDownloadURLResp>();
    }

    grpc::Status status = m_stub->GetDownloadURL(context.get(), *req.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc get download url. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::PullKvMeta(const std::shared_ptr<grpc::ClientContext>& context,
                         const std::shared_ptr<pbfs::PullKvMetaReq>& req, std::shared_ptr<pbfs::PullKvMetaResp>& resp)
{
    // validate input param.
    if (nullptr == req)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::PullKvMetaResp>();
    }

    grpc::Status status = m_stub->PullKvMeta(context.get(), *req.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::GetKvValue(const std::shared_ptr<grpc::ClientContext>& context,
                         const std::shared_ptr<pbfs::GetKvValueReq>& req, std::shared_ptr<pbfs::GetKvValueResp>& resp)
{
    // validate input param.
    if (nullptr == req)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::GetKvValueResp>();
    }

    grpc::Status status = m_stub->GetKvValue(context.get(), *req.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc get kv value. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::ListApps(const std::shared_ptr<grpc::ClientContext>& context,
                       const std::shared_ptr<pbfs::ListAppsReq>& req, std::shared_ptr<pbfs::ListAppsResp>& resp)
{
    // validate input param.
    if (nullptr == req)
    {
        return BSCP_CPP_SDK_INVALID_PARAM;
    }

    // allocate memory if resp is nullptr.
    if (nullptr == resp)
    {
        resp = std::make_shared<pbfs::ListAppsResp>();
    }

    grpc::Status status = m_stub->ListApps(context.get(), *req.get(), resp.get());

    // validate grpc status.
    if (!status.ok())
    {
        LOG_ERROR("", "failed to call grpc list apps. err-msg(%s)", status.error_message().c_str());
        return BSCP_CPP_SDK_GRPC_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Upstream::Reconnect(std::shared_ptr<grpc::Channel>& channel, int retryCount)
{
    int count = 0;

    while (count < retryCount)
    {
        // exponential backoff.
        if (count)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1 << count));
        }

        m_stub = pbfs::Upstream::NewStub(channel);
    }

    return BSCP_CPP_SDK_OK;
}

} // namespace bscp