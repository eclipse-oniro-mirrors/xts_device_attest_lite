/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

#include "attest_type.h"
#include "attest_entry.h"
#include "devattest_interface.h"

int32_t StartDevAttestTask(void)
{
    osThreadAttr_t attr = {0};
    attr.stack_size = LITEOS_M_STACK_SIZE;
    attr.priority = osPriorityNormal;
    attr.name = ATTEST_TASK_THREAD_NAME;
    if (osThreadNew((osThreadFunc_t)AttestTask, NULL, &attr) == NULL) {
        return DEVATTEST_FAIL;
    }
    return DEVATTEST_SUCCESS;
}

int32_t GetAttestStatus(AttestResultInfo* attestResultInfo)
{
    if (attestResultInfo == NULL) {
        return DEVATTEST_FAIL;
    }
    int *intArray = NULL;
    int arraySize = 0;
    int ticketLength = 0;
    char *ticketStr = NULL;
    int ret = QueryAttest(&intArray, &arraySize, &ticketStr, &ticketLength);
    if (ret != DEVATTEST_SUCCESS) {
        printf("[DEVATTEST][GetAttestStatus] failed!");
        return ret;
    }

    do {
        int *authResult = &attestResultInfo->authResult;
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_AUTH, authResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
        int *softwareResult = &attestResultInfo->softwareResult;
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_SOFTWARE, softwareResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
        int *versionIdResult = &attestResultInfo->softwareResultDetail[VERSIONID_RESULT];
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_VERSIONID, versionIdResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
        int *patchResult = &attestResultInfo->softwareResultDetail[PATCHLEVEL_RESULT];
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_PATCHLEVEL, patchResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
        int *roothashResult = &attestResultInfo->softwareResultDetail[ROOTHASH_RESULT];
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_ROOTHASH, roothashResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
        int *pcidResult = &attestResultInfo->softwareResultDetail[PCID_RESULT];
        if (AttestReadInt32(intArray, arraySize, ATTEST_RESULT_PCID, pcidResult) != DEVATTEST_SUCCESS) {
            ret = DEVATTEST_FAIL;
            break;
        }
    } while (0);
    attestResultInfo->softwareResultDetail[PCID_RESULT] = ATTEST_RESULT_INIT;
    if (ret != DEVATTEST_SUCCESS) {
        printf("[DEVATTEST][GetAttestStatus] read failed!");
        return DEVATTEST_FAIL;
    }

    if (ticketStr != NULL) {
        attestResultInfo->ticket = ticketStr;
        attestResultInfo->ticketLength = ticketLength;
    }
    return ret;
}

void ThreadMain(void)
{

}

APP_FEATURE_INIT(ThreadMain);