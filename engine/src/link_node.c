#include "ignite/link_node.h"
#include "ignite/assert.h"

#include <stddef.h>

void ignite_link_node_init(struct ignite_link_node *node, void *data,
                           struct ignite_link_node *next,
                           struct ignite_link_node *prev) {
    IGNITE_ASSERT(node != NULL);
    *node = (struct ignite_link_node){
        .data = data,
        .next = next,
        .prev = prev,
    };
}

void ignite_link_node_chain(struct ignite_link_node *prev,
                            struct ignite_link_node *next) {
    IGNITE_ASSERT(prev != NULL);
    IGNITE_ASSERT(next != NULL);
    prev->next = next;
    next->prev = prev;
}
