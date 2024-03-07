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

#include "type.h"

namespace bscp {

int SidecarMeta::Marshal(std::string& value) const
{
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

    // root start.
    writer.StartObject();

    // bid.
    RAPIDJSON_SET_UINT32(writer, "bid", m_bid);

    // fpt.
    RAPIDJSON_SET_STRING(writer, "fpt", m_fpt.c_str());

    // root end.
    writer.EndObject();

    // marshal to string.
    value = strBuf.GetString();

    return BSCP_CPP_SDK_OK;
}

} // namespace bscp
