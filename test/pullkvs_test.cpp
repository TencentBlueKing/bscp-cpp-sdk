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
    return 0;
}

TEST_CASE("API PullKvs Test", "[client]")
{
    SECTION("client")
    {
        REQUIRE(0 == TestPullKvs());
    }
}
