#ifndef IGNITE_RANDOM_H_
#define IGNITE_RANDOM_H_

#include <stdint.h>

void ignite_random_init(uint32_t seed);
int ignite_random_rand();

int32_t ignite_random_i32(int32_t min, int32_t max);
int32_t *ignite_random_array_i32(uint64_t length, const int32_t min, int32_t max);

#endif // IGNITE_RANDOM_H_
