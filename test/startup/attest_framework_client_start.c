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
#include <stdlib.h>
#include <unistd.h>

#include "devattest_interface.h"

#define ATTEST_QUERY_INTERVAL 5

int main(void)
{
    int32_t ret = StartDevAttestTask();
    if (ret == DEVATTEST_SUCCESS) {
        // delay query to make sure AttestTask
        sleep(ATTEST_QUERY_INTERVAL); // 延后5s再查询

        AttestResultInfo attestResultInfo = { 0 };
        attestResultInfo.ticket = NULL;
        
        ret = GetAttestStatus(&attestResultInfo);
        if (ret != DEVATTEST_SUCCESS) {
            printf("[CLIENT MAIN] wrong.\n");
        }

        if (attestResultInfo.ticket != NULL) {
            printf("[CLIENT MAIN] auth:%d, software:%d, ticket:%s\n",
                attestResultInfo.authResult, attestResultInfo.softwareResult, attestResultInfo.ticket);

            free(attestResultInfo.ticket);
            attestResultInfo.ticket = NULL;
        }
    }
    printf("[CLIENT MAIN] end.\n");
    while (1) {
        pause();
    }
    return 0;
}
