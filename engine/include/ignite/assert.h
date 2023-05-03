#ifndef IGNITE_ASSERT_H_
#define IGNITE_ASSERT_H_

#include "ignite/ignite.h"
#include "ignite/logging.h"

#ifdef IGNITE_CONFIG_DEBUG

#define IGNITE_ASSERT_IMPL(__check, __message, ...)                            \
    do {                                                                       \
        if (!(__check)) {                                                      \
            IGNITE_INTERNAL_LOG_ERROR(                                         \
                "Assertion '" IGNITE_STRINGIFY(                                \
                    __check) "' failed at %s:%d" __message "\n",               \
                __FILE__, __LINE__ __VA_OPT__(, __VA_ARGS__));                 \
            IGNITE_DEBUGBREAK();                                               \
        }                                                                      \
    } while (0)

#define IGNITE_ASSERT_WITHOUT_LOG(__check) IGNITE_ASSERT_IMPL(__check, "", "")

#define IGNITE_ASSERT_WITH_LOG(__check, ...)                                   \
    IGNITE_ASSERT_IMPL(__check, ": " __VA_ARGS__, "")

#define IGNITE_GET_ASSERT_MACRO_NAME(__arg0, __arg1, __macro, ...) __macro
#define IGNITE_GET_ASSERT_MACRO(...)                                           \
    IGNITE_EXPAND_MACRO(IGNITE_GET_ASSERT_MACRO_NAME(                          \
        __VA_ARGS__, IGNITE_ASSERT_WITH_LOG, IGNITE_ASSERT_WITHOUT_LOG, void))

#define IGNITE_ASSERT(...)                                                     \
    IGNITE_EXPAND_MACRO(IGNITE_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__))

#else

#define IGNITE_ASSERT(...)

#endif

#endif // IGNITE_ASSERT_H_
