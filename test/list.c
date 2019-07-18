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

bool test_list_null()
{
    bool passed = true;
    int_list *list = NULL;
    check_assertion(!list_head(list));
    check_assertion(!list_tail(list));
    check_assertion(list_is_empty(list));
    check_assertion(is_circular(list));
    check_assertion(!contains(list, 0));
    return passed;
}

bool test_list_append()
{
    bool passed = true;
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        check_assertion(!contains(list, i));
        int_list *node = int_list_new(i);
        list_append(list, node);;
        check_assertion(contains(list, i));
        check_assertion(is_circular(list));
    }

    int_list_delete(list->prev);

    int_list *temp = list->next;
    int_list_delete(list);
    list = temp;

    check_assertion(!contains(list, 0));
    check_assertion(!contains(list, 9));
    check_assertion(is_circular(list));

    temp = list;
    for (int i = 1; temp != list->prev; ++i) {
        check_assertion(temp->value == i);
        temp = temp->next;
    }
    check_assertion(temp->value == 8);

    destroy(list);
    return passed;
}

int int_compare(int a, int b)
{
    return a - b;
}

bool test_list_search_custom()
{
    bool passed = true;
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        int_list *node = int_list_new(i);
        list_append(list, node);
    }

    int_list *result = NULL;
    list_search_custom(list, result, 5, int_compare);
    check_assertion(result && result->value == 5);
    destroy(list);
    return passed;
}

bool is_nine(int n)
{
    return n == 9;
}

bool test_list_search_if()
{
    bool passed = true;
    int_list *list = NULL;
    for (int i = 0; i < 10; ++i) {
        int_list *node = int_list_new(i);
        list_append(list, node);
    }

    int_list *result = NULL;
    list_search_if(list, result, is_nine);
    check_assertion(result && result->value == 9);
    destroy(list);
    return passed;
}

bool test_list_search_nonexistent()
{
    bool passed = true;
    int_list *list = NULL;
    int_list *node = int_list_new(0);
    list_append(list, node);

    int_list *result = NULL;
    list_search(list, result, 1);
    check_assertion(!result);

    result = NULL;
    list_search_custom(list, result, 1, int_compare);
    check_assertion(!result);

    result = NULL;
    list_search_if(list, result, is_nine);
    check_assertion(!result);
    destroy(list);
    return passed;
}

int main()
{
    run_test(test_list_null);
    run_test(test_list_append);
    run_test(test_list_search_custom);
    run_test(test_list_search_if);
    run_test(test_list_search_nonexistent);
    return exit_test();
}
