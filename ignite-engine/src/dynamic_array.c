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
    struct ignite_dynamic_array *array, const void *data, const u64 length,
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
        ignite_memory_copy(array->data, data, type->size * length);
        return;
    }

    for (u64 i = 0; i < length; ++i) {
        array->type->copy((char *)array->data + i, (char *)data + i,
                          type->size);
    }
}

void ignite_dynamic_array_copy(void *restrict destanation, const void *source,
                               usize size) {
    (void)size;

    IGNITE_ASSERT(destanation != NULL);
    IGNITE_ASSERT(source != NULL);
    IGNITE_ASSERT(size == sizeof(struct ignite_dynamic_array));

    struct ignite_dynamic_array *destanation_array = destanation;
    const struct ignite_dynamic_array *source_array = source;

    ignite_dynamic_array_init_from_other(destanation_array, source_array);
}

void ignite_dynamic_array_push_back(struct ignite_dynamic_array *array,
                                    const void *data) {
    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(data != NULL);

    if (array->length == array->capacity) {
        ignite_dynamic_array_enlarge(array,
                                     ignite_dynamic_array_capacity_multiplyer);
    }

    ignite_memory_copy((char *)array->data + array->type->size * array->length,
                       data, array->type->size);

    ++(array->length);
}

void ignite_dynamic_array_realloc(struct ignite_dynamic_array *array,
                                  u64 amount) {
    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(amount < array->capacity);

    if (amount == 0 || amount == array->capacity) {
        return;
    }

    usize data_size = IGNITE_DYNAMIC_ARRAY_DATA_SIZE(array);
    u64 new_capacity = array->capacity + amount;
    usize new_data_size = new_capacity * array->type->size;

    void *new_data = ignite_memory_allocate(new_data_size);
    ignite_memory_copy(new_data, array->data, data_size);
    ignite_memory_free(array->data);

    array->data = new_data;
    array->capacity = new_capacity;
}

void ignite_dynamic_array_enlarge(struct ignite_dynamic_array *array,
                                  f32 multiplyer) {
    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(multiplyer >= 0.01f);

    u64 enlarge_amount =
        (u64)((f32)(array->capacity == 0 ? 1 : array->capacity) * multiplyer) -
        array->capacity;

    ignite_dynamic_array_realloc(array, enlarge_amount);
}

enum ignite_status
ignite_dynamic_array_get(const struct ignite_dynamic_array *array,
                         const u64 index, void **out_ptr) {
    IGNITE_ASSERT(array != NULL);
    IGNITE_ASSERT(array->data != NULL);
    IGNITE_ASSERT(array->length != 0);
    IGNITE_ASSERT(array->type != NULL);

    if (index > array->length - 1) {
        return IGNITE_INDEX_ERR;
    }

    *out_ptr = (char *)(array->data) + array->type->size * index;
    return IGNITE_OK;
}
