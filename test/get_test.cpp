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

#include "common.h"

extern std::map<std::string, std::string> g_argMap;

int TestGet()
{
    std::cout << "==========================" << std::endl;

    bscp::core::ClientOptions options;

    if (!CHECK_PARAMETER_EXIST("-token") || !CHECK_PARAMETER_EXIST("-addr") || !CHECK_PARAMETER_EXIST("-bid") ||
        !CHECK_PARAMETER_EXIST("-side_rid") || !CHECK_PARAMETER_EXIST("-app") || !CHECK_PARAMETER_EXIST("-key"))
    {
        return -1;
    }

    options.m_token = g_argMap["-token"];
    options.m_feedAddrs.push_back(g_argMap["-addr"]);
    options.m_bizID = std::stoi(g_argMap["-bid"]);
    options.m_sideRid = g_argMap["-side_rid"];

    // instantiate client.
    bscp::Client client(options);

    // set log handle, if not set, no logs will be output.
    bscp::log::Log::SetLogHandler(LogHandle);

    // you must initialize before you use client.
    auto ret = client.Initialize();
    if (ret)
    {
        std::cout << "failed to initialize client" << std::endl;
        return ret;
    }

    bscp::core::AppOptions appOptions;
    std::string app = g_argMap["-app"];

    std::string value;
    ret = client.Get(app, g_argMap["-key"], appOptions, value);
    if (ret)
    {
        std::cout << "something error" << std::endl;
    }
    else
    {
        // here is the value you get.
        std::cout << "value: " << value << std::endl;
        std::cout << "call get success" << std::endl;
    }

    return 0;
}

int TestGetAfterStopWatch()
{
    std::cout << "==========================" << std::endl;

    bscp::core::ClientOptions options;

    if (!CHECK_PARAMETER_EXIST("-token") || !CHECK_PARAMETER_EXIST("-addr") || !CHECK_PARAMETER_EXIST("-bid") ||
        !CHECK_PARAMETER_EXIST("-side_rid") || !CHECK_PARAMETER_EXIST("-app") || !CHECK_PARAMETER_EXIST("-key"))
    {
        return -1;
    }

    options.m_token = g_argMap["-token"];
    options.m_feedAddrs.push_back(g_argMap["-addr"]);
    options.m_bizID = std::stoi(g_argMap["-bid"]);
    options.m_sideRid = g_argMap["-side_rid"];

    bscp::Client client(options);

    // initialize client.
    auto ret = client.Initialize();
    if (ret)
    {
        std::cout << "failed to initialize client" << std::endl;
        return 2;
    }
    std::cout << "initialize client success" << std::endl;

    bscp::core::AppOptions appOptions;
    std::string app = g_argMap["-app"];

    // add watch.
    ret = client.AddWatcher(app, handle, appOptions);
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

    // stop watch.
    ret = client.StopWatch();
    if (ret)
    {
        std::cout << "failed to stop watch" << std::endl;
        return 5;
    }
    std::cout << "stop watch success" << std::endl;

    // call get.
    std::string value;
    ret = client.Get(app, g_argMap["-key"], appOptions, value);
    if (ret)
    {
        std::cout << "something error" << std::endl;
        return 5;
    }
    else
    {
        // here is the value you get.
        std::cout << "value: " << value << std::endl;
        std::cout << "call get success" << std::endl;
    }

    return 0;
}

TEST_CASE("API Get Test", "[client]")
{
    SECTION("client")
    {
        REQUIRE(0 == TestGet());
        REQUIRE(0 == TestGetAfterStopWatch());
    }
}
