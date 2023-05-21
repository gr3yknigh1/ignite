#ifndef IGNITE_DYNAMIC_ARRAY_H_
#define IGNITE_DYNAMIC_ARRAY_H_

#include <stddef.h>

#include "ignite/container_type.h"
#include "ignite/ignite.h"
#include "ignite/status.h"

extern float ignite_dynamic_array_capacity_multiplyer;

struct ignite_dynamic_array {
    void *data;
    u64 capacity;

    u64 length;
    const struct ignite_container_type *type;
};

#define IGNITE_DYNAMIC_ARRAY_DATA_SIZE(__darray) \
    ((__darray)->capacity * (__darray)->type->size)

void ignite_dynamic_array_init_empty(struct ignite_dynamic_array *array,
                                     const struct ignite_container_type *type);

void ignite_dynamic_array_init_from_other(
    struct ignite_dynamic_array *restrict array,
    const struct ignite_dynamic_array *other);

void ignite_dynamic_array_init_from_ptr(
    struct ignite_dynamic_array *array, const void *data, const u64 length,
    const struct ignite_container_type *type);

void ignite_dynamic_array_copy(void *restrict destanation, const void *source,
                               usize size);

void ignite_dynamic_array_push_back(struct ignite_dynamic_array *array,
                                    const void *data);

void ignite_dynamic_array_push_front(struct ignite_dynamic_array *array,
                                     const void *data);

void ignite_dynamic_array_realloc(struct ignite_dynamic_array *array,
                                  u64 amount);

void ignite_dynamic_array_enlarge(struct ignite_dynamic_array *array,
                                  f32 multiplyer);

enum ignite_status
ignite_dynamic_array_shrink(struct ignite_dynamic_array *array, u64 item_count);

void ignite_dynamic_array_shrink_to_fit(struct ignite_dynamic_array *array);

enum ignite_status
ignite_dynamic_array_get(const struct ignite_dynamic_array *array,
                         const u64 index, void **out_ptr);

void ignite_dynamic_array_clear(struct ignite_dynamic_array *array);

void ignite_dynamic_array_free(void *pointer);

#endif // IGNITE_DYNAMIC_ARRAY_H_
