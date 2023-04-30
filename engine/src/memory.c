#include "ignite/memory.h"
#include "ignite/assert.h"

#include <stddef.h>

void *ignite_memory_allocate(size_t bytes) {
    return malloc(bytes);
}

void *ignite_memory_copy(void *destanation, const void *restrict source,
                         size_t bytes) {

    IGNITE_ASSERT(destanation != NULL);
    IGNITE_ASSERT(source != NULL);

    for (size_t i = 0; i < bytes; ++i) {
        ((char *)destanation)[i] = ((char *)source)[i];
    }

    return destanation;
}

void ignite_memory_free(void *pointer) {
    IGNITE_ASSERT(pointer != NULL);
    free(pointer);
}
