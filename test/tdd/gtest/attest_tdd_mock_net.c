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
#include "attest_tdd_test_data.h"
#include "attest_utils.h"
#include "attest_utils_log.h"
#include "attest_tdd_mock_config.h"

#define MAX_INVOKE_TIME    3
#define MAX_NO_EXTEND_TIME 2
#define INTERFACE_COUNT    4

static char *mockTlsData[MAX_INVOKE_TIME][INTERFACE_COUNT] = 
    {
        {ATTEST_RESET_CHALLENGE_FIRST_MSG, ATTEST_REST_ERROR_FIRST_MSG, ATTEST_ACTIVE_FIRST_MSG, ATTEST_AUTH_FIST_MSG},
        {ATTEST_RESET_CHALLENGE_SECOND_MSG, ATTEST_REST_ERROR_SECOND_MSG, ATTEST_ACTIVE_SECOND_MSG, ATTEST_AUTH_SECOND_MSG},
        {ATTEST_RESET_CHALLENGE_THIRD_MSG, ATTEST_REST_ERROR_THIRD_MSG, ATTEST_ACTIVE_THIRD_MSG, ATTEST_AUTH_THIRD_MSG}
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
    char *input = mockTlsData[g_cout - 1][g_netType];
    size_t strLen = strlen(input);
    size_t realLen = (strLen + 1)/2 + 3;
    size_t charLen = sizeof(unsigned char);
    size_t mallocLen = (strLen == 1) ? charLen : (size_t)(charLen * realLen);
    uint8_t *temp = (uint8_t *)malloc(mallocLen);
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
    return g_isEnableNetWork ? ATTEST_OK : ERR_NET_SETUP_FAIL;
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
    g_cout++;
    int ret = getCoapMsg(buf, len);
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
