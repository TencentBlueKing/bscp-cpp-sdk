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

#ifndef _BSCP_CPP_SDK_CLIENT_H_
#define _BSCP_CPP_SDK_CLIENT_H_

// C++ standard.
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// grpc.
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

// bscp-cpp-sdk.
#include "internal/core/options.h"
#include "internal/core/upstream.h"
#include "internal/core/watch.h"
#include "internal/pkg/sf-share/type.h"
#include "internal/pkg/type.h"
#include "internal/tools/finger_print.h"
#include "internal/tools/log/log.h"
#include "third-party/lrucache11/LRUCache11.hpp"

// protocol.
#include "pkg/protocol/core/config-item/config_item.pb.h"
#include "pkg/protocol/core/hook/hook.pb.h"

namespace bscp {

/**
 * @brief Client. bscp client method.
 */
class Client final
{
public:
    Client(const ClientOptions& options, log::LogHandleFunc logHandleFunc)
        : m_options(options), m_logHandleFunc(logHandleFunc)
    {
        // initial log.
        log::Log::Instance().InitialLog(logHandleFunc);
    }
    ~Client() = default;

public:
    /**
     * @brief PullKvs get kv release from remote.
     *
     * @param app service name.
     * @param match match range.
     * @param opts app options.
     * @param release the output result.
     *
     * @return return 0 if success, non zero if failed.
     */
    int PullKvs(const std::string& app, std::vector<std::string>& match, const AppOptions& opts, Release& release);

    /**
     * @brief Get pull key value from remote.
     *
     * @param app service name.
     * @param key key name.
     * @param opts app options.
     * @param res the output result;
     *
     * @return return 0 if success, non zero if failed.
     */
    int Get(const std::string& app, const std::string& key, const AppOptions& opts, std::string& res);

    /**
     * @brief AddWatcher add a watcher to client.
     *
     * @param callback callback function.
     * @param app service name.
     * @param opts app options.
     *
     * @return return 0 if success, non zero if failed.
     */
    int AddWatcher(Callback callback, const std::string& app, AppOptions& opts);

    /**
     * @brief StartWatch start watch.
     *
     * @return return 0 if success, non zero if failed.
     */
    int StartWatch();

    /**
     * @brief StopWatch stop watch.
     *
     * @return return 0 if success, non zero if failed.
     */
    int StopWatch();

    /**
     * @brief InitialClient
     *
     * @return return 0 if success, non zero if failed.
     */
    int InitialClient();

private:
    // upstream client.
    std::shared_ptr<bscp::Upstream> m_upstream;

    // watcher.
    std::shared_ptr<Watcher> m_watcher;

    // client options.
    ClientOptions m_options;

    // grpc channel.
    std::shared_ptr<grpc::Channel> m_channel;

    // lru cache.
    std::shared_ptr<lru11::Cache<std::string, std::string>> m_cache;

    // log handle function.
    log::LogHandleFunc m_logHandleFunc;
};

} // namespace bscp

#endif // _BSCP_CPP_SDK_CLIENT_H_