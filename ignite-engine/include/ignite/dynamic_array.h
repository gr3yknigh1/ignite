#ifndef IGNITE_DYNAMIC_ARRAY_H_
#define IGNITE_DYNAMIC_ARRAY_H_

#include <stddef.h>
#include <stdint.h>

#include "ignite/container_type.h"
#include "ignite/status.h"

extern float ignite_dynamic_array_capacity_multiplyer;

struct ignite_dynamic_array {
    void *data;
    uint64_t capacity;

    uint64_t length;
    const struct ignite_container_type *type;
};

void ignite_dynamic_array_init_empty(struct ignite_dynamic_array *array,
                                     const struct ignite_container_type *type);

void ignite_dynamic_array_init_from_other(
    struct ignite_dynamic_array *restrict array,
    const struct ignite_dynamic_array *other);

void ignite_dynamic_array_init_from_ptr(
    struct ignite_dynamic_array *array, const void *data, const uint64_t length,
    const struct ignite_container_type *type);

void ignite_dynamic_array_copy(void *restrict destanation, const void *source,
                               size_t size);

void ignite_dynamic_array_push_back(struct ignite_dynamic_array *array,
                                    const void *data);

void ignite_dynamic_array_push_front(struct ignite_dynamic_array *array,
                                     const void *data);

enum ignite_status
ignite_dynamic_array_reserve(struct ignite_dynamic_array *array,
                             uint64_t amount);

enum ignite_status ignite_dynamic_array_get(struct ignite_dynamic_array *array,
                                            const uint64_t index,
                                            void **out_ptr);

void ignite_dynamic_array_clear(struct ignite_dynamic_array *array);

void ignite_dynamic_array_free(void *pointer);

#endif // IGNITE_DYNAMIC_ARRAY_H_
