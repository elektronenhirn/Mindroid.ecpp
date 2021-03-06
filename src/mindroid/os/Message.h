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

#ifndef MINDROID_MESSAGE_H_
#define MINDROID_MESSAGE_H_

#include <stdint.h>
#include <stddef.h>
#include "mindroid/util/concurrent/locks/Lock.h"

namespace mindroid {

class Handler;
class Runnable;

class Message {
public:
    Message();
    Message(Handler& handler);
    Message(Handler& handler, const int32_t what);
    Message(Handler& handler, const int32_t what, const int32_t arg1, const int32_t arg2);
    Message(Handler& handler, const int32_t what, void* const obj);

    Message& operator=(const Message& message);

    static Message* obtain(Message& message, Handler& handler);
    static Message* obtain(Message& message, Handler& handler, const int32_t what);
    static Message* obtain(Message& message, Handler& handler, const int32_t what, const int32_t arg1, const int32_t arg2);
    static Message* obtain(Message& message, Handler& handler, const int32_t what, void* const obj);

    Handler* getTarget() const {
        return target;
    }

    bool sendToTarget();

    inline bool isInUse() {
        AutoLock autoLock;
        return when != 0xFFFFFFFFFFFFFFFF;
    }

    int32_t what;
    int32_t arg1;
    int32_t arg2;
    void* obj;

private:
    inline void markInUse() {
    }

    inline void recycle() {
        AutoLock autoLock;
        when = 0xFFFFFFFFFFFFFFFF;
        nextMessage = NULL;
    }

    void clear();

    uint64_t when; // milliseconds
    Handler* target;
    Message* nextMessage;

    friend class MessageQueue;
    friend class RunnableQueue;
    friend class Looper;
};

} /* namespace mindroid */

#endif /* MINDROID_MESSAGE_H_ */
