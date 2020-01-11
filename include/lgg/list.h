#pragma once
#include "ds.h"
#include <stdbool.h>
#include <stdlib.h>

#define NODE_T(Namespace) struct Namespace##_node

#define LIST_T(Namespace) struct Namespace##_list

#define LIST(Namespace) (LIST_T(Namespace)){ .head = NULL }

#define LIST_GENERATE(Namespace, Type) \
 \
NODE_T(Namespace) { \
    Type data; \
    NODE_T(Namespace) *left; \
    NODE_T(Namespace) *right; \
}; \
 \
LIST_T(Namespace) { \
    NODE_T(Namespace) *head; \
}; \
 \
static inline bool Namespace##_is_empty(LIST_T(Namespace) const *list) \
{ \
    return !list->head; \
} \
 \
static inline NODE_T(Namespace) *Namespace##_new_node(Type data) \
{ \
    NODE_T(Namespace) *node = malloc(sizeof(NODE_T(Namespace))); \
    if (node) { \
        node->data = data; \
        node->left = node; \
        node->right = node; \
    } \
    return node; \
} \
 \
static inline bool Namespace##_delete_node(NODE_T(Namespace) *node) \
{ \
    bool head = node->right == node; \
    node->left->right = node->right; \
    node->right->left = node->left; \
    free(node); \
    return head; \
} \
 \
static inline bool Namespace##_push(LIST_T(Namespace) *list, Type data) \
{ \
    NODE_T(Namespace) *node = Namespace##_new_node(data); \
    if (!node) { \
        return false; \
    } \
    if (!list->head) { \
        list->head = node; \
    } else { \
        NODE_T(Namespace) *tail = list->head->left; \
        node->left = tail; \
        node->right = list->head; \
        tail->right = node; \
        list->head->left = node; \
    } \
    return true; \
} \
 \
static inline Type Namespace##_peek(LIST_T(Namespace) const *list) \
{ \
    return list->head->left->data; \
} \
 \
static inline Type Namespace##_pop(LIST_T(Namespace) *list) \
{ \
    Type data; \
    if (!IS_EMPTY(Namespace, list)) { \
        data = PEEK(Namespace, list); \
        if (Namespace##_delete_node(list->head->left)) { \
            list->head = NULL; \
        } \
    } \
    return data; \
} \
 \
static inline bool Namespace##_push_left(LIST_T(Namespace) *list, Type data) \
{ \
    if (!PUSH(Namespace, list, data)) { \
        return false; \
    } \
    list->head = list->head->left; \
    return true; \
} \
 \
static inline Type Namespace##_peek_left(LIST_T(Namespace) const *list) \
{ \
    return list->head->data; \
} \
 \
static inline Type Namespace##_pop_left(LIST_T(Namespace) *list) \
{ \
    Type data; \
    if (!IS_EMPTY(Namespace, list)) { \
        data = PEEK_LEFT(Namespace, list); \
        NODE_T(Namespace) *heir = list->head->right; \
        if (Namespace##_delete_node(list->head)) { \
            heir = NULL; \
        } \
        list->head = heir; \
    } \
    return data; \
} \
 \
static inline void Namespace##_clear(LIST_T(Namespace) *list) \
{ \
    while (!IS_EMPTY(Namespace, list)) { \
        POP(Namespace, list); \
    } \
} \
 \
static inline void Namespace##_destroy(LIST_T(Namespace) *list) \
{ \
    CLEAR(Namespace, list); \
} \
 \
ITER_T(Namespace) { \
    LIST_T(Namespace) *list; \
    NODE_T(Namespace) *current; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin( \
        LIST_T(Namespace) *list) \
{ \
    ITER_T(Namespace) it = { .list = list, .current = list->head, .done = true }; \
    if (!IS_EMPTY(Namespace, list)) { \
        it.done = false; \
        it.value = it.current->data; \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.current = it.current->right; \
        if (it.current == it.list->head) { \
            it.done = true; \
        } else { \
            it.value = it.current->data; \
        } \
    } \
    return it; \
}
