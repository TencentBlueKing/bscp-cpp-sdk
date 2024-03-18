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

#ifndef _BSCP_CPP_SDK_INTERNAL_TOOLS_LOAD_BALANCE_H_
#define _BSCP_CPP_SDK_INTERNAL_TOOLS_LOAD_BALANCE_H_

#include <string>
#include <vector>

namespace bscp {
namespace lb {

enum class LoadStrategy
{
    rr = 0
};

class LoadBalance final
{
public:
    LoadBalance(const LoadStrategy& strategy, const std::vector<std::string>& addrs) noexcept
        : m_strategy(strategy), m_addrs(addrs), m_cursor(0)
    {
    }

    ~LoadBalance() = default;

public:
    /**
     * @brief Initialize initialize load balance.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Initialize();

    /**
     * @brief Get get current address.
     *
     * @return return current address.
     */
    std::string Get();

    /**
     * @brief Update update address in special strategy.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Update();

private:
    /**
     * @brief RoundRobin update address in round robin strategy.
     *
     * @return return 0 if success, non zero if failed.
     */
    int RoundRobin();

private:
    // addresses.
    std::vector<std::string> m_addrs;

    // strategy.
    LoadStrategy m_strategy;

    // current address cursor.
    uint16_t m_cursor;
};

} // namespace lb
} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_TOOLS_LOAD_BALANCE_H_