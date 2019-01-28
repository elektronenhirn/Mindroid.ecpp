/*
 * Copyright (C) 2014 Daniel Himmelein
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

#ifndef ASSERT_H_
#define ASSERT_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "mindroid/lang/Object.h"

namespace mindroid {

#ifdef MINDROID_EXTERNAL_ASSERT_FUNCTION

extern void mindroid_assert_func(bool condition, const char *filename, int lineno, const char *conditionAsStr);
extern void mindroid_assert_func_with_msg(bool condition, const char *filename, int lineno, const char *msg, const char *conditionAsStr);

#define ASSERT_TRUE(condition) \
        mindroid_assert_func(condition, __FILE__, __LINE__, #condition)
#define ASSERT_TRUE_WITH_MSG(msg, condition) \
        mindroid_assert_func_with_msg(condition, __FILE__, __LINE__, msg, #condition)

#define ASSERT_FALSE(condition) \
        mindroid_assert_func(!condition, __FILE__, __LINE__, #condition)
#define ASSERT_FALSE_WITH_MSG(msg, condition) \
        mindroid_assert_func_with_msg(!condition, __FILE__, __LINE__, msg), #condition

#define ASSERT_NULL(condition) \
        mindroid_assert_func(condition == NULL, __FILE__, __LINE__, #condition)
#define ASSERT_NULL_WITH_MSG(msg, condition) \
        mindroid_assert_func_with_msg(condition == NULL, __FILE__, __LINE__, msg, #condition)

#define ASSERT_NOT_NULL(condition) \
        mindroid_assert_func(condition != NULL, __FILE__, __LINE__, #condition)
#define ASSERT_NOT_NULL_WITH_MSG(msg, condition) \
        mindroid_assert_func_with_msg(condition != NULL, __FILE__, __LINE__, msg, #condition)

#define ASSERT_EQUALS(expected, actual) \
        mindroid_assert_func(expected == actual, __FILE__, __LINE__, #expected "==" #actual)
#define ASSERT_EQUALS_WITH_MSG(msg, expected, actual) \
        mindroid_assert_func_with_msg(expected == actual, __FILE__, __LINE__, msg, #expected "==" #actual)

#else 

#define ASSERT_TRUE(condition) Assert::assertTrue(condition) 
#define ASSERT_TRUE_WITH_MSG(msg, condition) Assert::assertTrue(msg, condition)

#define ASSERT_FALSE(condition) Assert::assertFalse(condition)
#define ASSERT_FALSE_WITH_MSG(msg, condition) Assert::assertFalse(msg, condition)

#define ASSERT_NULL(condition) Assert::assertNull(condition) 
#define ASSERT_NULL_WITH_MSG(msg, condition) Assert::assertNull(msg, condition)

#define ASSERT_NOT_NULL(condition) Assert::assertNotNull(condition)
#define ASSERT_NOT_NULL_WITH_MSG(msg, condition) Assert::assertNotNull(msg, condition)

#define ASSERT_EQUALS(expected, actual) Assert::assertEquals(expected, actual)
#define ASSERT_EQUALS_WITH_MSG(msg, expected, actual) Assert::assertEquals(msg, expected, actual);

class Assert {
public:
    static void assertTrue(bool condition) {
        assert(condition);
    }
    static void assertTrue(const char* message, bool condition);

    static void assertFalse(bool condition) {
        assert(!condition);
    }
    static void assertFalse(const char* message, bool condition);

    static void assertNull(void* ptr) {
        assert(ptr == NULL);
    }
    static void assertNull(const char* message, void* ptr);

    static void assertNotNull(void* ptr) {
        assert(ptr != NULL);
    }
    static void assertNotNull(const char* message, void* ptr);

    static void assertEquals(bool expected, bool actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, bool expected, bool actual);

    static void assertEquals(int8_t expected, int8_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, int8_t expected, int8_t actual);

    static void assertEquals(uint8_t expected, uint8_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, uint8_t expected, uint8_t actual);

    static void assertEquals(int16_t expected, int16_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, int16_t expected, int16_t actual);

    static void assertEquals(uint16_t expected, uint16_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, uint16_t expected, uint16_t actual);

    static void assertEquals(int32_t expected, int32_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, int32_t expected, int32_t actual);

    static void assertEquals(uint32_t expected, uint32_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, uint32_t expected, uint32_t actual);

    static void assertEquals(int64_t expected, int64_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, int64_t expected, int64_t actual);

    static void assertEquals(uint64_t expected, uint64_t actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, uint64_t expected, uint64_t actual);

    static void assertEquals(void* expected, void* actual) {
        assert(expected == actual);
    }
    static void assertEquals(const char* message, void* expected, void* actual);

private:
    Assert() {
    }

    static const char* const LOG_TAG;

    NO_COPY_CONSTRUCTOR_AND_ASSIGNMENT_OPERATOR(Assert)
};

#endif /* MINDROID_EXTERNAL_ASSERT_FUNCTION */

} /* namespace mindroid */

#endif /* ASSERT_H_ */
