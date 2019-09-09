#include "rb.h"
#include "test_lib.h"
#include <string.h>

rb_register(ri, int)
rb_register(rs, const char *)

unit_test(test_rb_init)
{
    rb(rs) tree = NULL;
    assert_true(!rb_search(rs, tree, ""));
    assert_true(!rb_search_compare(rs, tree, "", strcmp));
    rb_destroy(rs, tree);
}

unit_test(test_rb_int)
{
    rb(ri) tree = NULL;
    for (int i = 0; i < 3; ++i) {
        tree = rb_insert(ri, tree, rb_new(ri, 2-i));
    }
    assert_true(rb_is_balanced(ri, tree));
    assert_true(rb_is_red_black_tree(ri, tree));

    rb(ri) result = rb_minimum(ri, tree);
    for (int i = 0; i < 3; ++i) {
        assert_true(result && result->data == i);
        result = rb_successor(ri, result);
    }
    assert_true(!result);

    result = rb_maximum(ri, tree);
    for (int i = 2; i >= 0; --i) {
        assert_true(result && result->data == i);
        result = rb_predecessor(ri, result);
    }
    assert_true(!result);

    for (int i = 0; i < 3; ++i) {
        result = rb_search(ri, tree, i);
        assert_true(result && result->data == i);
    }
    rb_destroy(ri, tree);
}

unit_test(test_rb_string)
{
    const char *array[] = {"a", "b", "c"};
    rb(rs) tree = NULL;
    for (int i = 0; i < 3; ++i) {
        tree = rb_insert_compare(rs, tree, rb_new(rs, array[2-i]), strcmp);
    }
    assert_true(rb_is_balanced(rs, tree));
    assert_true(rb_is_red_black_tree_compare(rs, tree, strcmp));

    rb(rs) result = rb_minimum(rs, tree);
    for (int i = 0; i < 3 && result; ++i) {
        assert_true(result && strcmp(result->data, array[i]) == 0);
        result = rb_successor(rs, result);
    }
    assert_true(!result);

    result = rb_maximum(rs, tree);
    for (int i = 2; i >= 0; --i) {
        assert_true(result && strcmp(result->data, array[i]) == 0);
        result = rb_predecessor(rs, result);
    }
    assert_true(!result);

    for (int i = 0; i < 3; ++i) {
        result = rb_search_compare(rs, tree, array[i], strcmp);
        assert_true(result && strcmp(result->data, array[i]) == 0);
    }
    rb_destroy(rs, tree);
}

unit_test(test_rb_balanced)
{
    rb(ri) tree = NULL;
    for (int i = 0; i < 100; ++i) {
        tree = rb_insert(ri, tree, rb_new(ri, i));
        assert_true(rb_is_red_black_tree(ri, tree));
        assert_true(rb_weight(ri, tree) == i+1);
        rb(ri) result = rb_maximum(ri, tree);
        assert_true(result && result->data == i);
    }

    for (int i = 0; i < 100; ++i) {
        rb(ri) result = rb_search(ri, tree, i);
        assert_true(result && result->data == i);
    }
    rb_destroy(ri, tree);
}

int main()
{
    run_unit_test(test_rb_init);
    run_unit_test(test_rb_int);
    run_unit_test(test_rb_string);
    run_unit_test(test_rb_balanced);
    return exit_test();
}
