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

#include "mindroid/os/Looper.h"
#include "mindroid/os/Handler.h"
#include "mindroid/os/Message.h"
#include "mindroid/util/Assert.h"
#include <new>

namespace mindroid {

uint8_t Looper::sLooperData[MAX_NUM_LOOPERS * sizeof(Looper)];
Looper* Looper::sLoopers[MAX_NUM_LOOPERS] = { NULL };
k_tid_t Looper::sLooperThreadIds[MAX_NUM_LOOPERS] = { NULL };
int Looper::sNumLoopers = 0;

Looper::Looper() :
        mMessageQueue(),
        mRunnableQueue(*this) {
}

bool Looper::prepare() {
    const k_tid_t threadId = k_current_get();
    int i = 0;
    for (; i < MAX_NUM_LOOPERS; i++) {
        if (sLooperThreadIds[i] == threadId) {
            break;
        }
    }
    Looper* looper = NULL;
    {
        AutoLock autoLock;
        ASSERT_TRUE(sNumLoopers < MAX_NUM_LOOPERS);
        if (i >= MAX_NUM_LOOPERS) {
            i = sNumLoopers;
        }
        if (sLoopers[i] == NULL) {
            looper = reinterpret_cast<Looper*>(sLooperData + i * sizeof(Looper));
            sLoopers[i] = looper;
            sLooperThreadIds[i] = threadId;
            sNumLoopers++;
        } else {
            // There should be only one Looper per thread.
            return false;
        }
    }
    ASSERT_TRUE(looper != NULL);
    new (looper) Looper();
    return true;
}

Looper* Looper::myLooper() {
    const k_tid_t threadId = k_current_get();
    AutoLock autoLock;
    int i = 0;
    for (; i < sNumLoopers; i++) {
        if (sLooperThreadIds[i] == threadId) {
            break;
        }
    }
    if (i < sNumLoopers) {
        return sLoopers[i];
    } else {
        return NULL;
    }
}

void Looper::loop() {
    Looper* me = myLooper();
    if (me != NULL) {
        MessageQueue& mq = me->mMessageQueue;
        while (true) {
            Message* message = mq.dequeueMessage(me->mMessage);
            if (message == NULL) {
                return;
            }
            Handler* handler = message->target;
            message->target = NULL;
            handler->dispatchMessage(*message);
        }
    }
}

void Looper::loop(uint32_t maxLoops) {
    Looper* me = myLooper();
    if (me != NULL) {
        MessageQueue& mq = me->mMessageQueue;
        uint32_t i = 0;
        while (i < maxLoops) {
            Message* message = mq.dequeueMessage(me->mMessage, false);
            if (message == NULL) {
                return;
            }
            Handler* handler = message->target;
            message->target = NULL;
            handler->dispatchMessage(*message);
            i++;
        }
    }
}

void Looper::quit() {
    mMessageQueue.quit();
}

} /* namespace mindroid */
