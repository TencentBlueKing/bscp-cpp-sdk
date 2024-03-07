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

#ifndef _BSCP_CPP_SDK_INTERNAL_TOOLS_RAPIDJSON_MACRO_H_
#define _BSCP_CPP_SDK_INTERNAL_TOOLS_RAPIDJSON_MACRO_H_

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/error/error.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#define RAPIDJSON_CHECK_IS_BOOL(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsBool())
#define RAPIDJSON_CHECK_IS_INT32(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsInt())
#define RAPIDJSON_CHECK_IS_UINT32(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsUint())
#define RAPIDJSON_CHECK_IS_INT64(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsInt64())
#define RAPIDJSON_CHECK_IS_UINT64(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsUint64())
#define RAPIDJSON_CHECK_IS_FLOAT(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsFloat())
#define RAPIDJSON_CHECK_IS_DOUBLE(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsDouble())
#define RAPIDJSON_CHECK_IS_STRING(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsString())
#define RAPIDJSON_CHECK_IS_NUMBER(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsNumber())
#define RAPIDJSON_CHECK_IS_ARRAY(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsArray())
#define RAPIDJSON_CHECK_IS_OBJECT(obj, strKey) (obj.HasMember(strKey) && obj[strKey].IsObject())

// NOTE: RAPIDJSON_GET_STRING/RAPIDJSON_ARRAY_GET_STRING cast the return value to std::string type
#define RAPIDJSON_GET_BOOL(obj, strKey, defVal) (RAPIDJSON_CHECK_IS_BOOL(obj, strKey) ? obj[strKey].GetBool() : defVal)
#define RAPIDJSON_GET_INT32(obj, strKey, defVal) (RAPIDJSON_CHECK_IS_INT32(obj, strKey) ? obj[strKey].GetInt() : defVal)
#define RAPIDJSON_GET_UINT32(obj, strKey, defVal)                                                                      \
    (RAPIDJSON_CHECK_IS_UINT32(obj, strKey) ? obj[strKey].GetUint() : defVal)
#define RAPIDJSON_GET_INT64(obj, strKey, defVal)                                                                       \
    (RAPIDJSON_CHECK_IS_INT64(obj, strKey) ? obj[strKey].GetInt64() : defVal)
#define RAPIDJSON_GET_UINT64(obj, strKey, defVal)                                                                      \
    (RAPIDJSON_CHECK_IS_UINT64(obj, strKey) ? obj[strKey].GetUint64() : defVal)
#define RAPIDJSON_GET_FLOAT(obj, strKey, defVal)                                                                       \
    (RAPIDJSON_CHECK_IS_FLOAT(obj, strKey) ? obj[strKey].GetFloat() : defVal)
#define RAPIDJSON_GET_DOUBLE(obj, strKey, defVal)                                                                      \
    (RAPIDJSON_CHECK_IS_DOUBLE(obj, strKey) ? obj[strKey].GetDouble() : defVal)
#define RAPIDJSON_GET_STRING(obj, strKey, defVal)                                                                      \
    (RAPIDJSON_CHECK_IS_STRING(obj, strKey) ? std::string(obj[strKey].GetString()) : defVal)
#define RAPIDJSON_ARRAY_GET_INT32(obj, i, defVal) (obj[i].IsInt() ? obj[i].GetInt() : defVal)
#define RAPIDJSON_ARRAY_GET_UINT32(obj, i, defVal) (obj[i].IsUint() ? obj[i].GetUint() : defVal)
#define RAPIDJSON_ARRAY_GET_INT64(obj, i, defVal) (obj[i].IsInt64() ? obj[i].GetInt64() : defVal)
#define RAPIDJSON_ARRAY_GET_UINT64(obj, i, defVal) (obj[i].IsUint64() ? obj[i].GetUint64() : defVal)
#define RAPIDJSON_ARRAY_GET_FLOAT(obj, i, defVal) (obj[i].IsFloat() ? obj[i].GetFloat() : defVal)
#define RAPIDJSON_ARRAY_GET_DOUBLE(obj, i, defVal) (obj[i].IsDouble() ? obj[i].GetDouble() : defVal)
#define RAPIDJSON_ARRAY_GET_STRING(obj, i, defVal) (obj[i].IsString() ? std::string(obj[i].GetString()) : defVal)

#define RAPIDJSON_SET_BOOL(obj, strKey, value)                                                                         \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Bool(value);                                                                                               \
    }
#define RAPIDJSON_SET_INT32(obj, strKey, value)                                                                        \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Int(value);                                                                                                \
    }
#define RAPIDJSON_SET_UINT32(obj, strKey, value)                                                                       \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Uint(value);                                                                                               \
    }
#define RAPIDJSON_SET_INT64(obj, strKey, value)                                                                        \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Int64(value);                                                                                              \
    }
#define RAPIDJSON_SET_UINT64(obj, strKey, value)                                                                       \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Uint64(value);                                                                                             \
    }
#define RAPIDJSON_SET_FLOAT(obj, strKey, value)                                                                        \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Double(value);                                                                                             \
    }
#define RAPIDJSON_SET_DOUBLE(obj, strKey, value)                                                                       \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.Double(value);                                                                                             \
    }
#define RAPIDJSON_SET_STRING(obj, strKey, value)                                                                       \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.String(value);                                                                                             \
    }

#define RAPIDJSON_SET_STRING_WITH_LEN(obj, strKey, value, lenValue)                                                    \
    {                                                                                                                  \
        obj.Key(strKey);                                                                                               \
        obj.String(value, lenValue);                                                                                   \
    }

#endif // _BSCP_CPP_SDK_INTERNAL_TOOLS_RAPIDJSON_MACRO_H_
