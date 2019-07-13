#pragma once
#include <stdlib.h>

// must be called before declaring any list_node
#define list_node_register_type(type) struct list_node_##type {\
    type value;\
    struct list_node_##type *prev;\
    struct list_node_##type *next;\
}

// shouldn't be called before type has been registered
#define list_node(type) struct list_node_##type

#define list_node_init(node, _value, _prev, _next) do {\
    (node).value = (_value);\
    (node).prev = (_prev);\
    (node).next = (_next);\
} while (0)

// insert left before right (both are pointers)
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
    (node)->prev->next = (node)->next;\
    (node)->next->prev = (node)->prev;\
} while (0)

// dummy is used to get size of a node
// size is the number of elements (excluding sentinel null)
// result is for storing query results
#define list(type) struct {\
    list_node(type) *null;\
    size_t size;\
    list_node(type) dummy;\
    list_node(type) *result;\
}

#define list_init(list) do {\
    (list).size = 0;\
    (list).dummy.prev = NULL;\
    (list).dummy.next = NULL;\
    (list).result = NULL;\
    (list).null = malloc(sizeof((list).dummy));\
    if ((list).null) {\
        (list).null->prev = (list).null;\
        (list).null->next = (list).null;\
    }\
} while (0)

#define list_is_empty(list) ((list).size == 0)

// returns pointer to head
#define list_head(list) ((list).null->next)

// returns pointer to tail
#define list_tail(list) ((list).null->prev)

// user should save a pointer to the head before deleting,
// so they can free the pointer if needed
#define list_delete_head(list) do {\
    if (!list_is_empty(list)) {\
        list_node_delete(list_head(list));\
        (list).size--;\
    }\
} while (0)

#define list_delete_tail(list) do {\
    if (!list_is_empty(list)) {\
        list_node_delete(list_tail(list));\
        (list).size--;\
    }\
} while (0)

// insert node before the head, node is a pointer
#define list_insert_before_head(list, node) do {\
    list_node_insert_after((list).null, (node));\
    (list).size++;\
} while (0)

#define list_insert_after_tail(list, node) do {\
    list_node_insert_before((node), (list).null);\
    (list).size++;\
} while (0)

// doesn't free dynamically allocated nodes
#define list_destroy(list) do {\
    while (!list_is_empty(list)) {\
        list_delete_head(list);\
    }\
    free((list).null);\
    (list).null = NULL;\
    (list).result = NULL;\
} while (0)

// stores result in list.result
#define list_search(list, _value) do {\
    (list).null->value = (_value);\
    (list).result = list_head(list);\
    while ((list).result->value != (_value)) {\
        (list).result = (list).result->next;\
    }\
} while (0)
