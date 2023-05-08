#ifndef IGNITE_CONTAINER_TYPE_H_
#define IGNITE_CONTAINER_TYPE_H_

#include <stdbool.h>

#include "ignite/memory.h"
#include "ignite/types.h"

typedef void *(*ignite_copy_func_t)(void *destanation,
                                    const void *restrict source, usize size);
typedef void (*ignite_free_func_t)(void *pointer);

struct ignite_container_type {
    usize size;
    bool is_reference;
    ignite_copy_func_t copy;
    ignite_free_func_t free;
};

void ignite_container_type_init(struct ignite_container_type *type,
                                const usize size, bool is_reference,
                                ignite_copy_func_t copy,
                                ignite_free_func_t free);

void ignite_container_store_value(const struct ignite_container_type *type,
                                  void **destanation, const void *value);

#define IGNITE_DEFINE_CONTAINER_TYPE(__name)                                   \
    extern const struct ignite_container_type __name

#define IGNITE_IMPL_CONTAINER_TYPE(__name, __size, __is_ref, __copy_func,      \
                                   __free_func)                                \
    const struct ignite_container_type __name = {.size = (__size),             \
                                                 .is_reference = (__is_ref),   \
                                                 .copy = (__copy_func),        \
                                                 .free = (__free_func)}

#define IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(__name, __size)                   \
    IGNITE_IMPL_CONTAINER_TYPE(__name, __size, false, ignite_memory_copy,      \
                               ignite_memory_free)

IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I8);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I16);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I32);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I64);

IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U8);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U16);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U32);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U64);

IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_F32);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_F64);

IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_USIZE);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_SSIZE);

IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_BYTE);
IGNITE_DEFINE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_CSTR);

#endif // IGNITE_CONTAINER_TYPE_H_
