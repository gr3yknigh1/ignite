#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <time.h>

#include "test_common.h"

#include "ignite/logging.h"
#include "ignite/memory.h"
#include "ignite/random.h"

void init() { ignite_internal_logger.log_level = LOG_LEVEL_NO_LOG; }
void fini() {}

TestSuite(memory, .init = init, .fini = fini);

Test(memory, allocation) {
    void *data = ignite_memory_allocate(10);
    cr_expect(data != NULL);
    ignite_memory_free(data);
}

Test(memory, copy) {
    ignite_random_init((uint32_t)time(NULL));

    uint64_t source_array_length = 10;
    int32_t *source_array =
        ignite_random_array_i32(source_array_length, -10, 10);

    int32_t copied_array[source_array_length];

    ignite_memory_copy(copied_array, source_array,
                       sizeof(int32_t) * source_array_length);

    cr_expect(source_array != copied_array);
    for (uint64_t i = 0; i < source_array_length; ++i) {
        cr_expect(source_array[i] == copied_array[i], "src=%d vs cpy=%d",
                  source_array[i], copied_array[i]);
    }

    ignite_memory_free(source_array);
}

Test(memory, copy_null, .signal = ASSERTION_SIGNAL) {
    ignite_random_init((uint32_t)time(NULL));

    uint64_t source_array_length = 10;
    int32_t *source_array =
        ignite_random_array_i32(source_array_length, -10, 10);

    ignite_memory_copy(NULL, source_array, source_array_length);

    int32_t copied_array[source_array_length];
    ignite_memory_copy(copied_array, NULL, source_array_length);
}

Test(memory, free) {
    char *some_buffer = ignite_memory_allocate(10);
    ignite_memory_free(some_buffer);
}

Test(memory, free_null, .signal = ASSERTION_SIGNAL) {
    ignite_memory_free(NULL);
}
