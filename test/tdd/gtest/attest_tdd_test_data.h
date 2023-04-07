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
const char* ATTEST_RESET_EXPECT_CHAP = "39a9d04d41617162893c3312ceb030acac8d8bd0cc9fcebcab5402a43891341d";
const int64_t ATTEST_RESET_EXPECT_CHAP_TIME = 1449458490;
const char* ATTEST_RESET_EXPECT_TOKEN = "WOetrEFOcjw8Px2TZNmq3ckoMzXEkkoLfgQeGNnG3XA=";

const char* ATTEST_REST_ERROR_EXPECT_RESULT = "15003";

const char* ATTEST_AUTH_EXPECT_RESULT = "{\"authStats\":\".eyJhdXRoUmVzdWx0IjowLCJhdXRoVHlwZSI6IlRPS0VOX0VOQUJMRSI\
sImV4cGlyZVRpbWUiOjE2ODMzNzM2NzE2NzQsImtpdFBvbGljeSI6W10sInNvZnR3YXJlUmVzdWx0IjozMDAwMiwic29mdHdhcmVSZXN1bHREZXRh\
aWwiOnsicGF0Y2hMZXZlbFJlc3VsdCI6MzAwMDgsInBjaWRSZXN1bHQiOjMwMDExLCJyb290SGFzaFJlc3VsdCI6MzAwMDksInZlcnNpb25JZFJlc\
3VsdCI6MzAwMDJ9LCJ1ZGlkIjoiODFDOTQ0NTI3OUEzQTQxN0Q0MTU5RkRGQzYyNjkxQkM4REEwMDJFODQ2M0M3MEQyM0FCNENCRjRERjk4MjYxQy\
IsInZlcnNpb25JZCI6ImRlZmF1bHQvaHVhLXdlaS9rZW1pbi9kZWZhdWx0L09wZW5IYXJtb255LTQuMC4zLjIoQ2FuYXJ5MSkvb2hvcy9tYXgvMTAv\
T3Blbkhhcm1vbnkgMi4zIGJldGEvZGVidWcifQ.\",\
\"errcode\":0,\
\"ticket\":\"svnR0unsciaFi7S4hcpBa/LCSiYwNSt6\",\
\"token\":\"yh9te54pfTb91CrSqpD5fQsVBA/etKNb\",\
\"uuid\":\"156dcff8-0ab0-4521-ac8f-ba682e6ca5a0\"\
}3";
const char* ATTEST_AUTH_CHAP = "a81441e3c0d8d6a78907fa0888f9241be9591c4d6b7a533318b010fb2c3d9b80";
const int64_t ATTEST_AUTH_CHAP_TIME = 1449458719;
const char* ATTEST_AUTH_GEN_TOKEN = "5HWNhKgnJ+sVZM313rCsNa3QK2RhrC4+bClH9SX5O84=";

const char* ATTEST_ACTIVE_EXPECT_TOKEN = "648390656";
const int64_t ATTEST_ACTIVE_CHAP_TIME = 1449459365;

const int64_t ATTEST_EXPIRRTIME = -584928741;
const int32_t ATTEST_HARDWARERESULT = 0;
             
#endif
