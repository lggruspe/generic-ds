#pragma once
#include <assert.h>
#include <stddef.h>

// circular doubly-linked list
// empty list is just a null pointer
// the list pointer should point to the head if it's nonempty
#define list_register(name, type) \
\
struct name {\
    type value;\
    struct name *prev;\
    struct name *next;\
};\
\
struct name *name##_new(type value)\
{\
    struct name *node = malloc(sizeof(struct name));\
    if (node) {\
        node->value = value;\
        node->next = node;\
        node->prev = node;\
    }\
    return node;\
}\
\
struct name *name##_delete(struct name *list)\
{\
    struct name *node = list;\
    list = list_delete(list);\
    free(node);\
    return list;\
}\
\
void name##_destroy(struct name *list)\
{\
    while (!list_is_empty(list)) {\
        struct name *node = list;\
        list = list_delete(list);\
        free(node);\
    }\
}

#define list_create() (NULL)
#define list_head(list) (list)
#define list_tail(list) ((list) ? (list)->prev : NULL)
#define list_is_empty(list) (!(list))

// append suffix to list
#define list_append(list, suffix) (\
        (!(list) ? (suffix) : !(suffix) ? (list) : \
         ( \
            ((list)->prev->next = (suffix)->prev),\
            ((suffix)->prev = (list)->prev),\
            ((list)->prev = (list)->prev->next),\
            ((list)->prev->next = (list)),\
            ((suffix)->prev->next = (suffix)),\
            (list)\
        )))

// deletes the node that list points to
// caller should save a pointer to list->next before calling
#define list_delete(list) \
    ( \
    ((list) ? \
    (((list)->next->prev = (list)->prev),\
    ((list)->prev->next = (list)->next))\
    : NULL),\
    ((list)->next != (list) ? (list)->next : NULL))

// list and result are both pointers to lists
// points result to the first matching node
// result is passed by reference
#define list_search(list, result, _value) do {\
    if (list) {\
        (result) = (list)->next;\
        while ((result) != (list) && (result)->value != (_value)) {\
            (result) = (result)->next;\
        }\
        if ((result) == (list) && (result)->value != (_value)) {\
            (result) = NULL;\
        }\
    } else {\
        (result) = NULL;\
    }\
} while (0)

// same as list_search, but with a custom comparator
// the comparator should take list->values as inputs
// and return -1 (<), 0 (=) or 1 (>)
#define list_search_custom(list, result, _value, compare) do {\
    if (list) {\
        (result) = (list)->next;\
        while ((result) != (list) && (compare)((result)->value, (_value))) {\
            (result) = (result)->next;\
        }\
        if ((result) == (list) && (compare)((result)->value, (_value))) {\
            (result) = NULL;\
        }\
    } else {\
        (result) = NULL;\
    }\
} while (0)

// points result to the first list that satisfies the predicate
// if there are none, result is set to NULL
// result is passed by reference
#define list_search_if(list, result, predicate) do {\
    if (list) {\
        (result) = (list)->next;\
        while ((result) != (list) && !(predicate)((result)->value)) {\
            (result) = (result)->next;\
        }\
        if ((result) == (list) && !(predicate)((result)->value)) {\
            (result) = NULL;\
        }\
    } else {\
        (result) = NULL;\
    }\
} while (0)
