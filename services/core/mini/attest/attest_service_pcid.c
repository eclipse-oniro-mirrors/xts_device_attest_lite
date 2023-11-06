/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef __LITEOS_M__
#include "attest_service_device.h"

#define ATTEST_DEFAULT_PCID "pcid"
char* GetPcid(void)
{
    // LITEOS_M not support pcid, this function return default value, but don't use
    return ATTEST_DEFAULT_PCID;
}
#endif