#pragma once
#include "ds.h"
#include "bst.h"
#include <stdbool.h>
#include <stdlib.h>

enum rb_color { RB_BLACK = 0, RB_RED };

#define RB_T(Namespace) BST_T(Namespace##_rb)

#define RB(Namespace) (RB_T(Namespace)){ .root = NULL }

#define RB_GENERATE(Namespace, Type, LessThan) \
 \
BST_GENERATE(Namespace##_rb, Type, LessThan, enum rb_color color) \
 \
static inline NODE_T(Namespace##_rb) *Namespace##_new_rb_node(Type data) \
{ \
    NODE_T(Namespace##_rb) *node = malloc(sizeof(NODE_T(Namespace##_rb))); \
    if (node) { \
        node->data = data; \
        node->left = NULL; \
        node->right = NULL; \
        node->parent = NULL; \
        node->color = RB_RED; \
    } \
    return node; \
} \
 \
static inline bool Namespace##_is_empty(RB_T(Namespace) const *tree) \
{ \
    return IS_EMPTY(Namespace##_rb, tree); \
} \
 \
static inline void \
Namespace##_rotate_left(RB_T(Namespace) *tree, NODE_T(Namespace##_rb) *x) \
{ \
    NODE_T(Namespace##_rb) *y = x->right; \
    if (y->left) { \
        y->left->parent = x; \
    } \
    x->right = y->left; \
    y->left = x; \
    y->parent = x->parent; \
    x->parent = y; \
    if (!y->parent) { \
        tree->root = y; \
    } else if (y->parent->left == x) { \
        y->parent->left = y; \
    } else { \
        y->parent->right = y; \
    } \
} \
 \
static inline void \
Namespace##_rotate_right(RB_T(Namespace) *tree, NODE_T(Namespace##_rb) *x) \
{ \
    NODE_T(Namespace##_rb) *y = x->left; \
    if (y->right) { \
        y->right->parent = x; \
    } \
    x->left = y->right; \
    y->right = x; \
    y->parent = x->parent; \
    x->parent = y; \
    if (!y->parent) { \
        tree->root = y; \
    } else if (y->parent->right == x) { \
        y->parent->right = y; \
    } else { \
        y->parent->left = y; \
    } \
} \
 \
static inline void \
Namespace##_repair(RB_T(Namespace) *tree, NODE_T(Namespace##_rb) *node) \
{ \
    if (!node->parent || node->parent->color == RB_BLACK) { \
        goto end; \
    } \
    NODE_T(Namespace##_rb) *parent = node->parent; \
    NODE_T(Namespace##_rb) *grandparent = parent->parent; \
    NODE_T(Namespace##_rb) *uncle = grandparent->left == parent \
        ? grandparent->right \
        : grandparent->left; \
    if (uncle && uncle->color == RB_RED) { \
        parent->color = RB_BLACK; \
        uncle->color = RB_BLACK; \
        grandparent->color = RB_RED; \
        return Namespace##_repair(tree, grandparent); \
    } \
    if (grandparent->left == parent && parent->right == node) { \
        Namespace##_rotate_left(tree, parent); \
    } else if (grandparent->right == parent && parent->left == node) { \
        Namespace##_rotate_right(tree, parent); \
    } \
    grandparent->color = RB_RED; \
    parent->color = RB_BLACK; \
    if (grandparent->left == parent && parent->left == node) { \
        Namespace##_rotate_right(tree, grandparent); \
    } else { \
        Namespace##_rotate_left(tree, grandparent); \
    } \
end: \
    tree->root->color = RB_BLACK; \
} \
 \
static inline bool \
Namespace##_insert_rb_node(RB_T(Namespace) *tree, NODE_T(Namespace##_rb) *node) \
{ \
    NODE_T(Namespace##_rb) *res = Namespace##_rb_insert_node(tree, node); \
    if (res != node) { \
        return false; \
    } \
    Namespace##_repair(tree, res); \
    return true; \
} \
 \
static inline bool Namespace##_insert(RB_T(Namespace) *tree, Type data) \
{ \
    NODE_T(Namespace##_rb) *node = Namespace##_new_rb_node(data); \
    if (!node) { \
        return false; \
    } else if (Namespace##_insert_rb_node(tree, node)) { \
        return true; \
    } else { \
        free(node); \
        return false; \
    } \
} \
 \
static inline Type Namespace##_peek(RB_T(Namespace) *tree) \
{ \
    return PEEK(Namespace##_rb, tree); \
} \
 \
static inline Type Namespace##_peek_left(RB_T(Namespace) *tree) \
{ \
    return PEEK_LEFT(Namespace##_rb, tree); \
} \
 \
static inline void Namespace##_destroy_node(NODE_T(Namespace##_rb) *node) \
{ \
    if (node) { \
        Namespace##_destroy_node(node->left); \
        Namespace##_destroy_node(node->right); \
        free(node); \
    } \
} \
 \
static inline void Namespace##_clear(RB_T(Namespace) *tree) \
{ \
    Namespace##_destroy_node(tree->root); \
    tree->root = NULL; \
} \
 \
static inline void Namespace##_destroy(RB_T(Namespace) *tree) \
{ \
    CLEAR(Namespace, tree); \
} \
 \
ITER_T(Namespace) { \
    RB_T(Namespace) *tree; \
    NODE_T(Namespace##_rb) *current; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin(RB_T(Namespace) *tree) \
{ \
    ITER_T(Namespace) it = { .tree = tree, .done = true }; \
    if (!IS_EMPTY(Namespace, tree)) { \
        it.done = false; \
        it.current = Namespace##_rb_minimum_node(tree->root), \
        it.value = it.current->data; \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.current = Namespace##_rb_successor_node(it.current); \
        if (!it.current) { \
            it.done = true; \
        } else { \
            it.value = it.current->data; \
        } \
    } \
    return it; \
}
