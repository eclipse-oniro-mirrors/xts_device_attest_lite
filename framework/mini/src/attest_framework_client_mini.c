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

static int32_t CopyAttestResult(int32_t *resultArray, AttestResultInfo *attestResultInfo)
{
    if (resultArray == NULL) {
        return DEVATTEST_FAIL;
    }
    int32_t *head = resultArray;
    attestResultInfo->authResult_ = *head;
    head++;
    attestResultInfo->softwareResult_ = *head;
    for (int i = 0; i < SOFTWARE_RESULT_DETAIL_SIZE; i++) {
        attestResultInfo.softwareResultDetail_[i] = *(++head);
    }
    return DEVATTEST_SUCCESS;
}

int32_t GetAttestStatus(AttestResultInfo* attestResultInfo)
{
    if (attestResultInfo == NULL) {
        return DEVATTEST_FAIL;
    }
    int32_t resultArraySize = MAX_ATTEST_RESULT_SIZE * sizeof(int32_t);
    int32_t *resultArray = (int32_t *)malloc(resultArraySize);
    if (resultArray == NULL) {
        HILOGE("malloc resultArray failed");
        return DEVATTEST_FAIL;
    }
    (void)memset_s(resultArray, resultArraySize, 0, resultArraySize);
    int32_t ticketLenght = 0;
    char* ticketStr = NULL;
    int32_t ret = DEVATTEST_SUCCESS;
    do {
        ret = QueryAttest(&resultArray, MAX_ATTEST_RESULT_SIZE, &ticketStr, &ticketLenght);
        if (ret != DEVATTEST_SUCCESS) {
            HILOGE("QueryAttest failed");
            break;
        }
        if (ticketStr == NULL || ticketLenght == 0) {
            HILOGE("get ticket failed");
            ret = DEVATTEST_FAIL;
            break;
        }
        attestResultInfo->ticketLength_ = ticketLenght;
        attestResultInfo->ticket_ = ticketStr;
        ret = CopyAttestResult(resultArray,  attestResultInfo);
        if (ret != DEVATTEST_SUCCESS) {
            HILOGE("copy attest result failed");
            break;
        }
    } while (0);
    if (ret != DEVATTEST_SUCCESS && ticketStr != NULL) {
        free(ticketStr);
        ticketStr = NULL;
    }
    resultArray = NULL;
    HILOGI("GetAttestStatus end success");
    return ret;
}

void ThreadMain(void)
{

}

APP_FEATURE_INIT(ThreadMain);