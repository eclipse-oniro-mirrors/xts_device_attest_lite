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
#include <securec.h>
#include "attest_adapter_mock.h"
#include "attest_type.h"

const char* ATTEST_TOKENID = "cb8cf67a-2c3e-44d6-b7bf-3eeed7724a55";
const char* ATTEST_TOKEVALUE = "XwTzVFdKzX/L8rJmDuqHnDlipM9QBT1d";
const char* ATTEST_SALT = "sfdsfTASDA";
const char* ATTEST_VERSION = "SFDSfdsSFSD";

// 读取Manufacturekey
int32_t AttestGetManufacturekey(uint8_t manufacturekey[], uint32_t len)
{
    return OsGetAcKeyStub((char*)manufacturekey, len);
}

// 读取ProductId
int32_t AttestGetProductId(uint8_t productId[], uint32_t len)
{
    if ((productId == NULL) || (len == 0)) {
        return ATTEST_ERR;
    }
    const char productIdBuf[] = "OH00004O";
    uint32_t productIdLen = strlen(productIdBuf);
    if (len < productIdLen) {
        return ATTEST_ERR;
    }

    int ret = memcpy_s(productId, len, productIdBuf, productIdLen);
    return ret;
}

// 读取ProductKey
int32_t AttestGetProductKey(uint8_t productKey[], uint32_t len)
{
    return OsGetProdKeyStub((char*)productKey, len);
}

int32_t AttestWriteToken(TokenInfo* tokenInfo)
{
    (void)tokenInfo;
    return ATTEST_OK;
}

int32_t AttestReadToken(TokenInfo* tokenInfo)
{
    if (tokenInfo == NULL) {
        return ATTEST_ERR;
    }
    if (memcpy_s(tokenInfo->tokenId, TOKEN_ID_ENCRYPT_LEN, ATTEST_TOKENID, TOKEN_ID_ENCRYPT_LEN) != 0) {
        return ATTEST_ERR;
    }
    if (memcpy_s(tokenInfo->tokenValue, TOKEN_VALUE_ENCRYPT_LEN, ATTEST_TOKEVALUE, TOKEN_VALUE_ENCRYPT_LEN) != 0) {
        return ATTEST_ERR;
    }
    if (memcpy_s(tokenInfo->salt, SALT_ENCRYPT_LEN, ATTEST_SALT, SALT_ENCRYPT_LEN) != 0) {
        return ATTEST_ERR;
    }
    if (memcpy_s(tokenInfo->version, VERSION_ENCRYPT_LEN, ATTEST_VERSION, VERSION_ENCRYPT_LEN) != 0) {
        return ATTEST_ERR;
    }
    return  ATTEST_OK;
}
