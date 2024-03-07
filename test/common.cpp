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

#include "common.h"

std::map<std::string, std::string> g_argMap;

int LogHandle(const bscp::log::LogLevel& level, const std::string& msg)
{
    std::cout << msg << std::endl;
    return 0;
}

int handle(const bscp::Release& release)
{
    std::cout << "running callback function" << std::endl;

    std::cout << release.m_releaseID << std::endl;

    return 0;
}