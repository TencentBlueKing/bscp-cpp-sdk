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

#ifndef _BSCP_CPP_SDK_INTERNAL_CORE_UPSTREAM_H_
#define _BSCP_CPP_SDK_INTERNAL_CORE_UPSTREAM_H_

// C++ standard.
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// grpc.
#include <grpcpp/grpcpp.h>

// sdk.
#include "internal/module/log/log.h"
#include "internal/pkg/protocol/feed-server/feed_server.grpc.pb.h"

namespace bscp {
namespace core {

/**
 * @brief Upstream.
 */
class Upstream final
{
public:
    Upstream(std::shared_ptr<grpc::Channel> channel) : m_stub(pbfs::Upstream::NewStub(channel)) {}
    ~Upstream() = default;

public:
    /**
     * @brief Handshake.
     *
     * @param context. grpc context.
     * @param message. input message.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int Handshake(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::HandshakeMessage> message,
                  std::shared_ptr<pbfs::HandshakeResp> resp);

    /**
     * @brief Messaging.
     *
     * @param context. grpc context.
     * @param meta. input meta.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int Messaging(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::MessagingMeta> meta,
                  std::shared_ptr<pbfs::MessagingResp> resp);

    /**
     * @brief Watch.
     *
     * @param context. grpc context.
     * @param meta. input meta.
     * @param reader. reader stream.
     *
     * @return return grpc reader, where can get the server message.
     */

    int Watch(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::SideWatchMeta> meta,
              std::unique_ptr<grpc::ClientReader<pbfs::FeedWatchMessage>>& reader);

    /**
     * @brief PullAppFileMeta.
     *
     * @param context. grpc context.
     * @param req. input request.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int PullAppFileMeta(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::PullAppFileMetaReq> req,
                        std::shared_ptr<pbfs::PullAppFileMetaResp> resp);

    /**
     * @brief GetDownloadURL.
     *
     * @param context. grpc context.
     * @param req. input request.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int GetDownloadURL(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::GetDownloadURLReq> req,
                       std::shared_ptr<pbfs::GetDownloadURLResp> resp);

    /**
     * @brief PullKvMeta.
     *
     * @param context. grpc context.
     * @param req. input request.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int PullKvMeta(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::PullKvMetaReq> req,
                   std::shared_ptr<pbfs::PullKvMetaResp> resp);

    /**
     * @brief GetKvValue.
     *
     * @param context. grpc context.
     * @param req. input request.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int GetKvValue(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::GetKvValueReq> req,
                   std::shared_ptr<pbfs::GetKvValueResp> resp);

    /**
     * @brief ListApps.
     *
     * @param context. grpc context.
     * @param req. input request.
     * @param resp. grpc server response.
     *
     * @return return 0 if success, non-zero if failed.
     */
    int ListApps(std::shared_ptr<grpc::ClientContext> context, std::shared_ptr<pbfs::ListAppsReq> req,
                 std::shared_ptr<pbfs::ListAppsResp> resp);

private:
    // grpc stub.
    std::unique_ptr<pbfs::Upstream::Stub> m_stub;
};

} // namespace core
} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_CORE_UPSTREAM_H_
