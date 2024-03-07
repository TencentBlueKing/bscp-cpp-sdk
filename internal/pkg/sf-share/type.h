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

#ifndef _BSCP_CPP_SDK_INTERNAL_PKG_SF_SHARE_TYPE_H_
#define _BSCP_CPP_SDK_INTERNAL_PKG_SF_SHARE_TYPE_H_

#include <map>
#include <string>

#include "../../error_code.h"
#include "../../tools/rapidjson_macro.h"

#include "pkg/protocol/core/base/base.pb.h"
#include "pkg/protocol/core/config-item/config_item.pb.h"
#include "pkg/protocol/core/content/content.pb.h"
#include "pkg/protocol/core/hook/hook.pb.h"
#include "pkg/protocol/core/kv/kvs.pb.h"
#include "pkg/protocol/feed-server/feed_server.pb.h"

namespace bscp {
namespace sfs {

namespace rj = rapidjson;

// the current api version used between sidecar and feed server.
#define BSCP_CPP_SDK_CURRENT_MAJOR_VERSION 1
#define BSCP_CPP_SDK_CURRENT_MINOR_VERSION 0
#define BSCP_CPP_SDK_CURRENT_PATCH_VERSION 0

// the least sidecar's api version that this feed server can work for.
#define BSCP_CPP_SDK_LEAST_MAJOR_VERSION 1
#define BSCP_CPP_SDK_LEAST_MINOR_VERSION 0
#define BSCP_CPP_SDK_LEAST_PATCH_VERSION 0

/**
 * @brief SideAppMeta defines an app's metadata within the sidecar.
 */
struct SideAppMeta
{
    uint32_t m_appID = 0;
    std::string m_app;
    std::string m_namespace;
    std::string m_uid;
    std::map<std::string, std::string> m_labels;
    // sidecar's current effected release id.
    uint32_t m_currentReleaseID = 0;
    // sidecar's current cursor id.
    uint32_t m_currentCursorID = 0;
};

/**
 * @brief SideWatchPayload defines the payload information for sidecar to watch feed server.
 */
struct SideWatchPayload
{
    uint32_t m_bizID = 0;
    std::vector<SideAppMeta> m_applications;

    /**
     * @brief Marshal marshal the metadata to json string.
     *
     * @param value output marshal json string.
     *
     * @return returns 0 on success and others on failure.
     */
    int Marshal(std::string& value) const;
};

/**
 * @brief ReleaseChangeEvent defines the release change event's detail information.
 */
struct ReleaseChangeEvent
{
    std::string m_rid;
    pbbase::Versioning m_apiVersion;
    std::string m_payload;
};

/**
 * @brief KvMetaV1 defines the released kv metadata.
 */
struct KvMetaV1
{
    uint32_t m_id = 0;
    std::string m_key;
    std::string m_kvType;
    pbbase::Revision m_revision;
    pbkv::KvAttachment m_kvAttachment;
};

/**
 * @brief ConfigItemMetaV1 defines the released configure item's metadata.
 */
struct ConfigItemMetaV1
{
    uint32_t m_id = 0;
    uint32_t m_commitID = 0;
    pbcontent::ContentSpec m_contentSpec;
    pbci::ConfigItemSpec m_configItemSpec;
    pbci::ConfigItemAttachment m_configItemAttachment;
    std::string m_repositoryPath;
};

/**
 * @brief RepositoryV1 repository.
 */
struct RepositoryV1
{
    std::string m_root;
    std::string m_accessKeyID;
    std::string m_secretAccessKey;
    std::string m_url;

    // tls bytes.
    bool m_insecureSkipVerify = false;
    std::string m_caFileBytes;
    std::string m_certFileBytes;
    std::string m_keyFileBytes;
};

/**
 * @brief ReleaseEventMetaV1 defines the event details when the sidecar watch the feed server to get the latest release.
 */
struct ReleaseEventMetaV1
{
    uint32_t m_appID = 0;
    uint32_t m_releaseID = 0;

    std::string m_app;
    std::vector<ConfigItemMetaV1> m_ciMetas;
    std::vector<KvMetaV1> m_kvMetas;

    RepositoryV1 m_repository;

    pbhook::HookSpec m_preHook;
    pbhook::HookSpec m_postHook;
};

/**
 * @brief InstanceSpec defines the specifics for an app instance to watch the event.
 */
struct InstanceSpec
{
    // instance.
    uint32_t m_bizID = 0;
    uint32_t m_appID = 0;
    std::string m_app;
    std::string m_uid;

    // file or kv.
    std::string m_configType;

    std::map<std::string, std::string> m_labels;
};

/**
 * @brief ReleaseChangePayload release change payload.
 */
struct ReleaseChangePayload
{
    // release meta.
    ReleaseEventMetaV1 m_releaseMeta;

    // instance.
    InstanceSpec m_instance;

    // cursor id.
    uint32_t m_cursorID = 0;

    /**
     * @brief Marshal marshal the metadata to json string.
     *
     * @param value output marshal json string.
     *
     * @return returns 0 on success and others on failure.
     */
    int Marshal(std::string& value) const;

    /**
     * @brief Unmarshal unmarshal json string to metadata.
     *
     * @param value json string.
     *
     * @return returns 0 on success and others on failure.
     */
    int Unmarshal(const std::string& value);
};

} // namespace sfs
} // namespace bscp

#endif // _BSCP_CPP_SDK_INTERNAL_PKG_SF_SHARE_TYPE_H_