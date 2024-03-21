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

int TestPullKvs()
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

    std::vector<std::string> match;
    bscp::Release release;

    ret = client.PullKvs(app, match, appOptions, release);
    if (ret)
    {
        std::cout << "something error" << std::endl;
        return 0;
    }

    std::cout << "release ID: " << release.m_releaseID << std::endl;
    std::cout << "call pull kvs success" << std::endl;

    return 0;
}

TEST_CASE("API PullKvs Test", "[client]")
{
    SECTION("client")
    {
        REQUIRE(0 == TestPullKvs());
    }
}
