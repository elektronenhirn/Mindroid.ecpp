/*
 * Copyright (C) 2011 Daniel Himmelein
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

#include "mindroid/util/concurrent/locks/Lock.h"
#include "mindroid/util/Assert.h"
#include <zephyr.h>

namespace mindroid {

uint32_t Lock::sCounter = 0;
uint32_t Lock::sLockOutKey = 0;

bool Lock::lock() {
    if (sCounter == 0) {
        sLockOutKey = irq_lock();
    }
    sCounter++;
    return true;
}

void Lock::unlock() {
    ASSERT_TRUE(sCounter != 0);

    sCounter--;
    if (sCounter == 0) {
        irq_unlock(sLockOutKey);
    }
}

} /* namespace mindroid */
