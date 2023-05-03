#ifndef IGNITE_MEMORY_H_
#define IGNITE_MEMORY_H_

#include <stddef.h>
#include <stdlib.h>

#include "ignite/ignite.h"

void *ignite_memory_allocate(size_t bytes);

void *ignite_memory_copy(void *destanation, const void *restrict source,
                         size_t bytes);

void ignite_memory_free(void *pointer);

#define smart_free IGNITE_CLEANUP(ignite_memory_free)
#define smart(__clean_callback) IGNITE_CLEANUP(__clean_callback)

#endif // IGNITE_MEMORY_H_
