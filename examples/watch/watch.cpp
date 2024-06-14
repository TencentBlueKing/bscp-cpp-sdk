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

#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "client.h"

int main(int argc, char** argv)
{
    if (argc < 11 || strcmp(argv[1], "-token") || strcmp(argv[3], "-addr") || strcmp(argv[5], "-bid") || strcmp(argv[7], "-side_rid") ||
        strcmp(argv[9], "-app"))
    {
        std::cout << "parameters error!\nusage: " << argv[0] << " -token {token} -addr {addr} -bid {bid} -side_rid {side_rid} -app {app}"
                  << std::endl;

        return 0;
    }

    // set client options.
    bscp::core::ClientOptions options;

    options.m_token = argv[2];
    options.m_feedAddrs.push_back(argv[4]);
    options.m_bizID = std::stoi(argv[6]);
    options.m_sideRid = argv[8];

    // instantiate client.
    bscp::Client client(options);

    // set log handle, if not set, no logs will be output.
    bscp::log::Log::SetLogHandler([](const bscp::log::LogLevel& level, const std::string& msg) {
        std::cout << msg << std::endl;
        return 0;
    });

    // you must initialize before you use client.
    auto ret = client.Initialize();
    if (ret)
    {
        std::cout << "failed to initialize client" << std::endl;
        return ret;
    }

    bscp::core::AppOptions appOptions;
    std::string app = argv[10];

    // add watch.
    // set handle function for the watch receive release data.
    ret = client.AddWatcher(
        app,
        [&app, &appOptions, &client](const bscp::Release& release) {
            std::cout << "release ID: " << release.m_releaseID << std::endl;

            for (auto kv : release.m_kvItems)
            {
                std::string value;

                auto ret = client.Get(app, kv.m_key, appOptions, value);
                if (ret)
                {
                    std::cout << "call get error, err-code(" << ret << ")" << std::endl;
                    return ret;
                }

                std::cout << kv.m_key << "=" << value << std::endl;
            }
            return 0;
        },
        appOptions);
    if (ret)
    {
        std::cout << "failed to add watcher" << std::endl;
    }
    else
    {
        std::cout << "add watcher success" << std::endl;
    }

    // watch.
    // call this to watch the bscp server, if bscp server publish new release, it will call the handle callback function
    // user setted to handle the received release data.
    ret = client.StartWatch();
    if (ret)
    {
        std::cout << "failed to start watch" << std::endl;
    }
    std::cout << "start watch success" << std::endl;

    // in here, user can exec their tasks.
    // feel free to call other client api in here, such as Client::Get(), Client::PullKvs().
    std::cout << "exec other tasks" << std::endl;

    // when user does not need to watch, call stop watch to close the watch channel.
    ret = client.StopWatch();
    if (ret)
    {
        std::cout << "failed to stop watch" << std::endl;
    }
    else
    {
        std::cout << "stop watch success" << std::endl;
    }

    return 0;
}