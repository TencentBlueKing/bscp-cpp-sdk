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

#include "load_balance.h"

#include "internal/error_code.h"

namespace bscp {
namespace lb {

int LoadBalance::Initialize()
{
    return m_addrs.empty() ? BSCP_CPP_SDK_LOAD_BALANCE_ERROR : BSCP_CPP_SDK_OK;
}

std::string LoadBalance::Get()
{
    return m_addrs[m_cursor];
}

int LoadBalance::Update()
{
    auto ret = 0;

    if (LoadStrategy::rr == m_strategy)
    {
        ret = RoundRobin();
    }

    return BSCP_CPP_SDK_OK;
}

int LoadBalance::RoundRobin()
{
    int len = m_addrs.size();

    m_cursor = (m_cursor + 1) % len;

    return BSCP_CPP_SDK_OK;
}

} // namespace lb
} // namespace bscp
