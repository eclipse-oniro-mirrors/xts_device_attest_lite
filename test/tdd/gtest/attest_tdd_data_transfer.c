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
#include "securec.h"
#include "attest_utils.h"
#include "attest_utils_log.h"
int32_t AttestSeriaToBinary(const char* input, uint8_t** buf)
{
    if (buf == NULL || *buf == NULL) {
        return ATTEST_ERR;
    }
    size_t strLen = strlen(input);
    size_t realLen = strLen + 1;
    size_t charLen = sizeof(unsigned char);
    size_t mallocLen = (strLen == 1) ? charLen : (size_t)(charLen * realLen);
    uint8_t *temp = (uint8_t *)malloc(mallocLen);
    if (temp == NULL) {
        return ATTEST_ERR;
    }
    memset_s(temp, mallocLen, 0, mallocLen);

    unsigned char *indexInput = (unsigned char *)input;
    unsigned char *indexTemp = (unsigned char*)temp;
    while (*indexInput != '\0') {
        *indexTemp++ = *indexInput++;
    }
    *buf = temp;
    return ATTEST_OK;    
}
