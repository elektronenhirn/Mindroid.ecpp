/*
 * Copyright (C) 2011 Daniel Himmelein
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mindroid/os/SystemClock.h"
#include <time.h>

namespace mindroid {

uint64_t SystemClock::monotonicTime() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    uint64_t ns = (((uint64_t) now.tv_sec * 1000000000LL) + now.tv_nsec);
    return ns / 1000000;
}

uint64_t SystemClock::realTime() {
    timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    uint64_t ns = (((uint64_t) now.tv_sec * 1000000000LL) + now.tv_nsec);
    return ns / 1000000;
}


} /* namespace mindroid */
