#include "ignite/random.h"

#include <stdlib.h>

void ignite_random_init(uint32_t seed) { srand(seed); }

int ignite_random_rand() { return rand(); }

int32_t ignite_random_i32(int32_t min, int32_t max) {
    return min + ignite_random_rand() % (max - min + 1);
}

// NOTE: It's heap allocation
int32_t *ignite_random_array_i32(uint64_t length, const int32_t min,
                                 int32_t max) {
    int32_t *array = malloc(sizeof(int32_t) * length);

    for (uint64_t i = 0; i < length; ++i) {
        array[i] = ignite_random_i32(min, max);
    }

    return array;
}
