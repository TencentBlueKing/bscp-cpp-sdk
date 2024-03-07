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

#include "options.h"

#include "../error_code.h"
#include "../pkg/type.h"
#include "../tools/finger_print.h"

namespace bscp {

int SetContext(std::shared_ptr<grpc::ClientContext>& context, const ClientOptions& options, bool isHandshake)
{
    context->AddMetadata("authorization", "Bearer " + options.m_token);

    if (isHandshake)
    {
        context->AddMetadata("side-rid", options.m_sideRid);
    }

    SidecarMeta sidecarMetaObj;
    sidecarMetaObj.m_bid = options.m_bizID;

    if (options.m_fingerPrint.empty())
    {
        auto ret = GetMachineID(sidecarMetaObj.m_fpt);
        if (ret)
        {
            return BSCP_CPP_SDK_SET_CONTEXT_ERROR;
        }
    }
    else
    {
        sidecarMetaObj.m_fpt = options.m_fingerPrint;
    }

    std::string sidecarMeta;
    auto ret = sidecarMetaObj.Marshal(sidecarMeta);
    if (ret)
    {
        return BSCP_CPP_SDK_SET_CONTEXT_ERROR;
    }

    context->AddMetadata("sidecar-meta", sidecarMeta);

    return BSCP_CPP_SDK_OK;
}

} // namespace bscp