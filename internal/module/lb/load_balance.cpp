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

int LoadBalancer::Initialize() noexcept
{
    if (m_addrs.empty())
    {
        return BSCP_CPP_SDK_LB_INITIAL_ERROR;
    }

    m_initialFlag = true;

    return BSCP_CPP_SDK_OK;
}

std::string LoadBalancer::Get() noexcept
{
    if (!m_initialFlag)
    {
        return "";
    }

    if (m_cursor >= m_addrs.size())
    {
        return "";
    }

    return m_addrs[m_cursor];
}

int LoadBalancer::Update() noexcept
{
    if (!m_initialFlag)
    {
        return BSCP_CPP_SDK_LB_INITIAL_ERROR;
    }

    auto ret = 0;

    if (LoadStrategy::RR == m_strategy)
    {
        ret = RoundRobin();
    }
    else if (LoadStrategy::RANDOM == m_strategy)
    {
        ret = Random();
    }

    if (ret)
    {
        return ret;
    }

    return BSCP_CPP_SDK_OK;
}

int LoadBalancer::RoundRobin() noexcept
{
    if (!m_initialFlag || m_addrs.empty())
    {
        return BSCP_CPP_SDK_LB_INITIAL_ERROR;
    }

    m_cursor = (m_cursor + 1) % m_addrs.size();

    return BSCP_CPP_SDK_OK;
}

int LoadBalancer::Random() noexcept
{
    if (!m_initialFlag || m_addrs.empty())
    {
        return BSCP_CPP_SDK_LB_INITIAL_ERROR;
    }

    srand(static_cast<unsigned>(time(nullptr)));
    m_cursor = rand() % m_addrs.size();

    return BSCP_CPP_SDK_OK;
}

} // namespace lb
} // namespace bscp
