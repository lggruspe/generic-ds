#include "list.h"
#include "test_lib.h"
#include <string.h>

list_register(li, int)
list_register(ls, const char *)

bool is_circular(list(li) list)
{
    if (!list) {
        return true;
    }
    list(li) head = list_head(li, list);
    list(li) tail = list_tail(li, list);
    if (!head || head->prev != tail) {
        return false;
    }
    if (!tail || tail->next != head) {
        return false;
    }
    for (list(li) node = head; node != tail; node = node->next) {
        if (node->prev->next != node || node->next->prev != node) {
            return false;
        }
    }
    return true;
}

bool contains(list(li) list, int item)
{
    list(li) result = list_search(li, list, item);
    return result && result->data == item;
}

unit_test(test_list_null)
{
    list(li) list = NULL;
    assert_true(!list_head(li, list));
    assert_true(!list_tail(li, list));
    assert_true(list_is_empty(li, list));
    assert_true(is_circular(list));
    assert_true(!contains(list, 0));
}

unit_test(test_list_append)
{
    list(li) list = NULL;
    for (int i = 0; i < 10; ++i) {
        assert_true(!contains(list, i));
        list = list_append(li, list, list_new(li, i));
    }
    assert_true(!list_is_empty(li, list));
    for (int i = 0; i < 10; ++i) {
        assert_true(contains(list, i));
    }
    assert_true(is_circular(list));

    list = list_delete_and_free(li, list_head(li, list));
    list = list_delete_and_free(li, list_tail(li, list));
    assert_true(!contains(list, 0));
    assert_true(!contains(list, 9));
    assert_true(is_circular(list));

    list(li) node = list_head(li, list);
    for (int i = 1; node != list_tail(li, list); ++i, node = node->next) {
        assert_true(node->data == i);
    }
    assert_true(node->data == 8);
    list = list_destroy(li, list);
    assert_true(list_is_empty(li, list));
}

int li_compare(int a, int b)
{
    return a - b;
}

bool is_five(int n)
{
    return n == 5;
}

unit_test(test_list_search)
{
    list(li) list = NULL;
    for (int i = 0; i < 10; ++i) {
        list = list_append(li, list, list_new(li, i));
    }
    list(li) res1 = list_search(li, list, 5);
    list(li) res2 = list_search_if(li, list, is_five);
    list(li) res3 = list_search_compare(li, list, 5, li_compare);
    assert_true(res1 == res2 && res2 == res3);
    list_destroy(li, list);
}

bool is_foo(const char *string)
{
    return strcmp(string, "foo") == 0;
}

unit_test(test_list_search_nonexistent)
{
    const char* strings[] = { "Hello", ",", " ", "world", "!", "\n" };
    list(ls) list = NULL;

    for (int i = 0; i < 6; ++i) {
        list = list_append(ls, list, list_new(ls, strings[i]));
    }

    list(ls) result = list_search_compare(ls, list, "world", strcmp);
    assert_true(result && strcmp("world", result->data) == 0);

    result = list_search_compare(ls, list, "foo", strcmp);
    assert_true(!result);
    result = list_search(ls, list, "asdf");
    assert_true(!result);
    result = list_search_if(ls, list, is_foo);
    assert_true(!result);
    list_destroy(ls, list);
}

unit_test(test_list_singleton_destroy)
{
    list(li) list = NULL;
    list = list_append(li, list, list_new(li, 0));
    list_destroy(li, list);
    assert_true(true);
}

int main()
{
    run_unit_test(test_list_null);
    run_unit_test(test_list_append);
    run_unit_test(test_list_search);
    run_unit_test(test_list_search_nonexistent);
    run_unit_test(test_list_singleton_destroy);
    return exit_test();
}
