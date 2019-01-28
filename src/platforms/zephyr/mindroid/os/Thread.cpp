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

#include "mindroid/os/Thread.h"
#include "mindroid/util/Assert.h"

namespace mindroid {

Thread::Thread() :
        mRunnable(this),
        mThreadId(NULL),
        mInterrupted(false) {
        /**
         * Dynamic thread creation is actually supported
         * by zephyr, but the stack area needs to be known
         * beforehand. As there is now way to pass stack ptr
         * here we cannot provide support for mindroid
         * threads.
         */
    __ASSERT(false, "Dynamic thread creation not supported");
}

Thread::Thread(Runnable* runnable) :
        mRunnable(runnable),
        mThreadId(NULL),
        mInterrupted(false) {
    __ASSERT(false, "Dynamic thread creation not supported");
}

bool Thread::start() {
    return false;
}

void Thread::sleep(uint32_t milliseconds) {
}

void Thread::join() const {
}

void Thread::exec(const void* args) {
}

void Thread::interrupt() {
}

bool Thread::isInterrupted() const {
    return false;
}

} /* namespace mindroid */
