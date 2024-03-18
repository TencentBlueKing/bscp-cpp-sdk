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
namespace sfs {

int SideWatchPayload::Marshal(std::string& value) const
{
    rj::StringBuffer strBuf;
    rj::Writer<rj::StringBuffer> writer(strBuf);

    // root start.
    writer.StartObject();

    // bizID.
    RAPIDJSON_SET_UINT32(writer, "bizID", m_bizID);

    // apps array start.
    writer.Key("apps");
    writer.StartArray();

    for (const auto& app : m_applications)
    {
        // SideAppMeta start.
        writer.StartObject();

        // appID.
        RAPIDJSON_SET_UINT32(writer, "appID", app.m_appID);

        // app.
        RAPIDJSON_SET_STRING(writer, "app", app.m_app.c_str());

        // namespace.
        RAPIDJSON_SET_STRING(writer, "namespace", app.m_namespace.c_str());

        // uid.
        RAPIDJSON_SET_STRING(writer, "uid", app.m_uid.c_str());

        // labels object start.
        writer.Key("labels");
        writer.StartObject();

        for (const auto& iter : app.m_labels)
        {
            RAPIDJSON_SET_STRING(writer, iter.first.c_str(), iter.second.c_str());
        }

        // labels object end.
        writer.EndObject();

        // currentReleaseID.
        RAPIDJSON_SET_UINT32(writer, "currentReleaseID", app.m_currentReleaseID);

        // currentCursorID.
        RAPIDJSON_SET_UINT32(writer, "currentCursorID", app.m_currentCursorID);

        // SideAppMeta end.
        writer.EndObject();
    }

    // apps array end.
    writer.EndArray();

    // root end.
    writer.EndObject();

    // marshal to string.
    value = strBuf.GetString();

    return BSCP_CPP_SDK_OK;
}

int ReleaseChangePayload::Unmarshal(const std::string& value)
{
    rj::Document doc;

    // parse json string.
    if (doc.Parse(value.data()).HasParseError())
    {
        return BSCP_CPP_SDK_JSON_ERROR;
    }

    // release meta.
    if (!RAPIDJSON_CHECK_IS_OBJECT(doc, "releaseMeta"))
    {
        return BSCP_CPP_SDK_JSON_ERROR;
    }

    auto releaseMetaObj = doc["releaseMeta"].GetObject();

    m_releaseMeta.m_app = RAPIDJSON_GET_STRING(releaseMetaObj, "app", "");
    m_releaseMeta.m_appID = RAPIDJSON_GET_UINT32(releaseMetaObj, "appID", 0);
    m_releaseMeta.m_releaseID = RAPIDJSON_GET_UINT32(releaseMetaObj, "releaseID", 0);

    // release meta ci metas.
    if (RAPIDJSON_CHECK_IS_ARRAY(releaseMetaObj, "ciMetas"))
    {
        for (auto& iter : releaseMetaObj["ciMetas"].GetArray())
        {
            ConfigItemMetaV1 ciMeta;

            auto CiMetaObj = iter.GetObject();

            ciMeta.m_id = RAPIDJSON_GET_UINT32(CiMetaObj, "id", 0);
            ciMeta.m_commitID = RAPIDJSON_GET_UINT32(CiMetaObj, "commentID", 0);

            // content spec.
            if (RAPIDJSON_CHECK_IS_OBJECT(CiMetaObj, "contentSpec"))
            {
                auto object = CiMetaObj["contentSpec"].GetObject();

                ciMeta.m_contentSpec.set_byte_size(RAPIDJSON_GET_UINT32(object, "byte_size", 0));
                ciMeta.m_contentSpec.set_signature(RAPIDJSON_GET_STRING(object, "signature", ""));
            }

            // content item spec.
            if (RAPIDJSON_CHECK_IS_OBJECT(CiMetaObj, "configItemSpec"))
            {
                auto object = CiMetaObj["configItemSpec"].GetObject();

                ciMeta.m_configItemSpec.set_name(RAPIDJSON_GET_STRING(object, "name", ""));
                ciMeta.m_configItemSpec.set_path(RAPIDJSON_GET_STRING(object, "path", ""));
                ciMeta.m_configItemSpec.set_file_type(RAPIDJSON_GET_STRING(object, "file_type", ""));
                ciMeta.m_configItemSpec.set_file_mode(RAPIDJSON_GET_STRING(object, "file_mode", ""));
                ciMeta.m_configItemSpec.set_memo(RAPIDJSON_GET_STRING(object, "memo", ""));

                // content item spec permission.
                if (!RAPIDJSON_CHECK_IS_OBJECT(object, "permission"))
                {
                    auto pObj = object["permission"].GetObject();

                    ciMeta.m_configItemSpec.mutable_permission()->set_user(RAPIDJSON_GET_STRING(pObj, "user", ""));
                    ciMeta.m_configItemSpec.mutable_permission()->set_user_group(
                        RAPIDJSON_GET_STRING(pObj, "user_group", ""));
                    ciMeta.m_configItemSpec.mutable_permission()->set_privilege(
                        RAPIDJSON_GET_STRING(pObj, "privilege", ""));
                }
            }

            // config item attachment.
            if (RAPIDJSON_CHECK_IS_OBJECT(CiMetaObj, "configItemAttachment"))
            {
                auto object = CiMetaObj["configItemAttachment"].GetObject();
                ciMeta.m_configItemAttachment.set_biz_id(RAPIDJSON_GET_UINT32(object, "biz_id", 0));
                ciMeta.m_configItemAttachment.set_app_id(RAPIDJSON_GET_UINT32(object, "app_id", 0));
            }

            ciMeta.m_repositoryPath = RAPIDJSON_GET_STRING(CiMetaObj, "repositoryPath", "");

            m_releaseMeta.m_ciMetas.push_back(ciMeta);
        }
    }

    // release meta kv metas.
    if (RAPIDJSON_CHECK_IS_ARRAY(releaseMetaObj, "kvMetas"))
    {
        for (auto& iter : releaseMetaObj["kvMetas"].GetArray())
        {
            KvMetaV1 kvMeta;

            auto kvMetaObj = iter.GetObject();

            kvMeta.m_id = RAPIDJSON_GET_UINT32(kvMetaObj, "id", 0);
            kvMeta.m_key = RAPIDJSON_GET_STRING(kvMetaObj, "key", "");
            kvMeta.m_kvType = RAPIDJSON_GET_STRING(kvMetaObj, "kv_type", "");

            // revision.
            if (RAPIDJSON_CHECK_IS_OBJECT(kvMetaObj, "revision"))
            {
                auto object = kvMetaObj["revision"].GetObject();

                kvMeta.m_revision.set_creator(RAPIDJSON_GET_STRING(object, "creator", ""));
                kvMeta.m_revision.set_reviser(RAPIDJSON_GET_STRING(object, "reviser", ""));
                kvMeta.m_revision.set_create_at(RAPIDJSON_GET_STRING(object, "create_at", ""));
                kvMeta.m_revision.set_update_at(RAPIDJSON_GET_STRING(object, "update_at", ""));
            }

            // kv attachment.
            if (RAPIDJSON_CHECK_IS_OBJECT(kvMetaObj, "kv_attachment"))
            {
                auto object = kvMetaObj["kv_attachment"].GetObject();
                kvMeta.m_kvAttachment.set_biz_id(RAPIDJSON_GET_UINT32(object, "biz_id", 0));
                kvMeta.m_kvAttachment.set_app_id(RAPIDJSON_GET_UINT32(object, "app_id", 0));
            }

            m_releaseMeta.m_kvMetas.push_back(kvMeta);
        }
    }

    // release meta repository.
    if (RAPIDJSON_CHECK_IS_OBJECT(releaseMetaObj, "repository"))
    {
        auto obj = releaseMetaObj["repository"].GetObject();

        m_releaseMeta.m_repository.m_root = RAPIDJSON_GET_STRING(obj, "root", "");
        m_releaseMeta.m_repository.m_accessKeyID = RAPIDJSON_GET_STRING(obj, "accessKeyId", "");
        m_releaseMeta.m_repository.m_secretAccessKey = RAPIDJSON_GET_STRING(obj, "secretAccessKey", "");
        m_releaseMeta.m_repository.m_url = RAPIDJSON_GET_STRING(obj, "url", "");

        // tls bytes.
        if (!RAPIDJSON_CHECK_IS_OBJECT(obj, "tls"))
        {
            auto object = obj["tls"].GetObject();

            m_releaseMeta.m_repository.m_insecureSkipVerify = RAPIDJSON_GET_BOOL(object, "insecure", false);
            m_releaseMeta.m_repository.m_caFileBytes = RAPIDJSON_GET_STRING(object, "ca", "");
            m_releaseMeta.m_repository.m_certFileBytes = RAPIDJSON_GET_STRING(object, "cert", "");
            m_releaseMeta.m_repository.m_keyFileBytes = RAPIDJSON_GET_STRING(object, "key", "");
        }
    }

    // release meta pre hook.
    if (RAPIDJSON_CHECK_IS_OBJECT(releaseMetaObj, "preHook"))
    {
        auto obj = releaseMetaObj["preHook"].GetObject();

        m_releaseMeta.m_preHook.set_name(RAPIDJSON_GET_STRING(obj, "name", ""));
        m_releaseMeta.m_preHook.set_type(RAPIDJSON_GET_STRING(obj, "type", ""));
        m_releaseMeta.m_preHook.set_tag(RAPIDJSON_GET_STRING(obj, "type", ""));
        m_releaseMeta.m_preHook.set_memo(RAPIDJSON_GET_STRING(obj, "memo", ""));
        m_releaseMeta.m_preHook.set_content(RAPIDJSON_GET_STRING(obj, "content", ""));
    }

    // release meta post hook.
    if (RAPIDJSON_CHECK_IS_OBJECT(releaseMetaObj, "postHook"))
    {
        auto obj = releaseMetaObj["postHook"].GetObject();

        m_releaseMeta.m_preHook.set_name(RAPIDJSON_GET_STRING(obj, "name", ""));
        m_releaseMeta.m_preHook.set_type(RAPIDJSON_GET_STRING(obj, "type", ""));
        m_releaseMeta.m_preHook.set_tag(RAPIDJSON_GET_STRING(obj, "type", ""));
        m_releaseMeta.m_preHook.set_memo(RAPIDJSON_GET_STRING(obj, "memo", ""));
        m_releaseMeta.m_preHook.set_content(RAPIDJSON_GET_STRING(obj, "content", ""));
    }

    // instance meta.
    if (!RAPIDJSON_CHECK_IS_OBJECT(doc, "instance"))
    {
        return BSCP_CPP_SDK_JSON_ERROR;
    }

    auto instanceMetaObj = doc["instance"].GetObject();

    m_instance.m_bizID = RAPIDJSON_GET_UINT32(instanceMetaObj, "bizID", 0);
    m_instance.m_appID = RAPIDJSON_GET_UINT32(instanceMetaObj, "appID", 0);
    m_instance.m_app = RAPIDJSON_GET_STRING(instanceMetaObj, "app", "");
    m_instance.m_uid = RAPIDJSON_GET_STRING(instanceMetaObj, "uid", "");
    m_instance.m_configType = RAPIDJSON_GET_STRING(instanceMetaObj, "configType", "");

    // instance meta labels.
    if (RAPIDJSON_CHECK_IS_OBJECT(instanceMetaObj, "labels"))
    {
        auto object = instanceMetaObj["labels"].GetObject();
        for (auto iter = object.MemberBegin(); iter != object.MemberEnd(); ++iter)
        {
            m_instance.m_labels[iter->name.GetString()] = iter->value.GetString();
        }
    }

    // cursor id.
    m_cursorID = RAPIDJSON_GET_UINT32(doc, "cursorID", 0);

    return BSCP_CPP_SDK_OK;
}

} // namespace sfs
} // namespace bscp