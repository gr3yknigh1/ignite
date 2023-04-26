#ifndef IGNITE_H_
#define IGNITE_H_

#include "ignite/platform.h"

#if defined(IGNITE_PLATFORM_WINDOWS)
#define IGNITE_DEBUGBREAK() __debugbreak()
#elif defined(IGNITE_PLATFORM_LINUX)
#include <signal.h>
#define IGNITE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "This platform doesn't support debugbreak"
#endif

#define IGNITE_STRINGIFY(X) #X

#endif // IGNITE_H_
