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
#include <gtest/gtest.h>
#include "attest_error.h"
#include "attest_utils_log.h"
#include "attest_utils.h"
#include "attest_entry.h"
#include "attest_result_info.h"
#include "attest_type.h"
#include "attest_network.h"
#include "attest_service_active.h"
#include "attest_service_auth.h"
#include "attest_service_challenge.h"
#include "attest_service_device.h"
#include "attest_service.h"
#include "attest_service_device.h"
#include "attest_security_token.h"
#include "attest_service_reset.h"
#include "attest_tdd_mock_config.h"
#include "attest_network.h"
#include "attest_adapter.h"

using namespace testing::ext;
namespace OHOS {
namespace DevAttest {
static const int32_t TDD_AUTH_RESULT = 0;

static const int32_t ATTEST_GET_CHANLLEGE = 0;
static const int32_t ATTEST_RESET = 1;
static const int32_t ATTEST_ACTIVE = 2;
static const int32_t ATTEST_AUTH = 3;

static const int32_t ATTEST_CHANLLEGE_LEN = 64;

static const char* ATTEST_RESET_EXPECT_TOKEN = "WOetrEFOcjw8Px2TZNmq3ckoMzXEkkoLfgQeGNnG3XA=";

static const char* ATTEST_AUTH_EXPECT_RESULT = "{\"authStats\":\".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VO\
QUJMRSIsImV4cGlyZVRpbWUiOjE2ODMzNzM2NzE2NzQsImtpdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHRE\
ZXRhaWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc\
3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQy\
IsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAv\
T3Blbkhhcm1vbnkgMi4zIGJldGEvZGVidWcifQ.\",\
\"errcode\":0,\
\"ticket\":\"svnR0unsciaFi7S4hcpBa/LCSiYwNSt6\",\
\"token\":\"yh9te54pfTb91CrSqpD5fQsVBA/etKNb\",\
\"uuid\":\"156dcff8-0ab0-4521-ac8f-ba682e6ca5a0\"\
}3";

static const char* ATTEST_AUTH_GEN_TOKEN = "5HWNhKgnJ+sVZM313rCsNa3QK2RhrC4+bClH9SX5O84=";
static const char* ATTEST_AUTH_CHAP = "a81441e3c0d8d6a78907fa0888f9241be9591c4d6b7a533318b010fb2c3d9b80";
static const int64_t ATTEST_AUTH_CHAP_TIME = 1449458719;

static const char* ATTEST_ACTIVE_EXPECT_TOKEN = "648390656";
static const char* ATTEST_ACTIVE_CHAP = "01824812bda06b33e3c76ac8cf3f6d2153867ce39db08f625203a350d5635ac9";
static const int64_t ATTEST_ACTIVE_CHAP_TIME = 1449459365;

static const int64_t ATTEST_EXPIRRTIME = -584928741;
static const int32_t ATTEST_HARDWARERESULT = 0;

static const char* ATTEST_REST_ERROR_EXPECT_RESULT = "15003";

static const char* ATTEST_RESET_EXPECT_CHAP = "39a9d04d41617162893c3312ceb030acac8d8bd0cc9fcebcab5402a43891341d";
static const int64_t ATTEST_RESET_EXPECT_CHAP_TIME = 1449458490;

static const char* ATTEST_TICKET = "svnR0unsciaFi7S4hcpBa/LCSiYwNSt6";
static const char* ATTEST_STATUS = ".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSI\
sImV4cGlyZVRpbWUiOjE2ODMzNzM2NzE2NzQsImtpdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRh\
aWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc\
3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQy\
IsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAv\
T3Blbkhhcm1vbnkgMi4zIGJldGEvZGVidWcifQ.";

class AttestTddTest : public testing::Test {
public:
    static void SetUpTestCase(void);

    static void TearDownTestCase(void);

    void SetUp();

    void TearDown();
};

void AttestTddTest::SetUpTestCase(void)
{
    // input testsuit setup step，setup invoked before all testcases
    (void)InitSysData();
    (void)InitNetworkServerInfo();
}

void AttestTddTest::TearDownTestCase(void)
{
    // input testsuit teardown step，teardown invoked after all testcases
}

void AttestTddTest::SetUp()
{
    // input testcase setup step，setup invoked before each testcases
}

void AttestTddTest::TearDown()
{
    // input testcase teardown step，teardown invoked after each testcases
}

static AuthResult *GetAuthResult()
{
    AuthResult *authResult = CreateAuthResult();
    if (authResult == nullptr) {
        return nullptr;
    }
    int32_t ret = ParseAuthResultResp(ATTEST_AUTH_EXPECT_RESULT, authResult);
    if (ret != ATTEST_OK) {
        DestroyAuthResult(&authResult);
        return nullptr;
    }
    return authResult;
}

static DevicePacket* TddGenActiveMsg()
{
    if (ATTEST_CHANLLEGE_LEN != strlen(ATTEST_ACTIVE_CHAP)) {
        return NULL;
    }

    AuthResult *authResult = GetAuthResult();
    if (authResult == nullptr) {
        return nullptr;
    }

    DevicePacket* reqMsg = NULL;
    char attestChallengeActive[ATTEST_CHANLLEGE_LEN + 1] = {0};
    errno_t rc = memcpy_s(attestChallengeActive, ATTEST_CHANLLEGE_LEN + 1,
        ATTEST_ACTIVE_CHAP, ATTEST_CHANLLEGE_LEN);
    if (rc != EOK) {
        ATTEST_LOG_ERROR("[TddGenResetMsg] memset failed");
        return nullptr;
    }

    ChallengeResult challenge;
    challenge.challenge = attestChallengeActive;
    challenge.currentTime = ATTEST_ACTIVE_CHAP_TIME;
    int32_t ret = GenActiveMsg(authResult, &challenge, &reqMsg);
    DestroyAuthResult(&authResult);
    if (ret != ATTEST_OK) {
        return nullptr;
    }
    return reqMsg;
}

static DevicePacket* TddGenAuthMsg()
{
    if (ATTEST_CHANLLEGE_LEN != strlen(ATTEST_AUTH_CHAP)) {
        return NULL;
    }
    DevicePacket* reqMsg = NULL;
    char attestChallengeAuth[ATTEST_CHANLLEGE_LEN + 1] = {0};
    errno_t rc = memcpy_s(attestChallengeAuth, ATTEST_CHANLLEGE_LEN + 1,
        ATTEST_AUTH_CHAP, ATTEST_CHANLLEGE_LEN);
    if (rc != EOK) {
        ATTEST_LOG_ERROR("[TddGenResetMsg] memset failed");
        return nullptr;
    }

    ChallengeResult challenge;
    challenge.challenge = attestChallengeAuth;
    challenge.currentTime = ATTEST_AUTH_CHAP_TIME;
    int32_t ret = GenAuthMsg(&challenge, &reqMsg);
    if (ret != ATTEST_OK) {
        return nullptr;
    }
    return reqMsg;
}

static DevicePacket* TddGenResetMsg()
{
    if (ATTEST_CHANLLEGE_LEN != strlen(ATTEST_RESET_EXPECT_CHAP)) {
        return nullptr;
    }
    DevicePacket* reqMsg = NULL;
    char attestChallengeReset[ATTEST_CHANLLEGE_LEN + 1] = {0};
    errno_t rc = memcpy_s(attestChallengeReset, ATTEST_CHANLLEGE_LEN + 1,
        ATTEST_RESET_EXPECT_CHAP, ATTEST_CHANLLEGE_LEN);
    if (rc != EOK) {
        ATTEST_LOG_ERROR("[TddGenResetMsg] memset failed");
        return nullptr;
    }
    ChallengeResult challenge;
    challenge.challenge = attestChallengeReset;
    challenge.currentTime = ATTEST_RESET_EXPECT_CHAP_TIME;
    int32_t ret = GenResetMsg(&challenge, &reqMsg);
    if (ret != ATTEST_OK) {
        return nullptr;
    }
    return reqMsg;
}

void WriteAuthStatus()
{
    int32_t ret = FlushAuthResult(ATTEST_TICKET, ATTEST_STATUS);
    EXPECT_TRUE((ret == ATTEST_OK));
}

void TestGetAuthStatus(char **status)
{
    int32_t ret = GetAuthStatus(status);
    EXPECT_TRUE((ret == ATTEST_OK));
}

static void FreeAuthStatus(AuthStatus* authStatus)
{
    if (authStatus->versionId != NULL) {
        free(authStatus->versionId);
    }
    if (authStatus->authType != NULL) {
        free(authStatus->authType);
    }
    if (authStatus->softwareResultDetail != NULL) {
        free(authStatus->softwareResultDetail);
    }
    free(authStatus);
}

/*
 * @tc.name: TestInitNetWort001
 * @tc.desc: Test init network.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestInitNetWort001, TestSize.Level1)
{
    int ret = InitNetworkServerInfo();
    EXPECT_TRUE(ret == ATTEST_OK);
    ret = D2CConnect();
    EXPECT_TRUE(ret == ATTEST_OK);
}

/*
 * @tc.name: TestSendActiveMsg001
 * @tc.desc: Test send active msg.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestSendActiveMsg001, TestSize.Level1)
{
    (void)InitNetworkServerInfo();
    (void)D2CConnect();

    g_netType = ATTEST_ACTIVE;
    DevicePacket* reqMsg = TddGenActiveMsg();
    ASSERT_TRUE(reqMsg != NULL);

    char* respMsg = NULL;
    int32_t ret = SendActiveMsg(reqMsg, &respMsg);
    EXPECT_TRUE((ret == ATTEST_OK) && (respMsg != NULL));
    if (respMsg == NULL) {
        ATTEST_LOG_ERROR("[SendActiveMsgTdd] respMsg is NULL.");
        return;
    }
    if (ret != ATTEST_OK) {
        free(respMsg);
        ATTEST_LOG_ERROR("[SendActiveMsgTdd] Send active message failed, ret = %d.", ret);
        return;
    }
    const char* ATTEST_ACTIVE_EXPECT_RESULT = "{\"errcode\":0}";
    EXPECT_TRUE(strcmp(ATTEST_ACTIVE_EXPECT_RESULT, respMsg) == 0);
    free(respMsg);
}

/*
 * @tc.name: TestParseActiveResult001
 * @tc.desc: Test parse active result，result is ok.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestParseActiveResult001, TestSize.Level1)
{
    const char *input = "{\"errcode\":0}";
    int32_t ret = ParseActiveResult(input);
    EXPECT_TRUE(ret == ATTEST_OK);
}

/*
 * @tc.name: TestParseActiveResult002
 * @tc.desc: Test parse active result，result is error.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestParseActiveResult002, TestSize.Level1)
{
    const char *input = "{\"errcode\":\"-32s\"}";
    int32_t ret = ParseActiveResult(input);
    EXPECT_TRUE((ret != ATTEST_OK));
}

/*
 * @tc.name: TestGetAuthStatus001
 * @tc.desc: Test get authStatus.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestGetAuthStatus001, TestSize.Level1)
{
    WriteAuthStatus();
    char *status = nullptr;
    TestGetAuthStatus(&status);
    EXPECT_TRUE((status != nullptr));
    if (status == nullptr) {
        return;
    }
    EXPECT_TRUE(strcmp(ATTEST_STATUS, status) == 0);
    free(status);
}

/*
 * @tc.name: TestDecodeAuthStatus001
 * @tc.desc: Test decode auth status.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestDecodeAuthStatus001, TestSize.Level1)
{
    WriteAuthStatus();
    char *status = nullptr;
    TestGetAuthStatus(&status);
    AuthStatus* outStatus = CreateAuthStatus();
    EXPECT_TRUE((outStatus != nullptr));
    if (outStatus == nullptr) {
        return;
    }
    int32_t ret = DecodeAuthStatus(status, outStatus);
    EXPECT_TRUE(ret == ATTEST_OK);
    SoftwareResultDetail* detail = outStatus->softwareResultDetail;
    EXPECT_TRUE((outStatus->versionId != nullptr) && (outStatus->authType != nullptr) && (detail != nullptr));
    if ((outStatus->versionId == nullptr) || (outStatus->authType == nullptr) || (detail == nullptr)) {
        FreeAuthStatus(outStatus);
        return;
    }
    const char* ATTEST_AUTH_TYPE = "TOKEN_ENABLE";
    EXPECT_TRUE(strcmp(outStatus->authType, ATTEST_AUTH_TYPE) == 0);
    EXPECT_TRUE((outStatus->hardwareResult == ATTEST_HARDWARERESULT));
    FreeAuthStatus(outStatus);
}

/*
 * @tc.name: TestCheckExpireTime001
 * @tc.desc: Test check auth result.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestCheckExpireTime001, TestSize.Level1)
{
    AuthStatus* outStatus = CreateAuthStatus();
    EXPECT_TRUE(outStatus != nullptr);
    if (outStatus == nullptr) {
        return;
    }
    outStatus->expireTime = 19673222;
    uint64_t currentTime = 19673223;
    int32_t ret = CheckExpireTime(outStatus, currentTime);
    EXPECT_TRUE(ret != ATTEST_OK);
    outStatus->expireTime = 19673222;
    currentTime = 19673221;
    ret = CheckExpireTime(outStatus, currentTime);
    EXPECT_TRUE(ret == ATTEST_OK);
    free(outStatus);
}

/*
 * @tc.name: TestGenAuthMsg001
 * @tc.desc: Test gen auth msg.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestGenAuthMsg001, TestSize.Level1)
{
    DevicePacket* reqMsg = TddGenAuthMsg();
    ASSERT_TRUE((reqMsg != nullptr));

    char *outToken = reqMsg->tokenInfo.token;
    EXPECT_TRUE(outToken != nullptr);
    if (outToken == NULL) {
        FREE_DEVICE_PACKET(reqMsg);
        return;
    }
    EXPECT_TRUE(strcmp(outToken, ATTEST_AUTH_GEN_TOKEN) == 0);
    FREE_DEVICE_PACKET(reqMsg);
}

/*
 * @tc.name: TestParseAuthResultResp001
 * @tc.desc: Test parse auth result resp.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestParseAuthResultResp001, TestSize.Level1)
{
    AuthResult *authResult = GetAuthResult();
    ASSERT_TRUE(authResult != nullptr);

    EXPECT_TRUE((authResult->ticket != nullptr) && (authResult->tokenValue != nullptr) &&
        (authResult->authStatus != nullptr));
    if (authResult->ticket != nullptr) {
        EXPECT_TRUE(strcmp(authResult->ticket, ATTEST_TICKET) == 0);
    }
    DestroyAuthResult(&authResult);
}

/*
 * @tc.name: TestGetChallenge001
 * @tc.desc: Test get reset challenge.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestGetChallenge001, TestSize.Level1)
{
    g_netType = ATTEST_GET_CHANLLEGE;
    ChallengeResult* challenge = NULL;
    int32_t ret = GetChallenge(&challenge, ATTEST_ACTION_RESET);
    EXPECT_TRUE(ret == ATTEST_OK);
    EXPECT_TRUE(challenge != NULL);
    if (ret != ATTEST_OK) {
        FREE_CHALLENGE_RESULT(challenge);
        ATTEST_LOG_ERROR("[AttestTdd] GetChallenge failed, ret = %d.", ret);
        return;
    }
    EXPECT_TRUE(strcmp(ATTEST_RESET_EXPECT_CHAP, challenge->challenge) == 0);
    FREE_CHALLENGE_RESULT(challenge);
}

/*
 * @tc.name: TestGenResetMsg001
 * @tc.desc: Test gen reset msg.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestGenResetMsg001, TestSize.Level1)
{
    DevicePacket* reqMsg = TddGenResetMsg();
    EXPECT_TRUE((reqMsg != nullptr));
    if (reqMsg == nullptr) {
        return;
    }
    char *outToken = reqMsg->tokenInfo.token;
    EXPECT_TRUE(outToken != nullptr);
    if (outToken == NULL) {
        FREE_DEVICE_PACKET(reqMsg);
        return;
    }
    EXPECT_TRUE(strcmp(ATTEST_RESET_EXPECT_TOKEN, outToken) == 0);
    FREE_DEVICE_PACKET(reqMsg);
}

/*
 * @tc.name: TestSendResetMsg001
 * @tc.desc: Test send reset msg.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestSendResetMsg001, TestSize.Level1)
{
    g_netType = ATTEST_RESET;
    DevicePacket* reqMsg = TddGenResetMsg();
    if (reqMsg == NULL) {
        return;
    }
    char* respMsg = NULL;
    int32_t ret = SendResetMsg(reqMsg, &respMsg);
    EXPECT_TRUE((ret == ATTEST_OK) && (respMsg != NULL));
    if (respMsg == NULL) {
        FREE_DEVICE_PACKET(reqMsg);
        ATTEST_LOG_ERROR("[SendResetTdd] respMsg is NULL.");
        return;
    }
    if (ret != ATTEST_OK) {
        FREE_DEVICE_PACKET(reqMsg);
        free(respMsg);
        ATTEST_LOG_ERROR("[SendResetMsgTdd] Send reset message failed, ret = %d.", ret);
        return;
    }
    ATTEST_LOG_ERROR("[SendResetTdd] respMsg is NULL.respMsg = %s", respMsg);
    EXPECT_TRUE(strstr(respMsg, ATTEST_REST_ERROR_EXPECT_RESULT) != nullptr);
    free(respMsg);
    FREE_DEVICE_PACKET(reqMsg);
}

/*
 * @tc.name: TestQueryAttestStatus001
 * @tc.desc: Test query attest status.
 * @tc.type: FUNC
 */
HWTEST_F(AttestTddTest, TestQueryAttestStatus001, TestSize.Level1)
{
    AuthResult *authResult = GetAuthResult();
    ASSERT_TRUE(authResult != nullptr);

    int32_t ret = FlushToken(authResult);
    EXPECT_EQ(ret, ATTEST_OK);

    uint8_t authResultCode = TDD_AUTH_RESULT;
    AttestWriteAuthResultCode((char*)&authResultCode, 1);
    AttestResultInfo attestResultInfo = { .softwareResultDetail = {-2, -2, -2, -2, -2} };
    attestResultInfo.ticket = NULL;
    ret = EntryGetAttestStatus(&attestResultInfo);
    EXPECT_TRUE((ret == ATTEST_OK) && (attestResultInfo.authResult == ATTEST_OK));
    EXPECT_TRUE((attestResultInfo.ticket != nullptr));
    if (attestResultInfo.ticket == nullptr) {
        return;
    }
    EXPECT_TRUE(strcmp(attestResultInfo.ticket, ATTEST_TICKET) == 0);
}
}
}
