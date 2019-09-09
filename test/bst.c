#include "bst.h"
#include "test_lib.h"
#include <string.h>

bst_register(ti, int)
bst_register(ts, const char *)

unit_test(test_bst_init)
{
    bst(ts) tree = NULL;
    assert_true(!bst_search(ts, tree, ""));
    assert_true(!bst_search_compare(ts, tree, "", strcmp));
    bst_destroy(ts, tree);
}

unit_test(test_bst_int)
{
    bst(ti) tree = NULL;
    for (int i = 0; i < 3; ++i) {
        tree = bst_insert(ti, tree, bst_new(ti, 2-i));
    }
    assert_true(bst_is_binary_search_tree(ti, tree));

    bst(ti) result = bst_minimum(ti, tree);
    for (int i = 0; i < 3; ++i) {
        assert_true(result && result->data == i);
        result = bst_successor(ti, result);
    }
    assert_true(!result);

    result = bst_maximum(ti, tree);
    for (int i = 2; i >= 0; --i) {
        assert_true(result && result->data == i);
        result = bst_predecessor(ti, result);
    }
    assert_true(!result);

    for (int i = 0; i < 3; ++i) {
        result = bst_search(ti, tree, i);
        assert_true(result && result->data == i);
        tree = bst_delete_and_free(ti, tree, result);
        result = bst_search(ti, tree, i);
        assert_true(!result);
    }
    assert_true(!tree);
    bst_destroy(ti, tree);
}

unit_test(test_bst_string)
{
    const char *array[] = {"a", "b", "c"};
    bst(ts) tree = NULL;
    for (int i = 0; i < 3; ++i) {
        tree = bst_insert_compare(ts, tree, bst_new(ts, array[2-i]), strcmp);
    }
    assert_true(bst_is_binary_search_tree_compare(ts, tree, strcmp));

    bst(ts) result = bst_minimum(ts, tree);
    for (int i = 0; i < 3 && result; ++i) {
        assert_true(result && strcmp(result->data, array[i]) == 0);
        result = bst_successor(ts, result);
    }
    assert_true(!result);

    result = bst_maximum(ts, tree);
    for (int i = 2; i >= 0; --i) {
        assert_true(result && strcmp(result->data, array[i]) == 0);
        result = bst_predecessor(ts, result);
    }
    assert_true(!result);

    for (int i = 0; i < 3; ++i) {
        result = bst_search_compare(ts, tree, array[i], strcmp);
        assert_true(result && strcmp(result->data, array[i]) == 0);
        tree = bst_delete_and_free(ts, tree, result);
        result = bst_search_compare(ts, tree, array[i], strcmp);
        assert_true(!result);
    }
    assert_true(!tree);
    bst_destroy(ts, tree);
}

int main()
{
    run_unit_test(test_bst_init);
    run_unit_test(test_bst_int);
    run_unit_test(test_bst_string);
    return exit_test();
}
