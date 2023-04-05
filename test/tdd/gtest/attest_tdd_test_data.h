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
const char* ATTEST_RESET_EXPECT_CHAP = "9f3ea2783a4ab4f9097da94c6640c9b813ad9fa3dba2b0c12432bf67eef83325";
const int64_t ATTEST_RESET_EXPECT_CHAP_TIME = 1279940966;
const char* ATTEST_RESET_EXPECT_TOKEN = "WV4xvYp/1ZplMQBFaEE7Q3mpA2sTiqLFq84rIj7yGqE=";

const char* ATTEST_REST_ERROR_EXPECT_RESULT = "{\"errcode\":15003}";

const char* ATTEST_AUTH_EXPECT_RESULT = "{ \
    \"authStats\":\".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSIsImV4cGlyZVRpbWUiOjE2ODMyMDQxNTQxNzQsImt \
    pdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRhaWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMD \
    gsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NT \
    I3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQyIsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhL \
    XdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAvT3Blbkhhcm1vbnkgMi4zIGJldGEvZGVi \
    dWcifQ.\", \
    \"errcode\":0, \
    \"ticket\":\"Fn99Hh0n0rAPPRTyliw2/KhxBlFO/Wxt\", \
    \"token\":\"lAwN6RgKsI4KIR4bm0aarnzPtstitvEh\", \
    \"uuid\":\"28aa1751-bc0a-49e1-a69b-8910e043ce77\" \
    }";
const char* ATTEST_AUTH_CHAP = "79f79b0d2a64cfd7d0591774c54442421588b6865adf968e81475c7ffc3ad692";
const int64_t ATTEST_AUTH_CHAP_TIME = 1279941246;
const char* ATTEST_AUTH_GEN_TOKEN = "CzuwaTMyRGcHl4pMBYkRN49G8Z0CXv+Mz/mzcU2NEnE=";

<<<<<<< HEAD
const char* ATTEST_ACTIVE_EXPECT_TOKEN = "c3u4NMDQ/RLrh6WH1+6U5Avn3YfVCUoheVRmS8Faz/w=";
const int64_t ATTEST_ACTIVE_CHAP_TIME = 1279941779;
=======
const char* ATTEST_ACTIVE_GEN_TOKEN = "HBDVx6ofSCNndqodOwX4YR3Les2PDP6NSsGV66uu4Jk=";
const int64_t ATTEST_ACTIVE_CHAP_TIME = 1118038882;
>>>>>>> b4e7b8cd1c9f95a053fc12afcd947cfa1a654579

const int64_t ATTEST_EXPIRRTIME = -584928741;
const int32_t ATTEST_HARDWARERESULT = 0;
             
#endif
