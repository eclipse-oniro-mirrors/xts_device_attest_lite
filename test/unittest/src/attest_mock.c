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

int32_t WriteNetWorkMock(AttestNetworkMockData *NetworkMockData)
{
    cJSON *netWorkMockJson = cJSON_CreateObject();
    // Network 数据
    // authStatusChange
    cJSON *authStatusChange = cJSON_CreateObject();
    cJSON *authStatusChallenge = cJSON_CreateObject();
    cJSON_AddNumberToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_CURRENTTIME,
                            (NetworkMockData->authStatusChange.currentTime));
    cJSON_AddStringToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE,
                            NetworkMockData->authStatusChange.challenge);
    cJSON_AddNumberToObject(authStatusChallenge, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->authStatusChange.errCode);
    cJSON_AddItemToObject(authStatusChange, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, authStatusChallenge);

    // resetDevice
    cJSON *resetDevice = cJSON_CreateObject();
    cJSON *resetResponse = cJSON_CreateObject();
    cJSON *resetChallenge = cJSON_CreateObject();
    cJSON_AddNumberToObject(resetResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->resetNetMockData.responseErrCode);
    cJSON_AddNumberToObject(resetChallenge, ATTEST_MOCK_NETWORK_PARA_CURRENTTIME,
                            (NetworkMockData->resetNetMockData.currentTime));
    cJSON_AddStringToObject(resetChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE,
                            NetworkMockData->resetNetMockData.challenge);
    cJSON_AddNumberToObject(resetChallenge, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->resetNetMockData.errCode);
    cJSON_AddItemToObject(resetDevice, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, resetChallenge);
    cJSON_AddItemToObject(resetDevice, ATTEST_MOCK_NETWORK_RESPONSE, resetResponse);

    // authDevice
    cJSON *authDevice = cJSON_CreateObject();
    cJSON *authResponse = cJSON_CreateObject();
    cJSON *authChallenge = cJSON_CreateObject();
    cJSON_AddNumberToObject(authChallenge, ATTEST_MOCK_NETWORK_PARA_CURRENTTIME,
                            (NetworkMockData->authDevice.currentTime));
    cJSON_AddStringToObject(authChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, NetworkMockData->authDevice.challenge);
    cJSON_AddNumberToObject(authChallenge, ATTEST_MOCK_NETWORK_PARA_ERRCODE, NetworkMockData->authDevice.errCode);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_TICKET, NetworkMockData->authDevice.ticket);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_UUID, NetworkMockData->authDevice.uuid);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_AUTHSTATS, NetworkMockData->authDevice.authStats);
    cJSON_AddStringToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_TOKEN, NetworkMockData->authDevice.token);
    cJSON_AddNumberToObject(authResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->authDevice.responseErrCode);
    cJSON_AddItemToObject(authDevice, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, authChallenge);
    cJSON_AddItemToObject(authDevice, ATTEST_MOCK_NETWORK_RESPONSE, authResponse);

    // activeToken
    cJSON *activeToken = cJSON_CreateObject();
    cJSON *activeChallenge = cJSON_CreateObject();
    cJSON *activeResponse = cJSON_CreateObject();
    cJSON_AddNumberToObject(activeResponse, ATTEST_MOCK_NETWORK_PARA_ERRCODE,
                            NetworkMockData->activeToken.responseErrCode);
    cJSON_AddNumberToObject(activeChallenge, ATTEST_MOCK_NETWORK_PARA_CURRENTTIME,
                            (NetworkMockData->activeToken.currentTime));
    cJSON_AddStringToObject(activeChallenge, ATTEST_MOCK_NETWORK_PARA_CHALLENGE,
                            NetworkMockData->activeToken.challenge);
    cJSON_AddNumberToObject(activeChallenge, ATTEST_MOCK_NETWORK_PARA_ERRCODE, NetworkMockData->activeToken.errCode);

    cJSON_AddItemToObject(activeToken, ATTEST_MOCK_NETWORK_PARA_CHALLENGE, activeChallenge);
    cJSON_AddItemToObject(activeToken, ATTEST_MOCK_NETWORK_RESPONSE, activeResponse);

    // 添加到最外层的json中
    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_AUTHCHANGE, authStatusChange);
    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_RESET, resetDevice);
    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_AUTH, authDevice);
    cJSON_AddItemToObject(netWorkMockJson, ATTEST_MOCK_NETWORK_ACTIVE, activeToken);
    const char *networkPara = cJSON_PrintUnformatted(netWorkMockJson);
    cJSON_Delete(netWorkMockJson);
    int32_t ret = WriteFile(ATTEST_MOCK_STUB_PATH, ATTEST_MOCK_STUB_NETWORK_NAME, networkPara, strlen(networkPara));
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