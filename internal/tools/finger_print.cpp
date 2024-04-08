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

#include "finger_print.h"

namespace bscp {
namespace tools {

std::string GetRandString(int len)
{
    std::srand(::time(NULL) + ::rand());

    std::string str;

    for (int i = 0; i < len; ++i)
    {
        switch ((::rand() % 2))
        {
        case 1:
            str.append(1, (char)('a' + ::rand() % 26));
            break;
        default:
            str.append(1, (char)('0' + ::rand() % 10));
            break;
        }
    }

    return str;
}

int GetMachineID(std::string& machineID)
{
    std::ifstream dbusPath("/var/lib/dbus/machine-id");
    if (dbusPath.is_open())
    {
        std::getline(dbusPath, machineID);
        dbusPath.close();
    }

    if (machineID.empty())
    {
        std::ifstream dbusPathEtc("/etc/machine-id");
        if (dbusPathEtc.is_open())
        {
            std::getline(dbusPathEtc, machineID);
            dbusPathEtc.close();
        }
    }

    // get machine id by custom rules.
    const int fingerPrintLen = 32;
    if (machineID.empty())
    {
        machineID = GetRandString(fingerPrintLen);
    }

    if (machineID.empty())
    {
        return BSCP_CPP_SDK_ERROR;
    }

    return BSCP_CPP_SDK_OK;
}

} // namespace tools
} // namespace bscp
