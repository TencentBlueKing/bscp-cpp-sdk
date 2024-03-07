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

#include "../client.h"
#include "common.h"
#include <map>
#include <string>

extern std::map<std::string, std::string> g_argMap;

int TestInitialClient()
{
    bscp::ClientOptions options;

    for (auto& iter : g_argMap)
    {
        std::cout << iter.first << ": " << iter.second << std::endl;
    }

    if (!CHECK_PARAMETER_EXIST("-token") || !CHECK_PARAMETER_EXIST("-addr") || !CHECK_PARAMETER_EXIST("-bid") ||
        !CHECK_PARAMETER_EXIST("-side_rid") || !CHECK_PARAMETER_EXIST("-app"))
    {
        return -1;
    }

    options.m_token = g_argMap["-token"];
    options.m_feedAddrs.push_back(g_argMap["-addr"]);
    options.m_bizID = std::stoi(g_argMap["-bid"]);
    options.m_sideRid = g_argMap["-side_rid"];

    bscp::Client client(options, LogHandle);
    auto ret = client.InitialClient();
    if (ret)
    {
        return 2;
    }

    return 0;
}

int TestContinueWatch()
{
    std::cout << "==========================" << std::endl;

    bscp::ClientOptions options;

    if (!CHECK_PARAMETER_EXIST("-token") || !CHECK_PARAMETER_EXIST("-addr") || !CHECK_PARAMETER_EXIST("-bid") ||
        !CHECK_PARAMETER_EXIST("-side_rid") || !CHECK_PARAMETER_EXIST("-app"))
    {
        return -1;
    }

    options.m_token = g_argMap["-token"];
    options.m_feedAddrs.push_back(g_argMap["-addr"]);
    options.m_bizID = std::stoi(g_argMap["-bid"]);
    options.m_sideRid = g_argMap["-side_rid"];

    bscp::Client client(options, LogHandle);

    // initial client.
    auto ret = client.InitialClient();
    if (ret)
    {
        std::cout << "failed to initial client" << std::endl;
        return 2;
    }
    std::cout << "initial client success" << std::endl;

    bscp::AppOptions appOptions;
    std::string app = g_argMap["-app"];

    // add watch.
    ret = client.AddWatcher(handle, app, appOptions);
    if (ret)
    {
        std::cout << "failed to add watcher" << std::endl;
        return 3;
    }
    std::cout << "add watcher success" << std::endl;

    // start watch.
    ret = client.StartWatch();
    if (ret)
    {
        std::cout << "failed to start watch" << std::endl;
        return 4;
    }
    std::cout << "start watch success" << std::endl;

    // continue call start watch, must call failed.
    for (int i = 1; i < 11; ++i)
    {
        auto ret = client.StartWatch();
        if (!ret)
        {
            std::cout << "continue call start watch success" << std::endl;
            return 5;
        }
    }

    // stop watch.
    ret = client.StopWatch();
    if (ret)
    {
        std::cout << "failed to stop watch" << std::endl;
    }
    std::cout << "stop watch success" << std::endl;

    return 0;
}

int TestContinueStartStopWatch()
{
    std::cout << "==========================" << std::endl;

    bscp::ClientOptions options;

    if (!CHECK_PARAMETER_EXIST("-token") || !CHECK_PARAMETER_EXIST("-addr") || !CHECK_PARAMETER_EXIST("-bid") ||
        !CHECK_PARAMETER_EXIST("-side_rid") || !CHECK_PARAMETER_EXIST("-app"))
    {
        return -1;
    }

    options.m_token = g_argMap["-token"];
    options.m_feedAddrs.push_back(g_argMap["-addr"]);
    options.m_bizID = std::stoi(g_argMap["-bid"]);
    options.m_sideRid = g_argMap["-side_rid"];

    bscp::Client client(options, LogHandle);

    // initial client.
    auto ret = client.InitialClient();
    if (ret)
    {
        std::cout << "failed to initial client" << std::endl;
        return 2;
    }
    std::cout << "initial client success" << std::endl;

    bscp::AppOptions appOptions;
    std::string app = g_argMap["-app"];

    // add watch.
    ret = client.AddWatcher(handle, app, appOptions);
    if (ret)
    {
        std::cout << "failed to add watcher" << std::endl;
        return 3;
    }
    std::cout << "add watcher success" << std::endl;

    // continue start stop watch.
    for (int i = 1; i < 11; ++i)
    {
        // start watch.
        ret = client.StartWatch();
        if (ret)
        {
            std::cout << "failed to start watch" << std::endl;
            return 4;
        }
        std::cout << "start watch success" << std::endl;

        // stop watch.
        ret = client.StopWatch();
        if (ret)
        {
            return 5;
            std::cout << "failed to stop watch" << std::endl;
        }
        std::cout << "stop watch success" << std::endl;
    }

    return 0;
}

TEST_CASE("API Watch Test", "[client]")
{
    SECTION("client")
    {
        REQUIRE(0 == TestInitialClient());
        REQUIRE(0 == TestContinueWatch());
        REQUIRE(0 == TestContinueStartStopWatch());
    }
}
