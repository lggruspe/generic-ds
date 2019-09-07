#include "list.h"
#include "test_lib.h"
#include <stdbool.h>

list_register(list_int, int)
typedef struct list_int list_int;

bool is_circular(list_int *list)
{
    if (!list) {
        return true;
    }
    list_int *node = list;
    while (node && node != list->prev) {
        if ((node->next && node->next->prev != node)
                || (node->prev && node->prev->next != node)) {
            return false;
        }
        node = node->next;
    }
    return !node 
        || (list->prev && list->prev->next == list
        && list->next && list->next->prev == list);
}

bool contains(list_int *list, int item)
{
    list_int *result = NULL;
    list_search(list, result, item);
    return result && result->value == item;
}

unit_test(test_list_null)
{
    list_int *list = NULL;
    assert_true(!list_head(list));
    assert_true(!list_tail(list));
    assert_true(list_is_empty(list));
    assert_true(is_circular(list));
    assert_true(!contains(list, 0));
}

unit_test(test_list_append)
{
    list_int *list = NULL;
    for (int i = 0; i < 10; ++i) {
        assert_true(!contains(list, i));
        list_int *node = list_int_new(i);
        list = list_append(list, node);;
        assert_true(contains(list, i));
        assert_true(is_circular(list));
    }
    list_int_delete(list->prev);
    list_int *temp = list->next;
    list_int_delete(list);
    list = temp;
    assert_true(!contains(list, 0));
    assert_true(!contains(list, 9));
    assert_true(is_circular(list));
    temp = list;
    for (int i = 1; temp != list->prev; ++i) {
        assert_true(temp->value == i);
        temp = temp->next;
    }
    assert_true(temp->value == 8);
    list_int_destroy(list);
}

int int_compare(int a, int b)
{
    return a - b;
}

unit_test(test_list_search_custom)
{
    list_int *list = NULL;
    for (int i = 0; i < 10; ++i) {
        list_int *node = list_int_new(i);
        list = list_append(list, node);
    }

    list_int *result = NULL;
    list_search_custom(list, result, 5, int_compare);
    assert_true(result && result->value == 5);
    list_int_destroy(list);
}

bool is_nine(int n)
{
    return n == 9;
}

unit_test(test_list_search_if)
{
    list_int *list = NULL;
    for (int i = 0; i < 10; ++i) {
        list_int *node = list_int_new(i);
        list = list_append(list, node);
    }

    list_int *result = NULL;
    list_search_if(list, result, is_nine);
    assert_true(result && result->value == 9);
    list_int_destroy(list);
}

unit_test(test_list_search_nonexistent)
{
    list_int *list = NULL;
    list_int *node = list_int_new(0);
    list = list_append(list, node);

    list_int *result = NULL;
    list_search(list, result, 1);
    assert_true(!result);

    result = NULL;
    list_search_custom(list, result, 1, int_compare);
    assert_true(!result);

    result = NULL;
    list_search_if(list, result, is_nine);
    assert_true(!result);
    list_int_destroy(list);
}

int main()
{
    run_unit_test(test_list_null);
    run_unit_test(test_list_append);
    run_unit_test(test_list_search_custom);
    run_unit_test(test_list_search_if);
    run_unit_test(test_list_search_nonexistent);
    return exit_test();
}
