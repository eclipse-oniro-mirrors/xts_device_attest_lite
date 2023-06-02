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

#ifdef __LITEOS_M__
#include "hi_mdm.h"
#endif

#include "attest_type.h"
#include "attest_utils_log.h"
#include "attest_adapter_oem.h"
#include "attest_adapter_os.h"
#include "attest_adapter_mock.h"
#include "attest_adapter.h"

#ifdef __LITEOS_M__
#define HI_NV_XTS_DEV_ATTEST_NET 0x60
#define HI_NV_NET_SIZE 164

typedef struct {
    uint8_t nv_dev_attest_net[HI_NV_NET_SIZE];
} hi_nv_xts_dev_attest_net_cfg;
#endif

// 是否存在重置标记
bool AttestIsResetFlagExist(void)
{
    return OEMIsResetFlagExist();
}
// 创建重置标记

int32_t AttestCreateResetFlag(void)
{
    return OEMCreateResetFlag();
}
// 写入认证结果
int32_t AttestWriteAuthStatus(const char* data, uint32_t len)
{
    return OEMWriteAuthStatus(data, len);
}

// 读取认证结果
int32_t AttestReadAuthStatus(char* buffer, uint32_t bufferLen)
{
    return OEMReadAuthStatus(buffer, bufferLen);
}

// 读取认证结果长度
int32_t AttestGetAuthStatusFileSize(uint32_t* len)
{
    return OEMGetAuthStatusFileSize(len);
}

// 读取凭据
int32_t AttestReadTicket(TicketInfo* ticketInfo)
{
    return OEMReadTicket(ticketInfo);
}

// 写入凭据
int32_t AttestWriteTicket(const TicketInfo* ticketInfo)
{
    return OEMWriteTicket(ticketInfo);
}

int32_t AttestSetParameter(const char *key, const char *value)
{
    return OsSetParameter(key, value);
}

int32_t AttestGetParameter(const char *key, const char *def, char *value, uint32_t len)
{
    return OsGetParameter(key, def, value, len);
}

// 读取网络配置信息
#ifdef __LITEOS_M__
static int32_t CopyNVData(char *dst, int32_t dstLen, unsigned char *src, int32_t srcLen)
{
    if (dst == NULL || src == NULL) {
        ATTEST_LOG_ERROR("[CopyNVData] input paramter wrong");
        return ATTEST_ERR;
    }
    int32_t dataLen = (dstLen < srcLen) ? dstLen : srcLen;
    for (int32_t i = 0; i < dataLen; i++) {
        dst[i] = (char)src[i];
    }
    return ATTEST_OK;
}

int32_t AttestReadNetworkConfig(char* buffer, uint32_t bufferLen)
{
    hi_nv_xts_dev_attest_net_cfg nv_net = { 0 };
    int32_t ret = hi_nv_read(HI_NV_XTS_DEV_ATTEST_NET, (void*)&nv_net, sizeof(nv_net), 0);
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestReadNetworkConfig] hi_nv_read failed");
        return ATTEST_ERR;
    }
    return CopyNVData(buffer, bufferLen, nv_net.nv_dev_attest_net, sizeof(hi_nv_xts_dev_attest_net_cfg));
}

int32_t AttestWriteNetworkConfig(const char* data, uint32_t len)
{
    if (data == NULL || len > HI_NV_NET_SIZE) {
        ATTEST_LOG_ERROR("[AttestWriteNetworkConfig] invalid parameter");
        return ATTEST_ERR;
    }
    hi_nv_xts_dev_attest_net_cfg nv_net = { 0 };
    int32_t ret = CopyNVData(nv_net.nv_dev_attest_net, sizeof(hi_nv_xts_dev_attest_net_cfg), data, len);
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestWriteNetworkConfig] copy data to NV failed");
        return ATTEST_ERR;
    }
    ret = hi_nv_write(HI_NV_XTS_DEV_ATTEST_NET, (void*)&nv_net, sizeof(nv_net), 0);
    if (ret != ATTEST_OK) {
        ATTEST_LOG_ERROR("[AttestWriteNetworkConfig] nv write failed");
        return ATTEST_ERR;
    }
    return ATTEST_OK;
}
#else
int32_t AttestReadNetworkConfig(char* buffer, uint32_t bufferLen)
{
    return OEMReadNetworkConfig(buffer, bufferLen);
}
#endif

int32_t AttestWriteNetworkConfig(const char* data, uint32_t len)
{
    return OEMWriteNetworkConfig(data, len);
}

int32_t AttestWriteAuthResultCode(const char* data, uint32_t len)
{
    return OEMWriteAuthResultCode(data, len);
}

int32_t AttestReadAuthResultCode(char* buffer, uint32_t bufferLen)
{
    return OEMReadAuthResultCode(buffer, bufferLen);
}
