#include "list.h"
#include "test_lib.h"
#include <stdbool.h>

typedef list_register_type(int_list, int) int_list;

int_list *int_list_new(int value)
{
    int_list *list = malloc(sizeof(int_list));
    if (list) {
        list->value = value;
        list->prev = list;
        list->next = list;
    }
    return list;
}

void int_list_delete(int_list *list)
{
    list_delete(list);
    if (list) {
        free(list);
    }
}

bool is_circular(int_list *list)
{
    if (!list) return true;
    int_list *node = list;
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

void destroy(int_list *list)
{
    if (!list) return;

    int_list *tail = list->prev;
    int_list *node = list;
    while (node != tail) {
        int_list *next = node->next;
        int_list_delete(node);
        node = next;
    }
    int_list_delete(tail);
}

bool contains(int_list *list, int item)
{
    int_list *result = NULL;
    list_search(list, result, item);
    return result && result->value == item;
}

unit_test(test_list_null)
{
    int_list *list = NULL;
    assert_true(!list_head(list));
    assert_true(!list_tail(list));
    assert_true(list_is_empty(list));
    assert_true(is_circular(list));
    assert_true(!contains(list, 0));
}

unit_test(test_list_append)
{
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        assert_true(!contains(list, i));
        int_list *node = int_list_new(i);
        list_append(list, node);;
        assert_true(contains(list, i));
        assert_true(is_circular(list));
    }
    int_list_delete(list->prev);
    int_list *temp = list->next;
    int_list_delete(list);
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
    destroy(list);
}

int int_compare(int a, int b)
{
    return a - b;
}

unit_test(test_list_search_custom)
{
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        int_list *node = int_list_new(i);
        list_append(list, node);
    }

    int_list *result = NULL;
    list_search_custom(list, result, 5, int_compare);
    assert_true(result && result->value == 5);
    destroy(list);
}

bool is_nine(int n)
{
    return n == 9;
}

unit_test(test_list_search_if)
{
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        int_list *node = int_list_new(i);
        list_append(list, node);
    }

    int_list *result = NULL;
    list_search_if(list, result, is_nine);
    assert_true(result && result->value == 9);
    destroy(list);
}

unit_test(test_list_search_nonexistent)
{
    int_list *list = NULL;
    int_list *node = int_list_new(0);
    list_append(list, node);

    int_list *result = NULL;
    list_search(list, result, 1);
    assert_true(!result);

    result = NULL;
    list_search_custom(list, result, 1, int_compare);
    assert_true(!result);

    result = NULL;
    list_search_if(list, result, is_nine);
    assert_true(!result);
    destroy(list);
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
