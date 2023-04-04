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
#include "attest_channel.h"
#include "attest_tls.h"
#include "attest_utils.h"
#include "attest_utils_log.h"
#include "attest_tdd_mock_config.h"

#define MAX_INVOKE_TIME    3
#define MAX_NO_EXTEND_TIME 2
#define INTERFACE_COUNT    4

#define ATTEST_RESET_CHAP_FIRST_MSG   "2,0"
#define ATTEST_RESET_CHAP_SECOND_MSG   "1"
#define ATTEST_RESET_CHAP_THIRD_MSG   "6,9,9,2,1,3,9,1,9,1,1,1,1,1,1,3,5,3,1,5,5,5,9,5,5,5,5,5,5,5,9,5,5,5,5,5,5, \
1,5,5,1,5,5,5,5,5,9,5,9,5,5,5,5,9,5,5,5,9,4,1,5,9,5,9,1,5,5,9,5,1,1,1,4,4,5,5,5,5,4,1,9,5,3,4,3,9,1,1,1,1,1,1,8,1, \
1,1,3,5,4,5,5,4,5,5,4,5,5,4,5,5,5,4,3,1,1,1,9,1,1,1,3,5,4,1,0"

#define ATTEST_REST_ERROR_FIRST_MSG     "2,0"
#define ATTEST_REST_ERROR_SECOND_MSG    "5,0"
#define ATTEST_REST_ERROR_THIRD_MSG     "6,2,1,2,1,3,1,1,1,9,1,1,1,3,5,4,5,4,4,5,1,5"

#define ATTEST_AUTH_FIRST_MSG           "2,0"
#define ATTEST_AUTH_SECOND_MSG          "1,1,4"
#define ATTEST_AUTH_THIRD_MSG           "6,1,2,2,1,3,9,1,1,1,8,1,9,1,1,3,5,3,4,1,1,7,1,1,8,8,1,8,1,8,1,1,8,1,4,7,1 \
,1,1,7,6,7,1,1,8,8,1,8,7,1,1,9,8,7,5,7,1,8,8,8,4,8,7,8,4,8,7,8,8,7,7,8,8,7,1,7,1,8,5,9,7,1,1,9,8,8,1,9,8,8,1,7,1,6,5, \
7,6,7,1,7,6,7,1,7,8,6,1,7,8,6,1,7,1,1,1,1,7,6,1,9,7,1,1,1,8,7,5,8,4,4,1,7,1,7,1,9,1,8,5,8,8,7,1,8,1,8,1,1,8,1,4,7,1, \
1,1,7,6,6,1,7,1,1,1,9,5,5,1,1,7,1,1,9,1,8,8,9,8,7,4,9,7,8,6,9,8,8,1,9,8,1,1,7,1,1,1,9,7,7,4,8,5,1,7,9,8,9,1,9,7,7,1,9 \
,5,8,1,1,6,7,5,7,1,6,1,7,6,1,1,7,1,6,1,9,8,8,8,9,8,7,4,9,7,8,1,7,1,7,1,7,6,6,1,7,6,7,1,9,5,5,4,8,7,7,1,9,7,7,1,9,5,8, \
1,1,6,7,5,7,1,6,1,7,6,1,1,7,1,9,1,9,1,7,1,9,5,5,7,9,7,7,1,9,5,8,1,1,6,7,5,7,1,6,1,7,6,7,5,7,6,7,4,9,7,1,1,7,1,1,1,7, \
6,7,6,7,8,8,4,7,8,7,5,7,8,6,1,8,8,8,1,7,4,8,4,7,8,8,5,8,1,8,7,8,1,8,1,7,1,1,1,8,1,7,5,8,6,6,1,7,6,7,7,7,6,8,5,7,4,7, \
5,7,6,8,1,7,4,7,6,7,6,7,6,8,1,8,6,8,1,1,5,7,1,8,1,8,1,7,1,7,1,9,1,9,1,7,1,9,5,5,7,9,6,7,5,7,1,8,1,9,1,7,4,9,7,8,1,9, \
7,8,1,7,8,1,1,9,8,5,1,9,8,4,1,9,1,5,1,9,8,9,1,1,8,1,4,7,4,5,1,9,8,5,7,8,8,7,1,9,5,5,5,7,8,8,1,7,6"

#define ATTEST_ACTIVE_FIRST_MSG   "2,0"
#define ATTEST_ACTIVE_SECOND_MSG  "1"
#define ATTEST_ACTIVE_THIRD_MSG   "6,2,1,2,1,3,1,1,1,9,1,1,1,3,5,4,1,0"

static const char *mockTlsData[MAX_INVOKE_TIME][INTERFACE_COUNT] = {
    {ATTEST_RESET_CHAP_FIRST_MSG, ATTEST_REST_ERROR_FIRST_MSG, ATTEST_ACTIVE_FIRST_MSG, ATTEST_AUTH_FIRST_MSG},
    {ATTEST_RESET_CHAP_SECOND_MSG, ATTEST_REST_ERROR_SECOND_MSG, ATTEST_ACTIVE_SECOND_MSG, ATTEST_AUTH_SECOND_MSG},
    {ATTEST_RESET_CHAP_THIRD_MSG, ATTEST_REST_ERROR_THIRD_MSG, ATTEST_ACTIVE_THIRD_MSG, ATTEST_AUTH_THIRD_MSG}
};
bool isHasExtend[4] = {true, true, true, true};
int g_cout = 0;

static int32_t getCoapMsg(uint8_t* buf, size_t len)
{
    if (buf == NULL || len == 0) {
        return ATTEST_ERR;
    }
    if (g_cout > MAX_INVOKE_TIME || (g_netType < 0 || g_netType > INTERFACE_COUNT - 1)) {
        return ATTEST_ERR;
    }
    const char *input = mockTlsData[g_cout - 1][g_netType];
    size_t strLen = strlen(input);
    size_t realLen = (strLen + 1)/2 + 3;
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
        if (*indexInput != ',') {
            *indexTemp++ = *indexInput;
        }
        indexInput++;
    }
    buf = temp;
    return ATTEST_OK;
}

int32_t TLSConnect(TLSSession* session)
{
    ATTEST_LOG_DEBUG("[TLSConnect mock] Begin.");
    if (session == NULL) {
        return ERR_NET_INVALID_ARG;
    }
    return ATTEST_OK;
}

int32_t TLSWrite(const TLSSession* session, const uint8_t* buf, size_t len)
{
    (void)session;
    (void)buf;
    (void)len;
    return ATTEST_OK;
}

int32_t TLSRead(const TLSSession* session, uint8_t* buf, size_t len)
{
    (void)session;
    if (g_netType > INTERFACE_COUNT - 1) {
        return ATTEST_ERR;
    }
    int ret = getCoapMsg(buf, len);
    g_cout++;
    int maxInvokeTime = isHasExtend[g_netType] ? MAX_INVOKE_TIME : MAX_NO_EXTEND_TIME;
    if (g_cout == maxInvokeTime) {
        g_cout = 0;
    }
    return ret;
}

int32_t TLSClose(TLSSession* session)
{
    (void)session;
    return ATTEST_OK;
}
