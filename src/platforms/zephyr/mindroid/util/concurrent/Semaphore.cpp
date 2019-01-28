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

#include "mindroid/util/concurrent/Semaphore.h"

namespace mindroid {

Semaphore::Semaphore(uint32_t value) {
    k_sem_init(&mSemaphore, value, 1);
}

Semaphore::~Semaphore() {
    //deleting semaphore not supported by zephyr
}

void Semaphore::signal() {
    k_sem_give(&mSemaphore);
}

bool Semaphore::wait() {
    return k_sem_take(&mSemaphore, K_FOREVER) == 0;
}

bool Semaphore::wait(uint32_t timeout) {
    return k_sem_take(&mSemaphore, timeout) == 0;
}

} /* namespace mindroid */
