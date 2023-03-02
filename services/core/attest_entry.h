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

#ifndef ATTEST_ENTRY_H
#define ATTEST_ENTRY_H

#include <stdint.h>
#include "devattest_msg_def.h"

#ifdef __LITEOS_M__
#include "cmsis_os2.h"
#include "ohos_init.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define LITEOS_M_STACK_SIZE           8192

#define SOFTWARE_RESULT_DETAIL_SIZE   5
#define MAX_ATTEST_RESULT_SIZE        (SOFTWARE_RESULT_DETAIL_SIZE + 2)

#define ATTEST_TASK_THREAD_NAME       "AttestSdk"

#define ATTEST_CALLBACK_THREAD_NAME   "AttestAuth"

typedef enum {
    SOFTWARE_RESULT_VERSIONID,
    SOFTWARE_RESULT_PATCHLEVEL,
    SOFTWARE_RESULT_ROOTHASH,
    SOFTWARE_RESULT_PCID,
    SOFTWARE_RESULT_RESERVE,
} SOFTWARE_RESULT_DETAIL_TYPE;

int32_t AttestTask(void);

int32_t EntryGetAttestStatus(AttestResultInfo* attestResultInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

