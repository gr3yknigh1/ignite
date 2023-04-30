#include <stdint.h>
#include <time.h>

#include <criterion/criterion.h>

#include "ignite/random.h"
#include "test_common.h"

void init() { ignite_random_init((uint32_t)time(NULL)); }
void fini() {}

TestSuite(random, .init = init, .fini = fini);

Test(random, init_seed) { ignite_random_init((uint32_t)time(NULL)); }
Test(random, call_rand) { ignite_random_rand(); }

Test(random, random_i32) {
    const uint64_t range_length = 1000;
    const int32_t range_min = -20;
    const int32_t range_max = 20;

    for (uint64_t i = 0; i < range_length; ++i) {
        int32_t generated_int = ignite_random_i32(range_min, range_max);
        cr_expect(generated_int >= range_min && generated_int <= range_max);
    }
}
