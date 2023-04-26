#include <criterion/criterion.h>

#include "ignite/link_node.h"

void init() {}
void fini() {}

TestSuite(link_node, .init = init, .fini = fini);
