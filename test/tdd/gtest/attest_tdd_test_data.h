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
#ifndef ATTEST_TDD_TEST_DATA
#define ATTEST_TDD_TEST_DATA

#define ATTEST_RESET_CHALLENGE_FIRST_MSG   "2,0"
#define ATTEST_RESET_CHALLENGE_SECOND_MSG  "1"
#define ATTEST_RESET_CHALLENGE_THIRD_MSG   "6,9,9,2,1,3,9,1,9,1,1,1,1,1,1,3,5,3,1,5,5,5,9,5,5,5,5,5,5,5,9,5,5,5,5,5,5,1,5,5,1,5,5, \
    5,5,5,9,5,9,5,5,5,5,9,5,5,5,9,4,1,5,9,5,9,1,5,5,9,5,1,1,1,4,4,5,5,5,5,4,1,9,5,3,4,3,9,1,1,1,1,1,1,8,1,1,1,3,5,4,5,5,4,5,5,4,5,5, \
    4,5,5,5,4,3,1,1,1,9,1,1,1,3,5,4,1,0"
#define ATTEST_RESET_EXPECT_CHALLENGE      "f646a2292338c342765f55e86948b4b3693a559b1e3a8bd62b2dff1076380ec9"
#define ATTEST_RESET_EXPECT_CHALLENGE_TIME (1118038129)
#define ATTEST_RESET_EXPECT_TOKEN          "4XTj7KhYINoDypTG1h5wVP2mByJ+AFXu1siWeuUNVd4="

#define ATTEST_REST_ERROR_FIRST_MSG        "2,0"
#define ATTEST_REST_ERROR_SECOND_MSG       "5,0"
#define ATTEST_REST_ERROR_THIRD_MSG        "6,2,1,2,1,3,1,1,1,9,1,1,1,3,5,4,5,4,4,5,1,5"
#define ATTEST_REST_ERROR_EXPECT_RESULT    "{\"errcode\":15003}"

#define ATTEST_AUTH_FIST_MSG               "2,0"
#define ATTEST_AUTH_SECOND_MSG             "1,1,4"
#define ATTEST_AUTH_THIRD_MSG              "6,1,2,2,1,3,9,1,1,1,8,1,9,1,1,3,5,3,4,1,1,7,1,1,8,8,1,8,1,8,1,1,8,1,4,7,1,1,1,7,6,7,1,1,8,8,1,8, \
7,1,1,9,8,7,5,7,1,8,8,8,4,8,7,8,4,8,7,8,8,7,7,8,8,7,1,7,1,8,5,9,7,1,1,9,8,8,1,9,8,8,1,7,1,6,5,7,6,7,1,7,6,7,1,7,8,6,1,7,8,6,1,7,1,1,1,1,7,6,1, \
9,7,1,1,1,8,7,5,8,4,4,1,7,1,7,1,9,1,8,5,8,8,7,1,8,1,8,1,1,8,1,4,7,1,1,1,7,6,6,1,7,1,1,1,9,5,5,1,1,7,1,1,9,1,8,8,9,8,7,4,9,7,8,6,9,8,8,1,9,8,1,1, \
7,1,1,1,9,7,7,4,8,5,1,7,9,8,9,1,9,7,7,1,9,5,8,1,1,6,7,5,7,1,6,1,7,6,1,1,7,1,6,1,9,8,8,8,9,8,7,4,9,7,8,1,7,1,7,1,7,6,6,1,7,6,7,1,9,5,5,4,8,7,7,1, \
9,7,7,1,9,5,8,1,1,6,7,5,7,1,6,1,7,6,1,1,7,1,9,1,9,1,7,1,9,5,5,7,9,7,7,1,9,5,8,1,1,6,7,5,7,1,6,1,7,6,7,5,7,6,7,4,9,7,1,1,7,1,1,1,7,6,7,6,7,8,8,4,7, \
8,7,5,7,8,6,1,8,8,8,1,7,4,8,4,7,8,8,5,8,1,8,7,8,1,8,1,7,1,1,1,8,1,7,5,8,6,6,1,7,6,7,7,7,6,8,5,7,4,7,5,7,6,8,1,7,4,7,6,7,6,7,6,8,1,8,6,8,1,1,5,7,1,8, \
1,8,1,7,1,7,1,9,1,9,1,7,1,9,5,5,7,9,6,7,5,7,1,8,1,9,1,7,4,9,7,8,1,9,7,8,1,7,8,1,1,9,8,5,1,9,8,4,1,9,1,5,1,9,8,9,1,1,8,1,4,7,4,5,1,9,8,5,7,8,8,7,1,9,5,5,5,7,8,8,1,7,6"
#define ATTEST_AUTH_EXPECT_RESULT          "{  \
    \"authStats\":\".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSIsImV4cGlyZVRpbWUiOjE2ODMwNDIyNTEyOTEsImtpdFBvbGljeSI6W10sInNvZnR3YXJl \
    UmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRhaWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZ \
    lcnNpb25JZFJlc3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQyIsInZlcnNpb25JZCI6I \
    mRlZmF1bHQvaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAvT3Blbkhhcm1vbnkgMi4zIGJldGEvZGVidWcifQ.\", \
    \"errcode\":0, \
    \"ticket\":\"vbVYmHYmc5i/jiEVITvDOHzevJgU/Ghe\", \
    \"token\":\"XwTzVFdKzX/L8rJmDuqHnDlipM9QBT1d\", \
    \"uuid\":\"cb8cf67a-2c3e-44d6-b7bf-3eeed7724a55\" \
    }"
#define ATTEST_AUTH_CHALLENGE             "65050587a92a6f5bfddad5b5b05a3562bd1be59727b28eff155dd43b188e4010"
#define ATTEST_AUTH_CHALLENGE_TIME        (1118038447)
#define ATTEST_AUTH_GEN_TOKEN              "CzuwaTMyRGcHl4pMBYkRN49G8Z0CXv+Mz/mzcU2NEnE="

#define ATTEST_ACTIVE_FIRST_MSG            "2,0"
#define ATTEST_ACTIVE_SECOND_MSG           "1"
#define ATTEST_ACTIVE_THIRD_MSG            "6,2,1,2,1,3,1,1,1,9,1,1,1,3,5,4,1,0"
#define ATTEST_ACTIVE_EXPECT_RESULT        "{\"errcode\":0}"
#define ATTEST_ACTIVE_GEN_TOKEN            "HBDVx6ofSCNndqodOwX4YR3Les2PDP6NSsGV66uu4Jk="
#define ATTEST_ACTIVE_CHALLENGE            "7bf570910d3e1fcdf3959e10ffddc5c2777164a4a2f55d9fd65b1896f65b3f97"
#define ATTEST_ACTIVE_CHALLENGE_TIME       (1118038882)

#define ATTEST_STATUS                      ".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSIsImV4cGlyZVRpbWUiOjE2ODMwNDIyNTEyOTEsImtp \
    dFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRhaWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLC \
    Jyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQy  \
    M0FCNENCRjRERjk4MjYxQyIsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAvT3Blb \
    khhcm1vbnkgMi4zIGJldGEvZGVidWcifQ."
#define ATTEST_TICKET                      "vbVYmHYmc5i/jiEVITvDOHzevJgU/Ghe"
#define ATTEST_VERSIONID                   "default/hua-wei/kemin/default/OpenHarmony-4.0.3.2(Canary1)/ohos/max/10/OpenHarmony 2.3 beta/debug"
#define ATTEST_AUTHTYP                     "TOKEN_ENABLE"
#define ATTEST_EXPIRRTIME                 (-584928741)
#define ATTEST_HARDWARERESULT             (0)
             
#endif
