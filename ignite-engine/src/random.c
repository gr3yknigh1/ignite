#include "ignite/random.h"
#include "ignite/memory.h"

#include <stdlib.h>

void ignite_random_init(u32 seed) { srand(seed); }

int ignite_random_rand() { return rand(); }

i32 ignite_random_i32(i32 min, i32 max) {
    return min + ignite_random_rand() % (max - min + 1);
}

// NOTE: It's heap allocation
i32 *ignite_random_array_i32(u64 length, const i32 min, i32 max) {
    int32_t *array = ignite_memory_allocate(sizeof(i32) * length);

    for (u64 i = 0; i < length; ++i) {
        array[i] = ignite_random_i32(min, max);
    }

    return array;
}
