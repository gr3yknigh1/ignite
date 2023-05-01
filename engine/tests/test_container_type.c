#include <criterion/criterion.h>

#include "test_common.h"

#include "ignite/container_type.h"
#include "ignite/memory.h"

void init() {}
void fini() {}

TestSuite(container_type, .init = init, .fini = fini);

Test(container_type, init) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    cr_expect(type.size == sizeof(int));
    cr_expect(type.is_reference == false);
    cr_expect(type.copy == ignite_memory_copy);
    cr_expect(type.free == ignite_memory_free);
}

Test(container_type, init_null_dest, .signal = ASSERTION_SIGNAL) {
    ignite_container_type_init(NULL, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);
}

Test(container_type, init_zero_size, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, 0, false, ignite_memory_copy,
                               ignite_memory_free);
}

Test(container_type, init_null_copy, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, NULL,
                               ignite_memory_free);
}

Test(container_type, init_null_free, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               NULL);
}

Test(container_type, store_value_not_ref) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    int source_value = 10;

    int *stored_ptr = NULL;
    ignite_container_store_value(&type, (void **)&stored_ptr, &source_value);

    cr_expect(stored_ptr != &source_value);
    cr_expect(*stored_ptr == source_value);
}

Test(container_type, store_value_with_null_type, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    int source_value = 10;

    int *stored_ptr = NULL;
    ignite_container_store_value(NULL, (void **)&stored_ptr, &source_value);
    ignite_container_store_value(&type, NULL, &source_value);
}

Test(container_type, store_null_value, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    int *stored_ptr = NULL;
    ignite_container_store_value(NULL, (void **)&stored_ptr, NULL);
}

Test(container_type, store_to_null, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    int source_value = 10;
    ignite_container_store_value(&type, NULL, &source_value);
}

Test(container_type, store_to_not_null_ptr, .signal = ASSERTION_SIGNAL) {
    struct ignite_container_type type;
    ignite_container_type_init(&type, sizeof(int), false, ignite_memory_copy,
                               ignite_memory_free);

    int source_value = 10;
    int *stored_ptr = &source_value;
    ignite_container_store_value(&type, (void **)&stored_ptr, &source_value);
}
