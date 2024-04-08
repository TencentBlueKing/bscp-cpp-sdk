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
#include "internal/module/lb/load_balance.h"
#include "internal/module/log/log.h"
#include "internal/pkg/sf-share/type.h"
#include "internal/pkg/type.h"
#include "internal/tools/finger_print.h"
#include "internal/tools/lock.h"
#include "third-party/lrucache11/LRUCache11.hpp"

// protocol.
#include "pkg/protocol/core/config-item/config_item.pb.h"
#include "pkg/protocol/core/hook/hook.pb.h"

namespace bscp {

/**
 * @brief Client. bscp client method.
 */
class Client final : public std::enable_shared_from_this<Client>
{
public:
    Client(const core::ClientOptions& options)
        : m_options(options), m_watchFlag(false), m_keepAliveFlag(false), m_readerValidFlag(true),
          m_reconnectSignal(false), m_initialFlag(false), m_lastHeartbeatTimeMS(0)
    {
    }
    ~Client();

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
    int PullKvs(const std::string& app, std::vector<std::string>& match, const core::AppOptions& opts,
                Release& release);

    /**
     * @brief Get pull key value from remote.
     *
     * @param app service name.
     * @param key key name.
     * @param opts app options.
     * @param value the output value;
     *
     * @return return 0 if success, non zero if failed.
     */
    int Get(const std::string& app, const std::string& key, const core::AppOptions& opts, std::string& value);

    /**
     * @brief AddWatcher add a watcher to client.
     *
     * @param app service name.
     * @param callback callback function.
     * @param opts app options.
     *
     * @return return 0 if success, non zero if failed.
     */
    int AddWatcher(const std::string& app, Callback callback, core::AppOptions& opts);

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
     * @brief Initialize initialize client.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Initialize();

private:
    /**
     * @brief WatchFunc watch func.
     *
     * @return void.
     */
    void WatchFunc();

    /**
     * @brief Heartbeat heart beat.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Heartbeat();

    /**
     * @brief KeepAlive keep channel alive.
     *
     * @return void.
     */
    void KeepAliveFunc();

    /**
     * @brief IsApiVersionMatch check api version.
     *
     * @param apiVersion input api version.
     *
     * @return return true if matched, false if unmatched.
     */
    bool IsApiVersionMatch(const pbbase::Versioning& apiVersion);

    /**
     * @brief OnReleaseChange handle all instances release change event.
     *
     * @param event release change event.
     *
     * @return return 0 if success, non zero if failed.
     */
    int OnReleaseChange(const sfs::ReleaseChangeEvent& event);

    /**
     * @brief Reconnect reconnect to server.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Reconnect();

private:
    // subscribers.
    std::vector<std::shared_ptr<Subscriber>> m_subscribers;

    // start watch flag, watch thread ending signal.
    std::atomic<bool> m_watchFlag;

    // watch thread.
    std::thread m_watchThread;

    // keep alive flag.
    std::atomic<bool> m_keepAliveFlag;

    // keep alive thread.
    std::thread m_keepAliveThread;

    // watch data payload.
    std::string m_payload;

    // watch return grpc reader stream.
    std::unique_ptr<grpc::ClientReader<pbfs::FeedWatchMessage>> m_reader;

    // watch client context.
    std::shared_ptr<grpc::ClientContext> m_readerContext;

    // reader valid flag.
    std::atomic<bool> m_readerValidFlag;

    // reconnect signal, send from work thread.
    std::atomic<bool> m_reconnectSignal;

    // last heart beat time.
    uint64_t m_lastHeartbeatTimeMS;

private:
    // upstream client.
    std::shared_ptr<core::Upstream> m_upstream;

    // client options.
    core::ClientOptions m_options;

    // grpc channel.
    std::shared_ptr<grpc::Channel> m_channel;

    // lru cache.
    std::shared_ptr<lru11::Cache<std::string, std::string>> m_cache;

    // load balancer.
    std::shared_ptr<lb::LoadBalancer> m_loadBalancer;

    // initialize flag.
    std::atomic<bool> m_initialFlag;
};

} // namespace bscp

#endif // _BSCP_CPP_SDK_CLIENT_H_