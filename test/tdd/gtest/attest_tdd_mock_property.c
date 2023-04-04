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
#include "attest_utils.h"
#include "attest_adapter_os.h"

#define ATTEST_VERSION_ID       "default/hua-wei/kemin/default/OpenHarmony-4.0.3.2(Canary1)/ohos/max/10/OpenHarmony 2.3 beta/debug"
#define ATTEST_BUILD_ROOT_HASH  "test666"
#define ATTEST_SOFTWARE_VERSION "OpenHarmony 4.0.3.2"
#define ATTEST_PRODUCT_MODEL    "ohos"
#define ATTEST_BRAND            "kemin"
#define ATTEST_SECURITY_PATCH   "2022-09-01"
#define ATTEST_UDID             "81C9445279A3A417D4159FDFC62691BC8DA002E8463C70D23AB4CBF4DF98261C"

char* AttestGetVersionId(void)
{
    return AttestStrdup(ATTEST_VERSION_ID);
}

char* AttestGetBuildRootHash(void)
{
    return AttestStrdup(ATTEST_BUILD_ROOT_HASH);
}

char* AttestGetDisplayVersion(void)
{
    return AttestStrdup(ATTEST_SOFTWARE_VERSION);
}

char* AttestGetProductModel(void)
{
    return AttestStrdup(ATTEST_PRODUCT_MODEL);
}

char* AttestGetBrand(void)
{
    return AttestStrdup(ATTEST_BRAND);
}

char* AttestGetSecurityPatchTag(void)
{
    return AttestStrdup(ATTEST_SECURITY_PATCH);;
}

char* AttestGetUdid(void)
{
    return AttestStrdup(ATTEST_UDID);
}

char* AttestGetManufacture(void)
{
    return OsGetManufacture();
}