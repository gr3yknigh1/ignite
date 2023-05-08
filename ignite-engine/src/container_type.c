#include "ignite/container_type.h"
#include "ignite/assert.h"
#include "ignite/memory.h"

void ignite_container_type_init(struct ignite_container_type *type,
                                const size_t size, bool is_reference,
                                ignite_copy_func_t copy,
                                ignite_free_func_t free) {
    IGNITE_ASSERT(type != NULL);
    IGNITE_ASSERT(size != 0);
    IGNITE_ASSERT(copy != NULL);
    IGNITE_ASSERT(free != NULL);

    *type = (struct ignite_container_type){
        .size = size,
        .is_reference = is_reference,
        .copy = copy,
        .free = free,
    };
}

void ignite_container_store_value(const struct ignite_container_type *type,
                                  void **destanation, const void *value) {
    IGNITE_ASSERT(type != NULL);
    IGNITE_ASSERT(destanation != NULL);
    IGNITE_ASSERT(*destanation == NULL);
    IGNITE_ASSERT(value != NULL);

    if (type->is_reference) {
        *destanation = (void *)value;
        return;
    }

    *destanation = ignite_memory_allocate(type->size);
    type->copy(*destanation, value, type->size);
}

IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I8, sizeof(i8));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I16, sizeof(i16));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I32, sizeof(i32));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_I64, sizeof(i64));

IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U8, sizeof(u8));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U16, sizeof(u16));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U32, sizeof(u32));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_U64, sizeof(u64));

IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_F32, sizeof(f32));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_F64, sizeof(f64));

IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_USIZE,
                                     sizeof(usize));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_SSIZE,
                                     sizeof(ssize));

IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_BYTE, sizeof(byte));
IGNITE_IMPL_PRIMITIVE_CONTAINER_TYPE(IGNITE_CONTAINER_TYPE_CSTR, sizeof(c_str));
