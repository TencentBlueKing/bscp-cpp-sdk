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

#ifndef _BSCP_CPP_SDK_INTERNAL_LOAD_BALANCE_H_
#define _BSCP_CPP_SDK_INTERNAL_LOAD_BALANCE_H_

#include <atomic>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

namespace bscp {
namespace lb {

enum class LoadStrategy
{
    RR = 0,
    RANDOM = 1
};

class LoadBalancer final
{
public:
    LoadBalancer(const LoadStrategy& strategy, const std::vector<std::string>& addrs) noexcept
        : m_strategy(strategy), m_addrs(addrs), m_cursor(0), m_initialFlag(false)
    {
    }

    ~LoadBalancer() = default;

public:
    /**
     * @brief Initialize initialize load balancer.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Initialize() noexcept;

    /**
     * @brief Get get current address.
     *
     * @return return current address.
     */
    std::string Get() noexcept;

    /**
     * @brief Update update address in special strategy.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Update() noexcept;

private:
    /**
     * @brief RoundRobin update address in round robin strategy.
     *
     * @return return 0 if success, non zero if failed.
     */
    int RoundRobin() noexcept;

    /**
     * @brief Random update address in random strategy.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Random() noexcept;

private:
    // addresses.
    std::vector<std::string> m_addrs;

    // strategy.
    LoadStrategy m_strategy;

    // current address cursor.
    uint16_t m_cursor;

    // initial flag.
    std::atomic<bool> m_initialFlag;
};

} // namespace lb
} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_LOAD_BALANCE_H_