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

#include "log.h"
#include "internal/error_code.h"

// clang-format off

/* log level string defines */
#define LOG_LEVEL_ERROR "ERROR"
#define LOG_LEVEL_WARN  "WARN"
#define LOG_LEVEL_INFO  "INFO"
#define LOG_LEVEL_DEBUG "DEBUG"

// clang-format on

namespace bscp {
namespace log {

LogHandlerFunc Log::m_handler = nullptr;

int Log::LocalDateToString(std::string& res)
{
    try
    {
        std::ostringstream ss;

        // time=2024-01-16T15:07:12.053+08:00
        auto now = std::chrono::system_clock::now();
        std::time_t local = std::chrono::system_clock::to_time_t(now);

        struct tm tmInfo;
        localtime_r(&local, &tmInfo);

        char time[20] = {0};
        std::strftime(time, 20, "%Y-%m-%dT%H:%M:%S", &tmInfo);
        ss << time;

        // ms.
        auto milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000;
        ss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

        // zone.
        char timezone[6] = {0};
        std::strftime(timezone, sizeof(timezone), "%z", &tmInfo);
        int zone = std::atoi(timezone) / 100;

        if (zone >= 0)
        {
            ss << '+';
        }
        ss << std::setw(2) << zone << ":00";

        res = ss.str();
    }
    catch (...)
    {
        return BSCP_CPP_SDK_LOG_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

int Log::GetLogMsg(const LogLevel& level, const std::string& file, const int line, const std::string& msg,
                   std::string& res)
{
    std::string time;
    auto ret = LocalDateToString(time);
    if (ret)
    {
        return ret;
    }

    res = "time=" + time + " ";

    // log level.
    res += "level=";
    if (LogLevel::debug == level)
    {
        res += LOG_LEVEL_DEBUG;
    }
    else if (LogLevel::info == level)
    {
        res += LOG_LEVEL_INFO;
    }
    else if (LogLevel::warn == level)
    {
        res += LOG_LEVEL_WARN;
    }
    else if (LogLevel::error == level)
    {
        res += LOG_LEVEL_ERROR;
    }
    else
    {
        // something error.
        return BSCP_CPP_SDK_LOG_ERROR;
    }

    // source.
    res += " source=" + file + ":" + std::to_string(line) + " ";

    // msg.
    res += "msg=" + msg + " ";

    return BSCP_CPP_SDK_OK;
}

int Log::Print(const LogLevel& level, const std::string& file, const int line, const std::string& msg)
{
    if (nullptr == m_handler)
    {
        return BSCP_CPP_SDK_NULL_LOG_HANDLER;
    }

    std::string res;
    auto ret = GetLogMsg(level, file, line, msg, res);
    if (ret)
    {
        return ret;
    }

    ret = m_handler(level, res);
    if (ret)
    {
        return BSCP_CPP_SDK_LOG_HANDLER_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

void Log::SetLogHandler(LogHandlerFunc handler)
{
    m_handler = handler;
}

} // namespace log
} // namespace bscp
