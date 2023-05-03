#ifndef IGNITE_IGNITE_H_
#define IGNITE_IGNITE_H_

#include "ignite/platform.h"

#if defined(IGNITE_PLATFORM_WINDOWS)
#define IGNITE_DEBUGBREAK() __debugbreak()
#elif defined(IGNITE_PLATFORM_LINUX)
#include <signal.h>
#define IGNITE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "This platform doesn't support debugbreak"
#endif

#define IGNITE_EXPAND_MACRO(X) X
#define IGNITE_STRINGIFY(X) #X

// TODO: Add .dll option export
#define IGNITE_EXPORT

#if defined(__clang__) || defined(__gcc__)
#define IGNITE_CLEANUP(__cleanup_callback)                                     \
    __attribute__((__cleanup__(__cleanup_callback)))
#else
#error                                                                         \
    "This compiler probably doesn't support `__cleanup__` attribute. Sorry MSVC"
#endif

#endif // IGNITE_IGNITE_H_
