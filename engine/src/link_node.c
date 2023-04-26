#include "ignite/link_node.h"

#include <stddef.h>

void ignite_link_node_init(struct ignite_link_node *node, void *data,
                           struct ignite_link_node *next,
                           struct ignite_link_node *prev) {
    if (node == NULL) {
        return;
    }

    *node = (struct ignite_link_node){
        .data = data,
        .next = next,
        .prev = prev,
    };
}

void ignite_link_node_chain(struct ignite_link_node *prev,
                            struct ignite_link_node *next) {
    prev->next = next;
    next->prev = prev;
}
