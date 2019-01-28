/*
 * Copyright (C) 2019 Florian Bramer
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
#include <zephyr.h>

namespace mindroid {

uint64_t SystemClock::monotonicTime() {
    return k_uptime_get();
}

uint64_t SystemClock::realTime() {
    __ASSERT_NO_MSG(false); //no support by zephyr found
}

} /* namespace mindroid */
