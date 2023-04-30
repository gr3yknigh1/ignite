#ifndef IGNITE_CONTAINER_TYPE_H_
#define IGNITE_CONTAINER_TYPE_H_

#include <stdbool.h>
#include <stddef.h>

typedef void *(*ignite_copy_func_t)(void *destanation,
                                    const void *restrict source, size_t size);
typedef void (*ignite_free_func_t)(void *pointer);

struct ignite_container_type {
    size_t size;
    bool is_reference;
    ignite_copy_func_t copy;
    ignite_free_func_t free;
};

void ignite_container_type_init(struct ignite_container_type *type,
                                const size_t size, bool is_reference,
                                ignite_copy_func_t copy,
                                ignite_free_func_t free);

void ignite_container_store_value(const struct ignite_container_type *type,
                                  const void *value);

#endif // IGNITE_CONTAINER_TYPE_H_
