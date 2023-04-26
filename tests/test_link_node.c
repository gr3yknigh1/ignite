#include <criterion/criterion.h>

#include "ignite/link_node.h"

void init() {}
void fini() {}

TestSuite(link_node, .init = init, .fini = fini);

Test(link_node, init_orphan_empty) {
    struct ignite_link_node node;
    ignite_link_node_init(&node, NULL, NULL, NULL);

    cr_expect_null(node.data);
    cr_expect_null(node.next);
    cr_expect_null(node.prev);
}

Test(link_node, init_orphan_with_value) {
    int value = 10;

    struct ignite_link_node node;
    ignite_link_node_init(&node, &value, NULL, NULL);

    cr_expect_eq(*(int *)node.data, value);
    cr_expect_null(node.next);
    cr_expect_null(node.prev);
}

Test(link_node, chain_two_orphan) {
    int value0 = 10;
    int value1 = 20;

    struct ignite_link_node node0;
    ignite_link_node_init(&node0, &value0, NULL, NULL);
    struct ignite_link_node node1;
    ignite_link_node_init(&node1, &value1, NULL, NULL);

    cr_expect_eq(*(int *)node0.data, value0);
    cr_expect_null(node0.next);
    cr_expect_null(node0.prev);

    cr_expect_eq(*(int *)node1.data, value1);
    cr_expect_null(node1.next);
    cr_expect_null(node1.prev);

    ignite_link_node_chain(&node0, &node1);

    cr_expect_not_null(node0.next);
    cr_expect_not_null(node1.prev);

    cr_expect_eq(node0.next, &node1);
    cr_expect_eq(node1.prev, &node0);
}

Test(link_node, chain_cirqle) {
    int value0 = 10;
    int value1 = 20;

    struct ignite_link_node node0;
    ignite_link_node_init(&node0, &value0, NULL, NULL);
    struct ignite_link_node node1;
    ignite_link_node_init(&node1, &value1, NULL, NULL);

    cr_expect_eq(*(int *)node0.data, value0);
    cr_expect_null(node0.next);
    cr_expect_null(node0.prev);

    cr_expect_eq(*(int *)node1.data, value1);
    cr_expect_null(node1.next);
    cr_expect_null(node1.prev);

    ignite_link_node_chain(&node0, &node1);
    ignite_link_node_chain(&node1, &node0);

    cr_expect_not_null(node0.next);
    cr_expect_not_null(node1.prev);

    cr_expect_eq(node0.next, &node1);
    cr_expect_eq(node0.prev, &node1);
    cr_expect_eq(node1.next, &node0);
    cr_expect_eq(node1.prev, &node0);
}

