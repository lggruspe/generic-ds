#pragma once
#include <assert.h>
#include <stdlib.h>

// NOTE passing the address of a stack-allocated node causes warnings
// using malloced-nodes prevents these warnings

// must be called before declaring any list_node
#define list_node_register_type(name, type) struct name {\
    type value;\
    struct name *prev;\
    struct name *next;\
}

#define list_node_init(node, _value, _prev, _next) do {\
    assert(node);\
    (node)->value = (_value);\
    (node)->prev = (_prev);\
    (node)->next = (_next);\
} while (0)

// insert left before right (both are pointers)
// NOTE if called as list_node_insert_before(&x, &y)
// make sure that the address of the new node is not already in the list
// otherwise, the list breaks
// using malloced nodes might be more error-prone
#define list_node_insert_before(left, right) do {\
    (left)->next = (right);\
    (left)->prev = (right)->prev;\
    (left)->prev->next = (left);\
    (right)->prev = (left);\
} while (0)

// insert right after left (both pointers)
#define list_node_insert_after(left, right) do {\
    (right)->prev = (left);\
    (right)->next = (left)->next;\
    (right)->next->prev = (right);\
    (left)->next = (right);\
} while (0)

// deletes a node, given pointer
// doesn't free the node if dynamicall allocated
#define list_node_delete(node) do {\
    assert(node);\
    (node)->prev->next = (node)->next;\
    (node)->next->prev = (node)->prev;\
} while (0)

#define list_node_delete_and_free(node) do {\
    assert(node);\
    void *temp = node;\
    list_node_delete(node);\
    free(temp);\
} while (0)

// node_type is the typename registered with list_node_register_type
// dummy is used to get size of a node
// size is the number of elements (excluding sentinel null)
// result is for storing query results
#define list(node_type) struct {\
    node_type *null;\
    size_t size;\
    node_type dummy;\
    node_type *result;\
}

#define list_init(list) do {\
    (list)->size = 0;\
    (list)->result = NULL;\
    (list)->null = malloc(sizeof((list)->dummy));\
    if ((list)->null) {\
        (list)->null->prev = (list)->null;\
        (list)->null->next = (list)->null;\
    }\
} while (0)

#define list_is_empty(list) ((list)->size == 0)

// returns pointer to head
#define list_head(list) ((list)->null->next)

// returns pointer to tail
#define list_tail(list) ((list)->null->prev)

// doesn't free node
#define list_delete(list, node) do {\
    if (!list_is_empty(list)) {\
        list_node_delete(node);\
        (list)->size--;\
    }\
} while (0)

// NOTE for some reason, doesn't work for
// list_delete_and_free(list, list_head(list))
// but works if list_head(list) is assigned to a variable first:
// list_delete_and_free(list, node)
#define list_delete_and_free(list, node) do {\
    if (!list_is_empty(list)) {\
        list_node_delete_and_free(node);\
        (list)->size--;\
    }\
} while (0)

// insert node before the head, node is a pointer
#define list_insert_before_head(list, node) do {\
    list_node_insert_after((list)->null, (node));\
    (list)->size++;\
} while (0)

#define list_insert_after_tail(list, node) do {\
    list_node_insert_before((node), (list)->null);\
    (list)->size++;\
} while (0)

// doesn't free dynamically allocated nodes
#define list_destroy(list) do {\
    while (!list_is_empty(list)) {\
        list_delete((list), list_head(list));\
    }\
    if ((list)->null) {\
        free((list)->null);\
        (list)->null = NULL;\
    }\
    (list)->result = NULL;\
} while (0)

#define list_destroy_and_free(list) do {\
    while (!list_is_empty(list)) {\
        list_delete_and_free((list), list_head(list));\
    }\
    if ((list)->null) {\
        free((list)->null);\
        (list)->null = NULL;\
    }\
    (list)->result = NULL;\
} while (0)

// stores result in list.result
#define list_search(list, _value) do {\
    assert((list)->null);\
    (list)->null->value = (_value);\
    (list)->result = list_head(list);\
    assert((list)->result);\
    while ((list)->result->value != (_value)) {\
        (list)->result = (list)->result->next;\
    }\
} while (0)

// compare(a, b) = -1 if a < b, 0 if a = b and 1 if a > b
// where a and b have the same type as the type parameter to list
#define list_search_custom(list, _value, comparator) do {\
    (list)->null->value = (_value);\
    (list)->result = list_head(list);\
    while ((comparator)((list)->result->value, (_value))) {\
        (list)->result = (list)->result->next;\
    }\
} while (0)

// assume: predicate(sample) is true
#define list_search_if(list, predicate, sample) do {\
    (list)->null->value = (sample);\
    (list)->result = list_head(list);\
    while (!(predicate)((list)->result->value)) {\
        (list)->result = (list)->result->next;\
    }\
} while (0)

// temp
#define list_delete_head(list) do {\
    list_delete((list), list_head(list));\
} while (0)

#define list_delete_tail(list) do {\
    list_delete((list), list_tail(list));\
} while (0)
