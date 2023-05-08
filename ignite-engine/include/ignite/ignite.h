#ifndef IGNITE_IGNITE_H_
#define IGNITE_IGNITE_H_

#include "ignite/platform.h"

#if defined(IGNITE_PLATFORM_WINDOWS)
#define IGNITE_DEBUGBREAK() __debugbreak()
#elif defined(IGNITE_PLATFORM_LINUX)
#include <signal.h>
#define IGNITE_DEBUGBREAK() raise(SIGILL)
#else
#error "This platform doesn't support debugbreak"
#endif

#define IGNITE_EXPAND_MACRO(X) X
#define IGNITE_STRINGIFY(X) #X

// TODO: Add .dll option export
#define IGNITE_EXPORT

#define IGNITE_ARRAY_LENGTH(__array) (sizeof((__array)) / sizeof((__array)[0]))

#define IGNITE_INLINE inline

#endif // IGNITE_IGNITE_H_
