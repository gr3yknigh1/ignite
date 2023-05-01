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
