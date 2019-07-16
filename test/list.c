#include "list.h"
#include "test_lib.h"
#include <stdbool.h>
#include <string.h>

#define test_list_setup(node_type) bool passed = true;\
list(node_type) list;\
list_init(list)

#define test_list_teardown() list_destroy(list); return passed

typedef 
list_node_register_type(list_node_char, char)
list_node_char;

typedef 
list_node_register_type(list_node_string, const char *)
list_node_string;

bool test_list_init()
{
    test_list_setup(list_node_char);
    check_assertion(!list.result);
    check_assertion(list.size == 0);
    check_assertion(list.null->next == list.null);
    check_assertion(list.null->prev == list.null);
    test_list_teardown();
}

bool test_list_is_empty()
{
    test_list_setup(list_node_char);
    check_assertion(list_is_empty(list));
    list_node_char node;
    list_node_init(node, 0, list.null, list.null);
    list_insert_before_head(list, &node);
    check_assertion(!list_is_empty(list));
    list_delete_head(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_head()
{
    test_list_setup(list_node_char);
    check_assertion(list_head(list) == list.null);
    list_node_char node;
    list_node_init(node, 'a', list.null, list.null);
    list_insert_before_head(list, &node);
    check_assertion(list_head(list) != list.null);
    check_assertion(list_head(list)->value == 'a');
    check_assertion(list_head(list) == list_tail(list));
    list_delete_head(list);
    check_assertion(list_head(list) == list.null);
    test_list_teardown();
}

bool test_list_tail()
{
    test_list_setup(list_node_char);
    check_assertion(list_tail(list) == list.null);
    list_node_char node;
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
    test_list_setup(list_node_char);
    list_delete_head(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_delete_tail()
{
    test_list_setup(list_node_char);
    list_delete_tail(list);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_destroy()
{
    test_list_setup(list_node_char);
    list_destroy(list);
    check_assertion(!list.null);
    check_assertion(!list.result);
    check_assertion(list_is_empty(list));
    test_list_teardown();
}

bool test_list_search()
{
    test_list_setup(list_node_char);
    list_search(list, 'a');
    check_assertion(list.result == list.null);

    list_node_char node;
    list_node_init(node, 'b', list.null, list.null);
    list_insert_before_head(list, &node);
    list_search(list, 'b');
    check_assertion(list.result == list_head(list));

    list_search(list, 'c');
    check_assertion(list.result == list.null);
    test_list_teardown();
}

int test_list_search_custom_comparator(char a, char b)
{
    if (a < b) {
        return -1;
    } else if (a == b) {
        return 0;
    } else {
        return 1;
    }
}

bool test_list_search_custom()
{
    test_list_setup(list_node_char);
    list_node_char node;
    list_node_init(node, 'b', list.null, list.null);
    list_insert_before_head(list, &node);
    list_search_custom(list, 'b', test_list_search_custom_comparator);
    check_assertion(list.result == list_head(list));
    check_assertion(list.result != list.null);
    test_list_teardown();
}

bool test_list_search_if_predicate(char a)
{
    return '0' <= a && a <= '9';
}

bool test_list_search_if()
{
    test_list_setup(list_node_char);
    list_node_char node;
    list_node_init(node, 'b', list.null, list.null);
    list_insert_before_head(list, &node);
    list_search_if(list, test_list_search_if_predicate, '0');
    check_assertion(list.result == list.null);

    list_node_init(node, '4', list.null, list.null);
    list_insert_after_tail(list, &node);
    list_search_if(list, test_list_search_if_predicate, '0');
    check_assertion(list.result != list.null);
    check_assertion(list.result == list_tail(list));
    test_list_teardown();
}

bool test_list_string()
{
    test_list_setup(list_node_string);
    list_node_string hello;
    list_node_init(hello, "hello", NULL, NULL);

    list_node_string space;
    list_node_init(space, " ", NULL, NULL);

    list_node_string world;
    list_node_init(world, "world", NULL, NULL);

    list_node_string bang;
    list_node_init(bang, "!\n", NULL, NULL);

    list_insert_after_tail(list, &hello);
    list_insert_after_tail(list, &space);
    list_insert_after_tail(list, &world);
    list_insert_after_tail(list, &bang);

    list_search_custom(list, "hello", strcmp);
    check_assertion(list.result == &hello);
    list_search_custom(list, " ", strcmp);
    check_assertion(list.result == &space);
    list_search_custom(list, "world", strcmp);
    check_assertion(list.result == &world);
    list_search_custom(list, "!\n", strcmp);
    check_assertion(list.result == &bang);
    test_list_teardown();
}

bool test_list_traverse()
{
    test_list_setup(list_node_char);

    list_node_char a, b, c;
    list_node_init(a, 'a', NULL, NULL);
    list_node_init(b, 'b', NULL, NULL);
    list_node_init(c, 'c', NULL, NULL);

    list_insert_before_head(list, &b);
    list_insert_before_head(list, &a);
    list_insert_after_tail(list, &c);

    list_node_char *node = list_head(list);
    check_assertion(node == &a);
    check_assertion(node->next == &b);
    check_assertion(node->next->next = &c);
    check_assertion(node->next->next->next == list.null);

    node = list_tail(list);
    check_assertion(node == &c);
    check_assertion(node->prev == &b);
    check_assertion(node->prev->prev == &a);
    check_assertion(node->prev->prev->prev == list.null);
    test_list_teardown();
}

list_node_char *test_list_dynamic_new(
        char value, 
        list_node_char *prev, 
        list_node_char *next)
{
    list_node_char *node = malloc(sizeof(list_node_char));
    list_node_init(*node, value, prev, next);
    return node;
}


bool test_list_dynamic()
{
    test_list_setup(list_node_char);

    for (char c = 'a'; c <= 'z'; ++c) {
        list_node_char *node1 = test_list_dynamic_new(c, NULL, NULL);
        list_node_char *node2 = test_list_dynamic_new(c, NULL, NULL);
        list_insert_before_head(list, node1);
        list_insert_after_tail(list, node2);
    }
    check_assertion(list.size == 52);

    list_node_char *node = list_head(list);
    for (size_t c = 'z'; c >= 'a'; --c) {
        check_assertion(node && c == node->value);
        node = node->next;
    }
    for (size_t c = 'a'; c <= 'z'; ++c) {
        check_assertion(node && c == node->value);
        node = node->next;
    }

    list_search(list, 'z');
    check_assertion(list.result && list.result->value == 'z');
    check_assertion(list.result == list_head(list));
    check_assertion(list.result != list_tail(list));

    list_delete_and_free(list, list_head(list));
    check_assertion(list.size == 51);

    node = list_head(list);
    check_assertion(node && node->value == 'y');
    node = list_tail(list);
    check_assertion(node && node->value == 'z');

    /*
    list_search(list, 'z');
    check_assertion(list.result && list.result->value == 'z');
    check_assertion(list.result == list_tail(list));
    check_assertion(list.result != list_head(list));

    list_delete_and_free(list, list_tail(list));
    check_assertion(list.size == 50);
    list_search(list, 'z');
    check_assertion(!list.result);
    */

    //list_destroy_and_free(list);
    //check_assertion(list_is_empty(list));
    return passed;
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
    run_test(test_list_search_custom, "test_list_search_custom");
    run_test(test_list_search_if, "test_list_search_if");
    run_test(test_list_traverse, "test_list_traverse");
    run_test(test_list_dynamic, "test_list_dynamic");
    return exit_test();
}
