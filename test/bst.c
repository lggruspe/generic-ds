#include "bst.h"
#include "test_lib.h"
#include <stdlib.h>
#include <string.h>

#define test_bst_setup(type) bool passed = true;\
bst(type) tree;\
bst_init(tree)

#define test_bst_teardown() return passed

typedef bst_register_node_type(bst_node_char, char, void*) bst_node_char;

typedef bst_register_node_type(bst_node_string_int, const char*, int) bst_node_string_int;

bool test_bst_init()
{
    test_bst_setup(bst_node_char);
    check_assertion(!(tree.root));
    check_assertion(!(tree.result));
    check_assertion(tree.size == 0);
    test_bst_teardown();
}

bool test_bst_set()
{
    test_bst_setup(bst_node_char);
    bst_node_char a;
    bst_node_init(a, 'a', NULL, NULL, NULL, NULL);
    bst_node_char aa;
    bst_node_init(aa, 'a', NULL, NULL, NULL, NULL);
    bst_node_char b;
    bst_node_init(b, 'b', NULL, NULL, NULL, NULL);
    bst_node_char bb;
    bst_node_init(bb, 'b', NULL, NULL, NULL, NULL);

    check_assertion(tree.size == 0);
    bst_insert(tree, &a);
    check_assertion(tree.size == 1);
    bst_insert(tree, &aa);
    check_assertion(tree.size == 1);
    bst_insert(tree, &b);
    check_assertion(tree.size == 2);
    bst_insert(tree, &bb);
    check_assertion(tree.size == 2);

    bst_search(tree, 'c');
    check_assertion(!tree.result);

    bst_search(tree, 'a');
    check_assertion(tree.result == &aa);
    check_assertion(tree.result != &a);

    bst_delete(tree, &aa);
    check_assertion(tree.size == 1);
    bst_search(tree, 'a');
    check_assertion(!tree.result);
    test_bst_teardown();
}

bool test_bst_map()
{
    test_bst_setup(bst_node_string_int);
    bst_node_string_int a;
    bst_node_init(a, "a", 1, NULL, NULL, NULL);
    bst_node_string_int b;
    bst_node_init(b, "b", 1, NULL, NULL, NULL);
    bst_node_string_int aa;
    bst_node_init(aa, "a", 2, NULL, NULL, NULL);
    bst_node_string_int bb;
    bst_node_init(bb, "b", 2, NULL, NULL, NULL);
    check_assertion(tree.size == 0);

    bst_insert_custom(tree, &a, strcmp);
    check_assertion(tree.size == 1);
    bst_search_custom(tree, "a", strcmp);
    check_assertion(strcmp(tree.result->key, "a") == 0);
    check_assertion(tree.result->value == 1);

    bst_insert_custom(tree, &aa, strcmp);
    check_assertion(tree.size == 1);
    bst_search_custom(tree, "a", strcmp);
    check_assertion(strcmp(tree.result->key, "a") == 0);
    check_assertion(tree.result->value == 2);

    bst_insert_custom(tree, &b, strcmp);
    check_assertion(tree.size == 2);
    bst_search_custom(tree, "b", strcmp);
    check_assertion(strcmp(tree.result->key, "b") == 0);
    check_assertion(tree.result->value == 1);

    bst_insert_custom(tree, &bb, strcmp);
    check_assertion(tree.size == 2);
    bst_search_custom(tree, "b", strcmp);
    check_assertion(tree.result->value == 2);

    bst_delete(tree, &aa);
    bst_search_custom(tree, "a", strcmp);
    check_assertion(tree.size == 1);
    check_assertion(!tree.result);
    test_bst_teardown();
}

int main()
{
    run_test(test_bst_init, "test_bst_init");
    run_test(test_bst_set, "test_bst_set");
    run_test(test_bst_map, "test_bst_map");
    return exit_test();
}
