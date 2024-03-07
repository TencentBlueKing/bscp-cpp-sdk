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

#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

#include "../../client.h"

int LogHandle(const bscp::log::LogLevel& level, const std::string& msg)
{
    std::cout << msg << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    // ./utest -token your_token -addr your_address -bid your_bid -side_rid your_side_rid -app your_app -key your_key
    if (argc < 13 || strcmp(argv[1], "-token") || strcmp(argv[3], "-addr") || strcmp(argv[5], "-bid") ||
        strcmp(argv[7], "-side_rid") || strcmp(argv[9], "-app") || strcmp(argv[11], "-key"))
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
    bscp::AppOptions appOptions;
    std::string app = argv[10];

    std::string value;

    int count = 0;

    auto ret = client.Get(app, argv[12], appOptions, value);
    if (ret)
    {
        std::cout << "something error" << std::endl;
    }
    else
    {
        std::cout << "call get success" << std::endl;
    }

    return 0;
}