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

#ifndef _BSCP_CPP_SDK_TEST_COMMON_H_
#define _BSCP_CPP_SDK_TEST_COMMON_H_

#include <iostream>
#include <string>

#include "../client.h"
#include "../third-party/catch2/catch.hpp"

#define CHECK_PARAMETER_EXIST(param) (g_argMap.find(param) == g_argMap.end() ? false : true)

int LogHandle(const bscp::log::LogLevel& level, const std::string& msg);

int handle(const bscp::Release& release);

#endif // _BSCP_CPP_SDK_TEST_COMMON_H_