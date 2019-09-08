#pragma once
#include "bst.h"
#include <assert.h>

// rb_insert assumes inserted node is a singleton and is red

#define rb(Namespace) bst(Namespace)
#define rb_new(Namespace, data) Namespace##_rb_new(data)
#define rb_search(Namespace, root, data) bst_search(Namespace, (root), (data))
#define rb_search_compare(Namespace, root, data) bst_search_compare(Namespace, (root), (data))
#define rb_minimum(Namespace, root) bst_minimum(Namespace, (root))
#define rb_maximum(Namespace, root) bst_maximum(Namespace, (root))
#define rb_successor(Namespace, node) bst_successor(Namespace, (node))
#define rb_predecessor(Namespace, node) bst_predecessor(Namespace, (node))
#define rb_insert(Namespace, root, node) Namespace##_rb_insert((root), (node))
#define rb_insert_compare(Namespace, root, node, compare) Namespace##_rb_insert_compare((root), (node), (compare))
#define rb_repair(Namespace, root, node) Namespace##_rb_repair((root), (node))
#define rb_destroy(Namespace, root) bst_destroy(Namespace, (root))
#define rb_color(Namespace, node) Namespace##_rb_color(Namespace, (node))
#define rb_rotate_left(Namespace, root, x) Namespace##_rotate_left((root), (x))
#define rb_rotate_right(Namespace, root, y) Namespace##_rotate_right((root), (y))

enum rb_color { RB_BLACK, RB_RED };

#define rb_register(Namespace, Type) \
 \
bst_register(Namespace, Type, enum rb_color color;) \
 \
rb(Namespace) Namespace##_rb_new(Type data) \
{ \
    rb(Namespace) node = bst_new(Namespace, data); \
    if (node) { \
        node->color = RB_BLACK; \
    } \
    return node; \
} \
 \
enum rb_color Namespace##_rb_color(rb(Namespace) node) \
{ \
    if (!node) { \
        return RB_BLACK; \
    } \
    return node->color; \
} \
 \
rb(Namespace) Namespace##_rotate_left( \
    rb(Namespace) root, \
    rb(Namespace) x) \
{ \
    assert(root && x && x->right); \
    rb(Namespace) y = x->right; \
 \
    x->right = y->left; \
    if (y->left) { \
        y->left->parent = x; \
    } \
 \
    y->parent = x->parent; \
    x->parent = y; \
    y->left = x; \
    if (!y->parent) { \
        root = y; \
    } else if (y->parent->left == x) { \
        y->parent->left = y; \
    } else { \
        y->parent->right = y; \
    } \
    return root; \
} \
 \
rb(Namespace) Namespace##_rotate_right( \
    rb(Namespace) root, \
    rb(Namespace) y) \
{ \
    assert(root && y && y->left); \
    rb(Namespace) x = y->left; \
 \
    y->left = x->right; \
    if (x->right) { \
        x->right->parent = y; \
    } \
 \
    x->parent = y->parent; \
    y->parent = x; \
    x->right = y; \
    if (!x->parent) { \
        root = x; \
    } else if (x->parent->right == y) { \
        x->parent->right = x; \
    } else { \
        x->parent->left = x; \
    } \
    return root; \
} \
 \
rb(Namespace) Namespace##_rb_repair(rb(Namespace) root, rb(Namespace) node) \
{ \
    if (!root || !node) { \
        return root; \
    } \
    if (root == node) { \
        root->color = RB_BLACK; \
        return root; \
    } \
    if (node->parent->color == RB_BLACK) { \
        return root; \
    } \
    rb(Namespace) grandparent = node->parent->parent; \
    rb(Namespace) uncle = grandparent->left == node->parent  \
        ? grandparent->right  \
        : grandparent->left; \
    if (uncle) { \
        grandparent->color = RB_RED; \
        node->parent->color = RB_BLACK; \
        uncle->color = RB_BLACK; \
        return rb_repair(Namespace, root, grandparent); \
    } \
     \
    if (grandparent->left == node->parent && node->parent->right == node) { \
        root = rb_rotate_left(Namespace, root, node->parent); \
    } else if (grandparent->right == node->parent && node->parent->left == node) { \
        root = rb_rotate_right(Namespace, root, node->parent); \
    } \
 \
    grandparent->color = RB_RED; \
    node->parent->color = RB_BLACK; \
    if (grandparent->left == node->parent && node->parent->left == node) { \
        root = rb_rotate_right(Namespace, root, grandparent); \
    } else if (grandparent->right == node->parent && node->parent->right == node) { \
        root = rb_rotate_left(Namespace, root, grandparent); \
    } \
 \
    root->color = RB_BLACK; \
    return root; \
} \
 \
rb(Namespace) Namespace##_rb_insert(rb(Namespace) root, rb(Namespace) node) \
{ \
    if (node) { \
        node->color = RB_RED; \
    } \
    root = bst_insert(Namespace, root, node); \
    root = rb_repair(Namespace, root, node); \
    return root; \
} \
 \
rb(Namespace) Namespace##_rb_insert_compare( \
    rb(Namespace) root,  \
    rb(Namespace) node, \
    int (*compare)(Type, Type)) \
{ \
    if (node) { \
        node->color = RB_RED; \
    } \
    root = bst_insert_compare(Namespace, root, node, compare); \
    root = rb_repair(Namespace, root, node); \
    return root; \
}
