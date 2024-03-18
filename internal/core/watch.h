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

#ifndef _BSCP_CPP_SDK_INTERNAL_CORE_WATCH_H_
#define _BSCP_CPP_SDK_INTERNAL_CORE_WATCH_H_

// C++ standard.
#include <chrono>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>

// grpc.
#include <grpcpp/grpcpp.h>

#include "options.h"
#include "upstream.h"

#include "internal/pkg/protocol/core/base/base.pb.h"
#include "internal/pkg/protocol/feed-server/feed_server.pb.h"
#include "internal/pkg/sf-share/type.h"
#include "internal/pkg/type.h"
#include "internal/tools/lb/load_balance.h"
#include "third-party/lrucache11/LRUCache11.hpp"

#define FEED_MESSAGE_TYPE_BOUNCE 1
#define FEED_MESSAGE_TYPE_PUBLISH_RELEASE 2

namespace bscp {

struct Subscriber
{
    AppOptions m_option;
    std::string m_app;
    // the callback function when the watched items are changed.
    Callback m_callback;
    // the current release id of the subscriber.
    uint32_t m_currentReleaseID = 0;
    // the labels of the subscriber.
    std::map<std::string, std::string> m_labels;
    // the unique id of the subscriber.
    std::string m_uid;
    // store the current config items of the subscriber, map[configItemName]commitID.
    std::map<std::string, uint32_t> m_currentConfigItems;
};

/**
 * @brief Watcher.
 */
class Watcher final
{
public:
    Watcher(const ClientOptions& options, std::shared_ptr<grpc::Channel>& channel,
            std::shared_ptr<lru11::Cache<std::string, std::string>>& cache,
            std::shared_ptr<lb::LoadBalance>& loadBalance)
        : m_channel(channel), m_options(options), m_watchFlag(false), m_reconnectSignal(false), m_cache(cache),
          m_loadBalance(loadBalance), m_keepAliveFlag(false)
    {
        m_upstream = std::make_shared<Upstream>(m_channel);
    }
    ~Watcher() = default;

public:
    /**
     * @brief Subscribe subscribe service.
     *
     * @param callback callback function.
     * @param app service name.
     * @param opts service special configure.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Subscribe(Callback callback, const std::string& app, AppOptions& opts);

    /**
     * @brief StartWatch start watch stream.
     *
     * @return return 0 if success, non zero if failed.
     */
    int StartWatch();

    /**
     * @brief StopWatch close watch stream.
     *
     * @return return 0 if success, non zero if failed.
     */
    int StopWatch();

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
    // start watch flag, watch thread ending signal.
    std::atomic<bool> m_watchFlag;

    // watch thread.
    std::thread m_watchThread;

    // current grpc channel to the watcher.
    std::shared_ptr<grpc::Channel> m_channel;

    // channel alive flag.
    std::atomic<bool> m_channelAliveFlag;

    // current client context to the watcher.
    std::shared_ptr<grpc::ClientContext> m_clientContext;

    // reconnect signal, send from work thread.
    std::atomic<bool> m_reconnectSignal;

    // keep alive flag.
    std::atomic<bool> m_keepAliveFlag;

    // keep alive thread.
    std::thread m_keepAliveThread;

    // watch return grpc reader stream.
    std::unique_ptr<grpc::ClientReader<pbfs::FeedWatchMessage>> m_reader;

    // watch data payload.
    std::string m_payload;

    // lru cache.
    std::shared_ptr<lru11::Cache<std::string, std::string>> m_cache;

    // load balance.
    std::shared_ptr<lb::LoadBalance> m_loadBalance;

    // subscribers.
    std::vector<std::shared_ptr<Subscriber>> m_subscribers;

    // client options.
    ClientOptions m_options;

    // upstream client.
    std::shared_ptr<Upstream> m_upstream;

    // last heart beat time.
    uint64_t m_lastHeartbeatTimeMS;
};

} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_CORE_WATCH_H_
