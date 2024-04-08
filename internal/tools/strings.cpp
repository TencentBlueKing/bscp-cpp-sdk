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

#include "strings.h"

namespace bscp {
namespace tools {

std::string UtilFormat(const char* fmt, ...)
{
    int size = 4096;
    std::unique_ptr<char[]> buffer(new char[size]);
    memset(buffer.get(), 0, size);

    while (true)
    {
        va_list args;
        va_start(args, fmt);
        int n = ::vsnprintf(buffer.get(), size, fmt, args);
        va_end(args);

        if (n >= 0 && n < size)
        {
            return std::string(buffer.get());
        }

        size = (n > -1) ? n + 1 : size * 2;
        buffer.reset(new char[size]);
        memset(buffer.get(), 0, size);
    }
}

} // namespace tools
} // namespace bscp
