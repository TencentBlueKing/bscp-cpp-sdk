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

#include "lock.h"

namespace bscp {
namespace tools {

RWMutex::RWMutex()
{
    pthread_rwlock_init(&m_rwMutex, NULL);
}

RWMutex::~RWMutex()
{
    pthread_rwlock_destroy(&m_rwMutex);
}

int RWMutex::RLock()
{
    return pthread_rwlock_rdlock(&m_rwMutex);
}

int RWMutex::TryRLock()
{
    return pthread_rwlock_tryrdlock(&m_rwMutex);
}

int RWMutex::WLock()
{
    return pthread_rwlock_wrlock(&m_rwMutex);
}

int RWMutex::TryWLock()
{
    return pthread_rwlock_trywrlock(&m_rwMutex);
}

int RWMutex::Unlock()
{
    return pthread_rwlock_unlock(&m_rwMutex);
}

} // namespace tools
} // namespace bscp