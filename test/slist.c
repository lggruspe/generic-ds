#include "slist.h"
#include "test_lib.h"
#include <string.h>

slist_register(sli, int)
slist_register(sls, const char *)

unit_test(test_slist_null)
{
    slist(sli) list = NULL;
    assert_true(!slist_head(sli, list));
    assert_true(!slist_tail(sli, list));
    assert_true(!slist_search(sli, list, 0));
}

unit_test(test_slist_head_tail)
{
    slist(sli) list = NULL;
    for (int i = 0; i < 10; ++i) {
        list = slist_append(sli, list, slist_new(sli, i));
        slist(sli) head = slist_head(sli, list);
        slist(sli) tail = slist_tail(sli, list);
        assert_true(head && head->data == 0);
        assert_true(tail && tail->data == i);
    }
    slist_destroy(sli, list);
}

unit_test(test_slist_insert_delete_after)
{
    const char *array[] = {"a", "b", "c", "d", "e"};
    slist(sls) list = NULL;
    for (int i = 0; i < 5; ++i) {
        list = slist_insert_after(sls, list, slist_new(sls, array[i]));
    }
    assert_true(list && strcmp(list->data, array[0]) == 0);

    int i = 4;
    for (slist(sls) node = list->next; list && node; node = node->next) {
        assert_true(strcmp(array[i], node->data) == 0);
        --i;
    }

    slist_delete_and_free_after(sls, list);
    list = slist_delete_and_free(sls, list);
    i = 3;
    for (slist(sls) node = list; node; node = node->next) {
        assert_true(strcmp(node->data, array[i]) == 0);
        --i;
    }

    slist_destroy(sls, list);
}

bool is_five(int n)
{
    return n == 5;
}

unit_test(test_slist_search)
{
    slist(sli) list = NULL;
    for (int i = 0; i < 10; ++i) {
        list = slist_insert(sli, list, slist_new(sli, i));
    }
    for (int i = 0; i < 10; ++i) {
        slist(sli) node = slist_search(sli, list, i);
        assert_true(node && node->data == i);
    }
    slist(sli) node = slist_search_if(sli, list, is_five);
    assert_true(node && node->data == 5);
    slist_destroy(sli, list);
}

unit_test(test_slist_search_compare)
{
    const char *strings[] = { "world", "hello" };
    slist(sls) list = NULL;

    for (int i = 0; i < 2; ++i) {
        list = slist_insert(sls, list, slist_new(sls, strings[i]));
    }

    slist(sls) result = slist_search_compare(sls, list, "hello", strcmp);
    assert_true(result && strcmp("hello", result->data) == 0);
    result = slist_search_compare(sls, result, "world", strcmp);
    assert_true(result && strcmp("world", result->data) == 0);

    result = slist_search_compare(sls, list, "foo", strcmp);
    assert_true(!result);
    slist_destroy(sls, list);
}

int main()
{
    run_unit_test(test_slist_null);
    run_unit_test(test_slist_head_tail);
    run_unit_test(test_slist_insert_delete_after);
    run_unit_test(test_slist_search);
    run_unit_test(test_slist_search_compare);
    return exit_test();
}
