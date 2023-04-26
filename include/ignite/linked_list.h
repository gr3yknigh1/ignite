#ifndef IGNITE_LINKED_LIST_H_
#define IGNITE_LINKED_LIST_H_

#include <stdint.h>

#include "ignite/link_node.h"

struct ignite_linked_list {
    struct ignite_link_node *head;
    struct ignite_link_node *tail;

    uint64_t length;
};

#endif // IGNITE_LINKED_LIST_H_
