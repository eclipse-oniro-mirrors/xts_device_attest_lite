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

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <securec.h>
#include "cJSON.h"
#include "attest_utils.h"
#include "attest_utils_file.h"
#include "attest_mock.h"

#ifdef __LITEOS_M__
#include "utils_file.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

int32_t InitMockData(AttestMockData *attestMockData)
{
    // devicePara 数据
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_VERSION_ID, attestMockData->deviceMockData.mockVersionId);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_VERSION_HASH, attestMockData->deviceMockData.mockVersionHash);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_DISPLAY_VERSION,
                            attestMockData->deviceMockData.mockDisplayVersion);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_MANU_STR, attestMockData->deviceMockData.mockManuStr);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_DEVICE_MODEL, attestMockData->deviceMockData.mockDeviceModel);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_BRAND, attestMockData->deviceMockData.mockBrand);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_PATCH_TAG, attestMockData->deviceMockData.mockPatchTag);
    cJSON_AddStringToObject(root, ATTEST_MOCK_DEVICE_PARA_SERIAL, attestMockData->deviceMockData.mockSerial);

    const char *devicePara = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    
    // network_mock 数据
    AttestNetworkMockData NetworkMockData = attestMockData->NetworkMockData;
    int32_t ret = WriteNetWorkMock(&NetworkMockData);
    if (ret != ATTEST_OK) {
        return ATTEST_ERR;
    }
    
    // 写文件
    ret = WriteFile(ATTEST_MOCK_STUB_PATH, ATTEST_MOCK_TOKEN_FILE_NAME, ATTEST_MOCK_TOKEN, strlen(ATTEST_MOCK_TOKEN));
    if (ret != ATTEST_OK) {
        return ATTEST_ERR;
    }
    ret = WriteFile(ATTEST_MOCK_STUB_PATH, ATTEST_MOCK_STUB_DEVICE_NAME, devicePara, strlen(devicePara));
    if (ret != ATTEST_OK) {
        return ATTEST_ERR;
    }
    ATTEST_MEM_FREE(devicePara);
    return ret;
}

static int32_t BuildMockNetworkParaChallenge(cJSON ** networkParaChallenge,
    long long currentTime, char* challenge, int errCode)
{
    if (networkParaChallenge == NULL || challenge == NULL) {
        return ATTEST_ERR;
    }
    cJSON *authStatusChallenge = cJSON_CreateObject();
    cJSON_AddNumberToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_CURRENTTIME, currentTime);
    cJSON_AddStringToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, challenge);
    cJSON_AddNumberToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_ERRCODE, errCode);
                            NetworkMockData->authStatusChange.errCode);
    cJSON_AddItemToObject(&networkParaChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, authStatusChallenge);
    return ATTEST_OK;
}


static int32_t WriteAuthChangeMock(AttestNetworkMockData *NetworkMockData, cJSON ** netWorkMockJson)
{
    if (netWorkMockJson == NULL) {
        return ATTEST_ERR;
    }

    cJSON *authStatusChange = cJSON_CreateObject();
    int32_t ret = BuildMockNetworkParaChallenge(&authStatusChange,
        NetworkMockData->authStatusChange.currentTime,
        NetworkMockData->authStatusChange.challenge,
        NetworkMockData->authStatusChange.errCode);
    if (ret != ATTEST_OK) {
        cJSON_Delete(authStatusChange);
        return ATTEST_ERR;
    }

    cJSON_AddItemToObject(&netWorkMockJson, ATTEST_MOCK_NETWORK_AUTHCHANGE, authStatusChange);
}

static int32_t WriteResetMock(AttestNetworkMockData *NetworkMockData, cJSON ** netWorkMockJson)
{
    if (netWorkMockJson == NULL) {
        return ATTEST_ERR;
    }

    cJSON *resetDevice = cJSON_CreateObject();
    cJSON *resetResponse = cJSON_CreateObject();
    ret = BuildMockNetworkParaChallenge(&resetDevice,
        NetworkMockData->resetNetMockData.currentTime,
        NetworkMockData->resetNetMockData.challenge,
        NetworkMockData->resetNetMockData.errCode);
    if (ret != ATTEST_OK) {
        cJSON_Delete(resetDevice);
        cJSON_Delete(resetResponse);
        return ATTEST_ERR;
    }
    cJSON_AddNumberToObject(resetResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->resetNetMockData.responseErrCode);
    cJSON_AddItemToObject(resetDevice, ATTEST_MOCK_NETWORK_RESPONSE, resetResponse);

    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_RESET, resetDevice);
}

static int32_t WriteAuthMock(AttestNetworkMockData *NetworkMockData, cJSON ** netWorkMockJson)
{
    if (netWorkMockJson == NULL) {
        return ATTEST_ERR;
    }

    cJSON *authDevice = cJSON_CreateObject();
    cJSON *authResponse = cJSON_CreateObject();
    int32_t ret = BuildMockNetworkParaChallenge(&authDevice,
        NetworkMockData->authDevice.currentTime,
        NetworkMockData->authDevice.challenge,
        NetworkMockData->authDevice.errCode);
    if (ret != ATTEST_OK) {
        cJSON_Delete(authDevice);
        cJSON_Delete(authResponse);
        return ATTEST_ERR;
    }
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_TICKET, NetworkMockData->authDevice.ticket);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_UUID, NetworkMockData->authDevice.uuid);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_AUTHSTATS, NetworkMockData->authDevice.authStats);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_TOKEN, NetworkMockData->authDevice.token);
    cJSON_AddNumberToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->authDevice.responseErrCode);
    cJSON_AddItemToObject(authDevice, ATTEST_MOCK_NETWORK_RESPONSE, authResponse);

    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_AUTH, authDevice);
}

static int32_t WriteActiveMock(AttestNetworkMockData *NetworkMockData, cJSON ** netWorkMockJson)
{
    if (netWorkMockJson == NULL) {
        return ATTEST_ERR;
    }

    cJSON *activeToken = cJSON_CreateObject();
    cJSON *activeResponse = cJSON_CreateObject();
    int32_t ret = BuildMockNetworkParaChallenge(&activeToken,
        NetworkMockData->activeToken.currentTime,
        NetworkMockData->activeToken.challenge,
        NetworkMockData->activeToken.errCode);
    if (ret != ATTEST_OK) {
        cJSON_Delete(activeToken);
        cJSON_Delete(activeResponse);
        return ATTEST_ERR;
    }
    cJSON_AddNumberToObject(activeResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->activeToken.responseErrCode);
    cJSON_AddItemToObject(activeToken, ATTEST_MOCK_NETWORK_RESPONSE, activeResponse);

    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_ACTIVE, activeToken);
}

int32_t WriteNetWorkMock(AttestNetworkMockData *NetworkMockData)
{
    cJSON *netWorkMockJson = cJSON_CreateObject();
    int32_t ret = WriteAuthChangeMock(NetworkMockData, &netWorkMockJson);
    if (ret != ATTEST_OK) {
        cJSON_Delete(netWorkMockJson);
        return ATTEST_ERR;
    }

    ret = WriteResetMock(NetworkMockData, &netWorkMockJson);
    if (ret != ATTEST_OK) {
        cJSON_Delete(netWorkMockJson);
        return ATTEST_ERR;
    }

    ret = WriteAuthMock(NetworkMockData, &netWorkMockJson);
    if (ret != ATTEST_OK) {
        cJSON_Delete(netWorkMockJson);
        return ATTEST_ERR;
    }

    ret = WriteActiveMock(NetworkMockData, &netWorkMockJson);
    if (ret != ATTEST_OK) {
        cJSON_Delete(netWorkMockJson);
        return ATTEST_ERR;
    }

    const char *networkPara = cJSON_PrintUnformatted(netWorkMockJson);
    cJSON_Delete(netWorkMockJson);
    int32_t ret = WriteFile(ATTEST_MOCK_STUB_PATH, ATTEST_MOCK_STUB_NETWORK_NAME,
                            networkPara, strlen(networkPara));
    if (ret != ATTEST_OK) {
        return ATTEST_ERR;
    }

    ATTEST_MEM_FREE(networkPara);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */