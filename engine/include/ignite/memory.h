#ifndef IGNITE_MEMORY_H_
#define IGNITE_MEMORY_H_

#include <stddef.h>
#include <stdlib.h>

void *ignite_memory_allocate(size_t bytes);

void *ignite_memory_copy(void *destanation, const void *restrict source,
                         size_t bytes);

void ignite_memory_free(void *pointer);

#endif // IGNITE_MEMORY_H_
