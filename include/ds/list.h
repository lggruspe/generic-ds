#pragma once
#include "generator.h"
#include <stdbool.h>
#include <stdlib.h>

/* missing operations:
 * - splice lists
 * - change value pointed to by operator
 */

#define List(Namespace) struct Namespace##_list_type

#define ListNode(Namespace) struct Namespace##_list_node_type

#define LIST_GENERATE(Namespace, Type) \
 \
ListNode(Namespace) { \
    Type data; \
    ListNode(Namespace) *left; \
    ListNode(Namespace) *right;     \
}; \
 \
List(Namespace) { \
    ListNode(Namespace) *head; \
}; \
 \
static inline List(Namespace) Namespace##_create() \
{ \
    return (List(Namespace)){ .head = NULL }; \
} \
 \
static inline bool Namespace##_is_empty(List(Namespace) const *l) \
{ \
    return !l->head; \
} \
 \
static inline ListNode(Namespace) *Namespace##_new_node(Type data) \
{ \
    ListNode(Namespace) *node = malloc(sizeof(ListNode(Namespace))); \
    if (node) { \
        node->data = data; \
        node->left = node; \
        node->right = node; \
    } \
    return node; \
} \
 \
static inline void Namespace##_delete_node(List(Namespace) *l, ListNode(Namespace) *node) \
{ \
    node->left->right = node->right; \
    node->right->left = node->left; \
    if (node == l->head) { \
        l->head = node == node->right \
            ? NULL \
            : node->right; \
    } \
    free(node); \
} \
 \
static inline bool Namespace##_push(List(Namespace) *l, Type data) \
{ \
    ListNode(Namespace) *node = Namespace##_new_node(data); \
    if (!node) { \
        return false; \
    } \
    if (!l->head) { \
        l->head = node; \
    } else { \
        ListNode(Namespace) *tail = l->head->left; \
        node->left = tail; \
        node->right = l->head; \
        tail->right = node; \
        l->head->left = node; \
    } \
    return true; \
} \
 \
static inline Type Namespace##_peek(List(Namespace) const *l) \
{ \
    return l->head->left->data; \
} \
 \
static inline Type Namespace##_pop(List(Namespace) *l) \
{ \
    Type data; \
    if (!Namespace##_is_empty(l)) { \
        data = Namespace##_peek(l); \
        Namespace##_delete_node(l, l->head->left); \
    } \
    return data; \
} \
 \
static inline bool Namespace##_push_left(List(Namespace) *l, Type data) \
{ \
    if (!Namespace##_push(l, data)) { \
        return false; \
    } \
    l->head = l->head->left; \
    return true; \
} \
 \
static inline Type Namespace##_peek_left(List(Namespace) const *l) \
{ \
    return l->head->data; \
} \
 \
static inline Type Namespace##_pop_left(List(Namespace) *l) \
{ \
    Type data; \
    if (!Namespace##_is_empty(l)) { \
        data = Namespace##_peek_left(l); \
        ListNode(Namespace) *heir = l->head->right; \
        Namespace##_delete_node(l, l->head); \
    } \
    return data; \
} \
 \
static inline void Namespace##_clear(List(Namespace) *l) \
{ \
 \
    while (!Namespace##_is_empty(l)) { \
        Namespace##_pop(l); \
    } \
} \
 \
static inline void Namespace##_destroy(List(Namespace) *l) \
{ \
    Namespace##_clear(l); \
} \
 \
GENERATOR(Type, Namespace##_iterate, List(Namespace) const *l) \
{ \
    static ListNode(Namespace) *node; \
    node = l->head; \
    do { \
        yield(node->data); \
        node = node->right; \
    } while (node != l->head); \
    stop_generator(); \
} \
 \
struct { \
    List(Namespace) (*create)(void); \
    void (*destroy)(List(Namespace)*); \
    bool (*is_empty)(List(Namespace) const*); \
    bool (*push)(List(Namespace)*, Type); \
    Type (*peek)(List(Namespace) const*); \
    Type (*pop)(List(Namespace)*); \
    bool (*push_left)(List(Namespace)*, Type); \
    Type (*peek_left)(List(Namespace) const*); \
    Type (*pop_left)(List(Namespace)*); \
    void (*clear)(List(Namespace)*); \
    Type (*iterate)(Iterator*, List(Namespace) const*); \
} Namespace = { \
    .create = Namespace##_create, \
    .destroy = Namespace##_destroy, \
    .is_empty = Namespace##_is_empty, \
    .push = Namespace##_push, \
    .peek = Namespace##_peek, \
    .pop = Namespace##_pop, \
    .push_left = Namespace##_push_left, \
    .peek_left = Namespace##_peek_left, \
    .pop_left = Namespace##_pop_left, \
    .clear = Namespace##_clear, \
    .iterate = Namespace##_iterate, \
};

/* usage:
 * Iterator it = create_iterator();
 * for (int a = list.iterate(&it, &l); !it.done; a = list.iterate(&it, &l)) {
 *  ...
 * }
 */
