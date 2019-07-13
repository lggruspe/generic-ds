#include "list.h"
#include "test_lib.h"
#include <stdbool.h>

#define test_list_setup(type) bool passed = false; list(type) list; list_init(list)
#define test_list_teardown() list_destroy(list); return passed

list_node_register_type(char);

bool test_list_init()
{
    test_list_setup(char);
    check_assertion(!list.result);
    check_assertion(list.size == 0);
    check_assertion(list.null->next == list.null);
    check_assertion(list.null->prev == list.null);
    test_list_teardown();
}

bool test_list_is_empty()
{
    test_list_setup(char);
    check_assertion(list_is_empty(list));
    list_node(char) node;
    list_node_init(node, 0, list.null, list.null);
    list_insert_before_head(list, &node);
    check_assertion(!list_is_empty(list));
    list_delete_head(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_head()
{
    test_list_setup(char);
    check_assertion(list_head(list) == list.null);
    list_node(char) node;
    list_node_init(node, 'a', list.null, list.null);
    list_insert_before_head(list, &node);
    check_assertion(list_head(list) != list.null);
    check_assertion(list_head(list)->value == 'a');
    list_delete_head(list);
    check_assertion(list_head(list) == list.null);
    test_list_teardown();
}

bool test_list_tail()
{
    test_list_setup(char);
    check_assertion(list_tail(list) == list.null);
    list_node(char) node;
    list_node_init(node, 'a', list.null, list.null);
    list_insert_after_tail(list, &node);
    check_assertion(list_tail(list) != list.null);
    check_assertion(list_tail(list)->value == 'a');
    list_delete_tail(list);
    check_assertion(list_tail(list) == list.null);
    test_list_teardown();
}

bool test_list_delete_head()
{
    test_list_setup(char);
    list_delete_head(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_delete_tail()
{
    test_list_setup(char);
    list_delete_tail(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_destroy()
{
    test_list_setup(char);
    list_destroy(list);
    check_assertion(!list.null);
    check_assertion(!list.result);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_search()
{
    test_list_setup(char);
    list_search(list, 'a');
    check_assertion(list.result == list.null);

    list_node(char) node;
    list_node_init(node, 'b', list.null, list.null);
    list_insert_before_head(list, &node);
    list_search(list, 'b');
    check_assertion(list.result == list_head(list));

    list_search(list, 'c');
    check_assertion(list.result == list.null);
    test_list_teardown();
}

int main()
{
    run_test(test_list_init, "test_list_init");
    run_test(test_list_is_empty, "test_list_is_empty");
    run_test(test_list_head, "test_list_head");
    run_test(test_list_tail, "test_list_tail");
    run_test(test_list_delete_head, "test_list_delete_head");
    run_test(test_list_delete_tail, "test_list_delete_tail");
    run_test(test_list_destroy, "test_list_destroy");
    run_test(test_list_search, "test_list_search");
    return exit_test();
}
