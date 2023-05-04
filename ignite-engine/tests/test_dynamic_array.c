#include <criterion/criterion.h>

#include "ignite/container_type.h"
#include "ignite/dynamic_array.h"
#include "ignite/memory.h"

static struct {
    struct ignite_container_type type_i32;
} data;

void init() {
    ignite_container_type_init(&data.type_i32, sizeof(int32_t), false,
                               ignite_memory_copy, ignite_memory_free);
}
void fini() {}

TestSuite(dynamic_array, .init = init, .fini = fini);

Test(dynamic_array, init_empty) {
    struct ignite_dynamic_array array;
    ignite_dynamic_array_init_empty(&array, &data.type_i32);

    cr_expect(array.data == NULL);
    cr_expect(array.capacity == 0);
    cr_expect(array.length == 0);
    cr_expect(array.type == &data.type_i32);
}

Test(dynamic_array, init_from_other) {}

Test(dynamic_array, init_from_ptr) {}

Test(dynamic_array, reserve) {}
