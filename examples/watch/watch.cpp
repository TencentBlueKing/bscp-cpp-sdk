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

#include "../../client.h"

int handle(const bscp::Release& release)
{
    std::cout << "running callback function" << std::endl;

    std::cout << release.m_releaseID << std::endl;

    return 0;
}

int LogHandle(const bscp::log::LogLevel& level, const std::string& msg)
{
    std::cout << msg << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 11 || strcmp(argv[1], "-token") || strcmp(argv[3], "-addr") || strcmp(argv[5], "-bid") ||
        strcmp(argv[7], "-side_rid") || strcmp(argv[9], "-app"))
    {
        std::cout << "parameters error!\nplease start the programme as follow: ./utest -token token -addr addr -bid "
                     "bid -side_rid side_ird"
                  << std::endl;
        return 0;
    }

    bscp::ClientOptions options;

    options.m_token = argv[2];
    options.m_feedAddrs.push_back(argv[4]);
    options.m_bizID = std::stoi(argv[6]);
    options.m_sideRid = argv[8];

    bscp::Client client(options, LogHandle);
    auto ret = client.InitialClient();
    if (ret)
    {
        std::cout << "failed to initial client" << std::endl;
        return ret;
    }

    bscp::AppOptions appOptions;
    std::string app = argv[10];

    // add watch.
    ret = client.AddWatcher(handle, app, appOptions);
    if (ret)
    {
        std::cout << "failed to add watcher" << std::endl;
    }
    else
    {
        std::cout << "add watcher success" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(60 * 2));

    // watch.
    ret = client.StartWatch();
    if (ret)
    {
        std::cout << "failed to start watch" << std::endl;
    }
    else
    {
        std::cout << "start watch success" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(60 * 5));

    // stop watch.
    ret = client.StopWatch();
    if (ret)
    {
        std::cout << "failed to stop watch" << std::endl;
    }
    else
    {
        std::cout << "stop watch success" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(60 * 5));

    return 0;
}