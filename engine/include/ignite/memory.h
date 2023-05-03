#ifndef IGNITE_MEMORY_H_
#define IGNITE_MEMORY_H_

#include <stddef.h>
#include <stdlib.h>

void *ignite_memory_allocate(size_t bytes);

void *ignite_memory_copy(void *destanation, const void *restrict source,
                         size_t bytes);

void ignite_memory_free(void *pointer);

#if defined(__clang__) || defined(__gcc__)
#define IGNITE_CLEANUP(__cleanup_callback)                                     \
    __attribute__((__cleanup__(__cleanup_callback)))
#else
#error                                                                         \
    "This compiler probably doesn't support `__cleanup__` attribute. Sorry MSVC"
#endif

#define smart_free IGNITE_CLEANUP(ignite_memory_free)
#define smart(__clean_callback) IGNITE_CLEANUP(__clean_callback)

#endif // IGNITE_MEMORY_H_
