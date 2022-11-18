/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#ifndef ATTEST_MOCK_H
#define ATTEST_MOCK_H

#include <stdint.h>
#include "attest_adapter_mock.h"
#include "attest_adapter_oem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define ATTEST_MOCK_TOKEN "6PkCJZDsUfuqqdvxTLv8ZH+FqASsUInUV4y9IPLHtPyJt0v0RrwtVaLHpEunfMjD,\
yCbOb5Y3M4sgXEqhyTqIXwDl4JEWTmEfWr3Vov0NamgsBmzMCHXsM4xH3pNT+ZMd,XXoIPrlEu6EV+/rI,1000"

#define ATTEST_MOCK_DEVICE_PARA_VERSION_ID "versionId"
#define ATTEST_MOCK_DEVICE_PARA_VERSION_HASH "buildRootHash"
#define ATTEST_MOCK_DEVICE_PARA_DISPLAY_VERSION "displayVersion"
#define ATTEST_MOCK_DEVICE_PARA_MANU_STR "manufacture"
#define ATTEST_MOCK_DEVICE_PARA_DEVICE_MODEL "productModel"
#define ATTEST_MOCK_DEVICE_PARA_BRAND "brand"
#define ATTEST_MOCK_DEVICE_PARA_PATCH_TAG "securityPatchTag"
#define ATTEST_MOCK_DEVICE_PARA_SERIAL "serial"

#define ATTEST_MOCK_NETWORK_PARA_CURRENTTIME "currentTime"
#define ATTEST_MOCK_NETWORK_PARA_CHALLENGE "challenge"
#define ATTEST_MOCK_NETWORK_PARA_ERRCODE "errcode"
#define ATTEST_MOCK_NETWORK_PARA_TICKET "ticket"
#define ATTEST_MOCK_NETWORK_PARA_UUID "uuid"
#define ATTEST_MOCK_NETWORK_PARA_AUTHSTATS "authStats"
#define ATTEST_MOCK_NETWORK_PARA_TOKEN "token"

#define ATTEST_MOCK_NETWORK_RESPONSE "response"
#define ATTEST_MOCK_NETWORK_AUTHCHANGE "authStatusChange"
#define ATTEST_MOCK_NETWORK_RESET "resetDevice"
#define ATTEST_MOCK_NETWORK_AUTH "authDevice"
#define ATTEST_MOCK_NETWORK_ACTIVE "activeToken"

#define AUTH_SATUS_LEN 500
#define TICKET_LEN 100

typedef struct AttestDeviceMockData {
    const char* mockVersionId;
    const char* mockVersionHash;
    const char* mockDisplayVersion;
    const char* mockManuStr;
    const char* mockDeviceModel;
    const char* mockBrand;
    const char* mockPatchTag;
    const char* mockSerial;
} AttestDeviceMockData;

typedef struct AuthStatusChangeMockData {
    long long currentTime;
    const char* challenge;
    int errCode;
} AuthStatusChangeMockData;

typedef struct ResetNetMockData {
    long long currentTime;
    const char* challenge;
    int errCode;
    int responseErrCode;
} ResetNetMockData;

typedef struct AuthNetMockData {
    long long currentTime;
    const char* challenge;
    int errCode;
    const char* ticket;
    const char* uuid;
    const char* authStats;
    const char* token;
    int responseErrCode;
} AuthNetMockData;

typedef struct ActiveNetMockData {
    long long currentTime;
    const char* challenge;
    int errCode;
    int responseErrCode;
} ActiveNetMockData;

typedef struct AttestNetworkMockData {
    struct AuthStatusChangeMockData authStatusChange;
    struct ResetNetMockData resetNetMockData;
    struct AuthNetMockData authDevice;
    struct ActiveNetMockData activeToken;
} AttestNetworkMockData;

typedef struct AttestMockData {
    struct AttestDeviceMockData deviceMockData;
    struct AttestNetworkMockData NetworkMockData;
} AttestMockData;

// 初始化MOCKData
int32_t InitMockData(AttestMockData *attestMockData);

// 初始化NetWorkData
int32_t WriteNetWorkMock(AttestNetworkMockData *NetworkMockData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif