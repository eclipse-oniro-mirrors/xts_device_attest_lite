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

#include "attest_type.h"
#include "attest_utils_log.h"
#include "attest_utils_timer.h"
#include "attest_service.h"
#include "attest_entry.h"

static ATTEST_TIMER_ID g_ProcAttestTimerId = NULL;

#ifdef __LITEOS_M__

static osThreadId_t g_AttestTaskId = NULL;
typedef void(*AttestTaskCallback)(void);
// L0启动
static int CreateAttestThread(void(*run)(void *), void *argv, const char *name, osThreadId_t *serverTaskId)
{
    osThreadAttr_t attr = {0};
    attr.stack_size = LITEOS_M_STACK_SIZE;
    attr.priority = osPriorityNormal;
    attr.name = name;
    *serverTaskId = osThreadNew((osThreadFunc_t)run, argv, &attr);
    if (*serverTaskId == NULL) {
        ATTEST_LOG_ERROR("[CreateAttestThread] osThreadNew fail.");
        return ATTEST_ERR;
    }
    return ATTEST_OK;
}

static void AttestTaskThread(void *argv)
{
    AttestTaskCallback cb = (AttestTaskCallback)argv;
    cb();
    return;
}

static void AttestAuthCallBack(void *argv)
{
    (void)argv;
    if (g_AttestTaskId != NULL) {
        const char *pthreadName = osThreadGetName(g_AttestTaskId);
        if ((pthreadName != NULL) && (strcmp(pthreadName, ATTEST_CALLBACK_THREAD_NAME) == 0)) {
            osThreadTerminate(g_AttestTaskId);
            ATTEST_LOG_ERROR("[AttestAuthCallBack] osThreadTerminate");
        }
        g_AttestTaskId = NULL;
    }
    int ret = CreateAttestThread(AttestTaskThread,
        (void *)ProcAttest,
        ATTEST_CALLBACK_THREAD_NAME,
        &g_AttestTaskId);
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestAuthCallBack] CreateAttestThread return failed");
    }
    return;
}
#else
static void AttestAuthCallBack(void *argv)
{
    (void)argv;
    int32_t ret = ProcAttest();
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestAuthCallBack] Proc failed ret = %d.", ret);
    }
    return;
}
#endif

int32_t AttestTask(void)
{
    ATTEST_LOG_INFO("[AttestTask] Begin.");
    // 执行主流程代码
    int32_t ret = ProcAttest();
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestTask] Proc failed ret = %d.", ret);
    }

    // 创建主流程定时器
    ret = AttestCreateTimerTask(ATTEST_TIMER_TYPE_PERIOD,
        EXPIRED_INTERVAL,
        &AttestAuthCallBack,
        NULL,
        &g_ProcAttestTimerId);
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestTask] Create Periodic TimerTask return ret = %d.", ret);
    }
    ATTEST_LOG_INFO("[AttestTask] End.");
    return ret;
}

static int32_t CopyAttestResult(int32_t *resultArray, AttestResultInfo *attestResultInfo)
{
    if (resultArray == NULL) {
        return DEVATTEST_FAIL;
    }
    int32_t *head = resultArray;
    attestResultInfo->authResult = *head;
    head++;
    attestResultInfo->softwareResult = *head;
    for (int i = 0; i < SOFTWARE_RESULT_DETAIL_SIZE; i++) {
        attestResultInfo->softwareResultDetail[i] = *(++head);
    }
    return DEVATTEST_SUCCESS;
}

int32_t EntryGetAttestStatus(AttestResultInfo* attestResultInfo)
{
    if (attestResultInfo == NULL) {
        return DEVATTEST_FAIL;
    }
    int32_t resultArraySize = MAX_ATTEST_RESULT_SIZE * sizeof(int32_t);
    int32_t *resultArray = (int32_t *)malloc(resultArraySize);
    if (resultArray == NULL) {
        ATTEST_LOG_ERROR("malloc resultArray failed");
        return DEVATTEST_FAIL;
    }
    (void)memset_s(resultArray, resultArraySize, 0, resultArraySize);
    int32_t ticketLength = 0;
    char* ticketStr = NULL;
    int32_t ret = DEVATTEST_SUCCESS;
    do {
        ret = QueryAttestStatus(&resultArray, MAX_ATTEST_RESULT_SIZE, &ticketStr, &ticketLength);
        if (ret != DEVATTEST_SUCCESS) {
            ATTEST_LOG_ERROR("QueryAttest failed");
            break;
        }
        ret = CopyAttestResult(resultArray,  attestResultInfo);
        if (ret != DEVATTEST_SUCCESS) {
            ATTEST_LOG_ERROR("copy attest result failed");
            break;
        }
        attestResultInfo->ticketLength = ticketLength;
        attestResultInfo->ticket = ticketStr;
    } while (0);
    free(resultArray);
    resultArray = NULL;
    ATTEST_LOG_INFO("GetAttestStatus end success");
    return ret;
}