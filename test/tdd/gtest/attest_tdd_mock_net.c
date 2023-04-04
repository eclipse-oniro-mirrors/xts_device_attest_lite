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
#include "attest_tdd_data_transfer.h"

#define MAX_INVOKE_TIME    3
#define MAX_NO_EXTEND_TIME 2
#define INTERFACE_COUNT    4

#define ATTEST_RESET_CHAP_FIRST_MSG   "20"
#define ATTEST_RESET_CHAP_SECOND_MSG   "10"
#define ATTEST_RESET_CHAP_THIRD_MSG   "65121391911111135351519555595995154551955955549595459151951995949455559155 \
1115555534391111118111354554545455545431119111354197"

#define ATTEST_REST_ERROR_FIRST_MSG     "20"
#define ATTEST_REST_ERROR_SECOND_MSG    "50"
#define ATTEST_REST_ERROR_THIRD_MSG     "6122131119111354544510"

#define ATTEST_AUTH_FIRST_MSG           "2,0"
#define ATTEST_AUTH_SECOND_MSG          "1,1,0"
#define ATTEST_AUTH_THIRD_MSG           "61521391118191135341171188181811814711176711881871198757188848784878877887 \
1718597119881988171657671768178817181711117619711187584417171918588718181181471117661711195511711918898749786988198 \
1171119774851798919771958116757161761171619888987497817171766176719554877197719581167571617611719191719557977195811 \
67571617675767497117111767678847875786188817484788581878181711181758661767776857475768174767676818681157181817171919 \
1719557967571819174978197817811985198419151989118147451985788719555788176517171857188757811951191518811786185619111 \
9141911171517771176197811891184343111911135443119111353715571414168888111154711617748113431111135316175817175778591 \
499111811111161343111135355994554499494551449559455441455915531133"

#define ATTEST_ACTIVE_FIRST_MSG   "2,0"
#define ATTEST_ACTIVE_SECOND_MSG  "10"
#define ATTEST_ACTIVE_THIRD_MSG   "611213111911135410"

static const char *mockTlsData[MAX_INVOKE_TIME][INTERFACE_COUNT] = {
    {ATTEST_RESET_CHAP_FIRST_MSG, ATTEST_REST_ERROR_FIRST_MSG, ATTEST_ACTIVE_FIRST_MSG, ATTEST_AUTH_FIRST_MSG},
    {ATTEST_RESET_CHAP_SECOND_MSG, ATTEST_REST_ERROR_SECOND_MSG, ATTEST_ACTIVE_SECOND_MSG, ATTEST_AUTH_SECOND_MSG},
    {ATTEST_RESET_CHAP_THIRD_MSG, ATTEST_REST_ERROR_THIRD_MSG, ATTEST_ACTIVE_THIRD_MSG, ATTEST_AUTH_THIRD_MSG}
};
bool isHasExtend[4] = {true, true, true, true};
int g_cout = 0;

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
    (void)len;
    if (g_cout > MAX_INVOKE_TIME || (g_netType < 0 || g_netType > INTERFACE_COUNT - 1)) {
        return ATTEST_ERR;
    }
    int32_t ret = AttestSeriaToBinary(mockTlsData[g_cout - 1][g_netType], &buf);
    g_cout++;
    int32_t maxInvokeTime = isHasExtend[g_netType] ? MAX_INVOKE_TIME : MAX_NO_EXTEND_TIME;
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
