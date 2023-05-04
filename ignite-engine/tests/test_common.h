#ifndef TEST_COMMON_H_
#define TEST_COMMON_H_

#include "ignite/ignite.h"

#ifdef IGNITE_PLATFORM_LINUX
#include <signal.h>
static const int ASSERTION_SIGNAL = SIGILL;
#else
#error "Doesn't support signal check"
#endif

#endif
