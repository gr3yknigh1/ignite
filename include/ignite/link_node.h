#ifndef IGNITE_LINK_NODE_H_
#define IGNITE_LINK_NODE_H_

struct ignite_link_node {
    void *data;

    struct ignite_link_node *next;
    struct ignite_link_node *prev;
};

void ignite_link_node_init(struct ignite_link_node *node, const void *data,
                           struct ignite_link_node *next,
                           struct ignite_link_node *prev);

void ignite_link_node_chain(struct ignite_link_node *prev,
                            struct ignite_link_node *next);

#endif // IGNITE_LINK_NODE_H_
