#ifndef IGNITE_RANDOM_H_
#define IGNITE_RANDOM_H_

#include "ignite/types.h"

void ignite_random_init(u32 seed);
int ignite_random_rand();

int32_t ignite_random_i32(i32 min, i32 max);
int32_t *ignite_random_array_i32(u64 length, const i32 min, i32 max);

#endif // IGNITE_RANDOM_H_
