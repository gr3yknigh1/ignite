#include "ignite/dynamic_array.h"
#include "ignite/assert.h"
#include "ignite/memory.h"

float ignite_dynamic_array_capacity_multiplyer = 2;

void ignite_dynamic_array_init_empty(struct ignite_dynamic_array *array,
                                     const struct ignite_container_type *type) {
    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(type != NULL);

    *array = (struct ignite_dynamic_array){
        .data = NULL,
        .capacity = 0,
        .length = 0,
        .type = type,
    };
}

void ignite_dynamic_array_init_from_other(
    struct ignite_dynamic_array *restrict array,
    const struct ignite_dynamic_array *other) {

    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(other != NULL);

    ignite_dynamic_array_init_from_ptr(array, other->data, other->length,
                                       other->type);
}

void ignite_dynamic_array_init_from_ptr(
    struct ignite_dynamic_array *array, const void *data, const uint64_t length,
    const struct ignite_container_type *type) {

    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(data != NULL);
    IGNITE_ASSERT(type != NULL);

    *array = (struct ignite_dynamic_array){
        .data = ignite_memory_allocate(length * type->size),
        .capacity = length,
        .length = length,
        .type = type,
    };

    if (!array->type->is_reference) {
        ignite_memory_copy(array->data, data, length);
        return;
    }

    for (uint64_t i = 0; i < length; ++i) {
        array->type->copy((char *)array->data + i, (char *)data + i,
                          type->size);
    }
}

void ignite_dynamic_array_copy(void *restrict destanation, const void *source,
                               size_t size) {
    (void)size;

    IGNITE_ASSERT(destanation != NULL);
    IGNITE_ASSERT(source != NULL);
    IGNITE_ASSERT(size == sizeof(struct ignite_dynamic_array));

    struct ignite_dynamic_array *destanation_array = destanation;
    const struct ignite_dynamic_array *source_array = source;

    ignite_dynamic_array_init_from_other(destanation_array, source_array);
}
