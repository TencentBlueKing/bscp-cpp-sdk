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

#ifndef _BSCP_CPP_SDK_INTERNAL_TOOLS_LOG_H_
#define _BSCP_CPP_SDK_INTERNAL_TOOLS_LOG_H_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "internal/tools/strings.h"

namespace bscp {
namespace log {

enum class LogLevel
{
    debug = 0,
    info = 1,
    warn = 2,
    error = 3
};

using LogHandleFunc = int (*)(const LogLevel& level, const std::string& msg);

class Log
{
public:
    Log() = default;
    ~Log() = default;

public:
    /**
     * @brief Instance single instance for logger instance.
     *
     * @return logger instance which is unique in global
     */
    static Log& Instance() noexcept
    {
        static Log inst;
        return inst;
    }

public:
    /**
     * @brief InitializeLog initialize log.
     *
     * @param handle log handle function.
     *
     * @return return 0 if success, non zero if failed.
     */
    int InitializeLog(LogHandleFunc handle);

    /**
     * @brief GetLogMsg get log message.
     *
     * @param level the log level.
     * @param file the log file name.
     * @param line the log file line.
     * @param upstream sdk upstream name.
     * @param msg the log message.
     * @param res the output result.
     *
     * @return return 0 if success, non zero if failed.
     */
    int GetLogMsg(const LogLevel& level, const std::string& file, const int line, const std::string& upstream,
                  const std::string& msg, std::string& res);

    /**
     * @brief Print print log
     *
     * @param level the log level.
     * @param file the log file name.
     * @param line the log file line.
     * @param upstream sdk upstream name.
     * @param msg the log message.
     * @param handle log handle function.
     *
     * @return return 0 if success, non zero if failed.
     */
    int Print(const LogLevel& level, const std::string& file, const int line, const std::string& upstream,
              const std::string& msg, LogHandleFunc handle);

    /**
     * @brief GetLogHandle get log handle function.
     *
     * @return return log handle function.
     */
    LogHandleFunc GetLogHandle();

private:
    /**
     * @brief LocalDateToString trans local date to target string.
     *
     * @param res the return result.
     *
     * @return return 0 if success, non zero if failed.
     */
    int LocalDateToString(std::string& res);

private:
    // log handle function.
    LogHandleFunc m_handle;
};

// NOTE: LOG internal format implement.
#define BSCP_CPP_SDK_LOG_FORMAT(level, file, line, upstream, fmt, ...)                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        bscp::log::Log::Instance().Print(level, file, line, upstream, bscp::UtilFormat((fmt), ##__VA_ARGS__),          \
                                         bscp::log::Log::Instance().GetLogHandle());                                   \
    } while (0)

#define LOG_DEBUG(upstream, fmt, ...)                                                                                  \
    BSCP_CPP_SDK_LOG_FORMAT(bscp::log::LogLevel::debug, __FILE__, __LINE__, upstream, fmt, ##__VA_ARGS__)

#define LOG_INFO(upstream, fmt, ...)                                                                                   \
    BSCP_CPP_SDK_LOG_FORMAT(bscp::log::LogLevel::info, __FILE__, __LINE__, upstream, fmt, ##__VA_ARGS__)

#define LOG_WARN(upstream, fmt, ...)                                                                                   \
    BSCP_CPP_SDK_LOG_FORMAT(bscp::log::LogLevel::warn, __FILE__, __LINE__, upstream, fmt, ##__VA_ARGS__)

#define LOG_ERROR(upstream, fmt, ...)                                                                                  \
    BSCP_CPP_SDK_LOG_FORMAT(bscp::log::LogLevel::error, __FILE__, __LINE__, upstream, fmt, ##__VA_ARGS__)

} // namespace log
} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_TOOLS_LOG_H_