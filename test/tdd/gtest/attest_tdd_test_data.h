/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
#ifndef ATTEST_TDD_TEST_DATA_H
#define ATTEST_TDD_TEST_DATA_H
const char* ATTEST_RESET_EXPECT_CHAP = "f646a2292338c342765f55e86948b4b3693a559b1e3a8bd62b2dff1076380ec9";
const int64_t ATTEST_RESET_EXPECT_CHAP_TIME = 1118038129;
const char* ATTEST_RESET_EXPECT_TOKEN = "4XTj7KhYINoDypTG1h5wVP2mByJ+AFXu1siWeuUNVd4=";

const char* ATTEST_REST_ERROR_EXPECT_RESULT = "{\"errcode\":15003}";

const char* ATTEST_AUTH_EXPECT_RESULT = "{  \
\"authStats\":\".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSIsImV4cGlyZVRpbWUiOjE2ODMwNDIyNTEyOTEsImt \
pdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRhaWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgs \
InBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3O \
UEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQyIsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhLXdla \
S9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAvT3Blbkhhcm1vbnkgMi4zIGJldGEvZGVidW \
cifQ.\", \
\"errcode\":0, \
\"ticket\":\"vbVYmHYmc5i/jiEVITvDOHzevJgU/Ghe\", \
\"token\":\"XwTzVFdKzX/L8rJmDuqHnDlipM9QBT1d\", \
\"uuid\":\"cb8cf67a-2c3e-44d6-b7bf-3eeed7724a55\" \
}";
const char* ATTEST_AUTH_CHAP = "65050587a92a6f5bfddad5b5b05a3562bd1be59727b28eff155dd43b188e4010";
const int64_t ATTEST_AUTH_CHAP_TIME = 1118038447;
const char* ATTEST_AUTH_GEN_TOKEN = "CzuwaTMyRGcHl4pMBYkRN49G8Z0CXv+Mz/mzcU2NEnE=";

const char* ATTEST_ACTIVE_EXPECT_RESULT = "{\"errcode\":0}";
const char* ATTEST_ACTIVE_GEN_TOKEN = "HBDVx6ofSCNndqodOwX4YR3Les2PDP6NSsGV66uu4Jk=";
const char* ATTEST_ACTIVE_CHAP = "7bf570910d3e1fcdf3959e10ffddc5c2777164a4a2f55d9fd65b1896f65b3f97";
const int64_t ATTEST_ACTIVE_CHAP_TIME = 1118038882;

const char* ATTEST_STATUS = ".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSIsImV4cGlyZVRpbWUi \
OjE2ODMwNDIyNTEyOTEsImtpdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRhaWwiOnsicGF0Y2hMZXZlb \
FJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc3VsdCI6MzAwMDJ9LCJ1ZGlkIj \
oiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQyIsInZlcnNpb25JZCI6ImRlZmF1bHQ \
vaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAvT3Blb \
khhcm1vbnkgMi4zIGJldGEvZGVidWcifQ.";
const char* ATTEST_TICKET = "vbVYmHYmc5i/jiEVITvDOHzevJgU/Ghe";
const char* ATTEST_VERSIONID = "default/hua-wei/kemin/default/OpenHarmony-4.0.3.2(Canary1)/ohos/max/10 \
/OpenHarmony 2.3 beta/debug";
const char* ATTEST_AUTHTYP = "TOKEN_ENABLE";
const int64_t ATTEST_EXPIRRTIME = -584928741;
const int32_t ATTEST_HARDWARERESULT = 0;
             
#endif
