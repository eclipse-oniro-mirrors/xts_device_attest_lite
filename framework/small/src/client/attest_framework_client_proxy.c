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

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <securec.h>
#include <ohos_errno.h>
#include <ohos_types.h>
#include <registry.h>
#include <iunknown.h>
#include <samgr_lite.h>
#include <iproxy_client.h>
#include <iproxy_server.h>

#include "attest_log.h"
#include "attest_framework_define.h"
#include "devattest_interface.h"

typedef struct {
    INHERIT_CLIENT_IPROXY;
    int32_t(*StartProc)(IUnknown *iUnknown);
    int32_t(*QueryStatus)(IUnknown *iUnknown, AttestResultInfo *attestResultInfo);
} AttestClientProxy;

typedef struct {
    INHERIT_IUNKNOWNENTRY(AttestClientProxy);
} AttestClientEntry;

static AttestClientProxy *g_clientProxy;

static int32_t ReadAttestResultInfo(IpcIo *reply, AttestResultInfo **attestStatus)
{
    if ((attestStatus == NULL) || (*attestStatus == NULL) || (reply == NULL)) {
        HILOGE("[ReadAttestResultInfo] Invalid parameter.");
        return DEVATTEST_FAIL;
    }
    AttestResultInfo *attestResult = *attestStatus;
    if (!ReadInt32(reply, (int32_t *)&attestResult->authResult) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResult) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResultDetail[VERSIONID_RESULT]) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResultDetail[PATCHLEVEL_RESULT]) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResultDetail[ROOTHASH_RESULT]) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResultDetail[PCID_RESULT]) ||
        !ReadInt32(reply, (int32_t *)&attestResult->softwareResultDetail[RESERVE_RESULT]) ||
        !ReadInt32(reply, (int32_t *)&attestResult->ticketLength)) {
        HILOGE("[ReadAttestResultInfo] Failed to ReadInt32.");
        return DEVATTEST_FAIL;
    }

    size_t ticketLen = 0;
    attestResult->ticket = (char *)ReadString(reply, &ticketLen);
    if ((attestResult->ticket == NULL) || (ticketLen != (unsigned int)attestResult->ticketLength)) {
        HILOGE("[ReadAttestResultInfo] Failed to ReadString.");
        return DEVATTEST_FAIL;
    }

    return DEVATTEST_SUCCESS;
}

static int AttestClientStartProcCb(void *owner, int code, IpcIo *reply)
{
    (void)code;
    if ((owner == NULL) || (reply == NULL)) {
        HILOGE("[AttestClientStartProcCb] owner or reply is nullptr.");
        return DEVATTEST_FAIL;
    }

    int32_t *result = (int32_t *)owner;
    ReadInt32(reply, result);
    return DEVATTEST_SUCCESS;
}

static int AttestClientQueryStatusCb(void *owner, int code, IpcIo *reply)
{
    (void)code;
    if ((owner == NULL) || (reply == NULL)) {
        HILOGE("[AttestClientQueryStatusCb] owner or reply is nullptr.");
        return DEVATTEST_FAIL;
    }

    int32_t ret;
    ServiceRspMsg *respInfo = (ServiceRspMsg *)owner;

    if (!ReadInt32(reply, &respInfo->result)) {
        HILOGE("[AttestClientQueryStatusCb] Failed to ReadInt32.");
        return DEVATTEST_FAIL;
    }
    if (respInfo->result != DEVATTEST_SUCCESS) {
        HILOGE("[AttestClientQueryStatusCb] Failed to QueryStatus, result:%d.", respInfo->result);
        return DEVATTEST_FAIL;
    }
    ret = ReadAttestResultInfo(reply, &respInfo->attestResultInfo);
    return ret;
}

static int32_t StartProc(IUnknown *iUnknown)
{
    if (iUnknown == NULL) {
        return DEVATTEST_FAIL;
    }
    AttestClientProxy *proxy = (AttestClientProxy *)iUnknown;
    if (proxy == NULL) {
        HILOGE("[StartProc] Get proxy failed.");
        return DEVATTEST_FAIL;
    }
    int32_t result = DEVATTEST_SUCCESS;
    int32_t ret = proxy->Invoke((IClientProxy *)proxy, ATTEST_FRAMEWORK_MSG_PROC, NULL, &result, AttestClientStartProcCb);

    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[StartProc] Invoke failed.");
        return DEVATTEST_FAIL;
    }
    if (result != DEVATTEST_SUCCESS) {
        HILOGE("[StartProc] An error has occurred");
    }
    return DEVATTEST_SUCCESS;
}

static int32_t QueryStatus(IUnknown *iUnknown, AttestResultInfo *attestResultInfo)
{
    if (iUnknown == NULL) {
        return DEVATTEST_FAIL;
    }
    AttestClientProxy *proxy = (AttestClientProxy *)iUnknown;
    if (proxy == NULL) {
        HILOGE("[QueryStatus] Get proxy failed.");
        return DEVATTEST_FAIL;
    }
    ServiceRspMsg reply = {0};
    reply.attestResultInfo = attestResultInfo;
    int32_t ret = proxy->Invoke((IClientProxy *)proxy, ATTEST_FRAMEWORK_MSG_QUERY, NULL, &reply, AttestClientQueryStatusCb);

    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[QueryStatus] Invoke failed.");
        return DEVATTEST_FAIL;
    }
    if (reply.result != DEVATTEST_SUCCESS) {
        HILOGE("[QueryStatus] Service return failed, result = %d", reply.result);
        return DEVATTEST_FAIL;
    }
    return DEVATTEST_SUCCESS;
}

static void *CreateClient(const char *service, const char *feature, uint32 size)
{
    (void)service;
    (void)feature;
    uint32 len = size + sizeof(AttestClientEntry);
    uint8 *client = malloc(len);
    if (client == NULL) {
        return NULL;
    }
    (void)memset_s(client, len, 0, len);
    AttestClientEntry *entry = (AttestClientEntry *)&client[size];
    if (entry == NULL) {
        return NULL;
    }
    entry->ver = ((uint16)SERVER_PROXY_VER | (uint16)DEFAULT_VERSION);
    entry->ref = 1;
    entry->iUnknown.QueryInterface = IUNKNOWN_QueryInterface;
    entry->iUnknown.AddRef = IUNKNOWN_AddRef;
    entry->iUnknown.Release = IUNKNOWN_Release;
    entry->iUnknown.Invoke = NULL;
    entry->iUnknown.StartProc = StartProc;
    entry->iUnknown.QueryStatus = QueryStatus;
    return client;
}

static void DestroyClient(const char *service, const char *feature, void *iproxy)
{
    (void)service;
    (void)feature;
    if (iproxy != NULL) {
        free(iproxy);
        iproxy = NULL;
    }
}

static int32_t ModuleSamgrInitialize(void)
{
    int32_t ret = (int32_t)SAMGR_RegisterFactory(ATTEST_SERVICE, ATTEST_FEATURE, CreateClient, DestroyClient);
    if (ret != DEVATTEST_SUCCESS) {
        return DEVATTEST_FAIL;
    }
    return DEVATTEST_SUCCESS;
}

static int32_t GetModuleClientApi(void)
{
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(ATTEST_SERVICE, ATTEST_FEATURE);
    if (iUnknown == NULL) {
        return DEVATTEST_FAIL;
    }
    int32_t ret = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&g_clientProxy);
    if (ret != DEVATTEST_SUCCESS || g_clientProxy == NULL) {
        return DEVATTEST_FAIL;
    }
    return DEVATTEST_SUCCESS;
}

int32_t StartDevAttestTask(void)
{
    int32_t ret = ModuleSamgrInitialize();
    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[StartDevAttestTask] Failed to Initialize!");
        return DEVATTEST_FAIL;
    }

    ret = GetModuleClientApi();
    if ((ret != DEVATTEST_SUCCESS) || (g_clientProxy == NULL)) {
        HILOGE("[StartDevAttestTask] Get failed!");
        return DEVATTEST_FAIL;
    }

    if (g_clientProxy->StartProc == NULL) {
        HILOGE("[StartDevAttestTask] Interface not found!");
        (void)g_clientProxy->Release((IUnknown *)g_clientProxy);
        return DEVATTEST_FAIL;
    }

    ret = g_clientProxy->StartProc((IUnknown *)g_clientProxy);
    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[StartDevAttestTask] Interface execution failed!");
    }
    (void)g_clientProxy->Release((IUnknown *)g_clientProxy);
    return ret;
}

int32_t GetAttestStatus(AttestResultInfo *attestResultInfo)
{
    if (attestResultInfo == NULL) {
        return DEVATTEST_FAIL;
    }

    int32_t ret = ModuleSamgrInitialize();
    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[GetAttestStatus] Failed to Initialize!");
        return DEVATTEST_FAIL;
    }

    ret = GetModuleClientApi();
    if ((ret != DEVATTEST_SUCCESS) || (g_clientProxy == NULL)) {
        HILOGE("[GetAttestStatus] Get failed!");
        return DEVATTEST_FAIL;
    }

    if (g_clientProxy->QueryStatus == NULL) {
        HILOGE("[GetAttestStatus] Interface not found!");
        (void)g_clientProxy->Release((IUnknown *)g_clientProxy);
        return DEVATTEST_FAIL;
    }

    ret = g_clientProxy->QueryStatus((IUnknown *)g_clientProxy, attestResultInfo);
    if (ret != DEVATTEST_SUCCESS) {
        HILOGE("[GetAttestStatus] Interface execution failed!");
    }
    (void)g_clientProxy->Release((IUnknown *)g_clientProxy);
    return ret;
}