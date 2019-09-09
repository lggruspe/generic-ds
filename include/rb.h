#pragma once
#include "bst.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>

// rb_insert assumes inserted node is a singleton and is red

#define rb(Namespace) bst(Namespace)
#define rb_new(Namespace, data) Namespace##_rb_new(data)
#define rb_search(Namespace, root, data) bst_search(Namespace, (root), (data))
#define rb_search_compare(Namespace, root, data, compare) bst_search_compare(Namespace, (root), (data), (compare))
#define rb_minimum(Namespace, root) bst_minimum(Namespace, (root))
#define rb_maximum(Namespace, root) bst_maximum(Namespace, (root))
#define rb_successor(Namespace, node) bst_successor(Namespace, (node))
#define rb_predecessor(Namespace, node) bst_predecessor(Namespace, (node))
#define rb_insert(Namespace, root, node) Namespace##_rb_insert((root), (node))
#define rb_insert_compare(Namespace, root, node, compare) Namespace##_rb_insert_compare((root), (node), (compare))
#define rb_repair(Namespace, root, node) Namespace##_rb_repair((root), (node))
#define rb_destroy(Namespace, root) bst_destroy(Namespace, (root))
#define rb_color(Namespace, node) Namespace##_rb_color(node)
#define rb_rotate_left(Namespace, root, x) Namespace##_rotate_left((root), (x))
#define rb_rotate_right(Namespace, root, y) Namespace##_rotate_right((root), (y))

#define rb_height(Namespace, root) bst_height(Namespace, root)
#define rb_weight(Namespace, root) bst_weight(Namespace, root)
#define rb_is_binary_search_tree(Namespace, root) bst_is_binary_search_tree(Namespace, root)
#define rb_is_binary_search_tree_compare(Namespace, root, compare) bst_is_binary_search_tree_compare(Namespace, (root), (compare))
#define rb_is_balanced(Namespace, root) Namespace##_is_balanced(root)
#define rb_black_height(Namespace, root) Namespace##_black_height(root)
#define rb_red_child_black_parent(Namespace, root) Namespace##_red_child_black_parent(root)
#define rb_is_red_black_tree(Namespace, root) Namespace##_is_red_black_tree(root)
#define rb_is_red_black_tree_compare(Namespace, root, compare) Namespace##_is_red_black_tree_compare((root), (compare))

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
    rb(Namespace) parent = node->parent; \
    rb(Namespace) grandparent = parent->parent; \
    rb(Namespace) uncle = grandparent->left == parent  \
        ? grandparent->right  \
        : grandparent->left; \
    if (uncle && uncle->color == RB_RED) { \
        grandparent->color = RB_RED; \
        parent->color = RB_BLACK; \
        uncle->color = RB_BLACK; \
        return rb_repair(Namespace, root, grandparent); \
    } \
     \
    if (grandparent->left == parent && parent->right == node) { \
        root = rb_rotate_left(Namespace, root, parent); \
    } else if (grandparent->right == parent && parent->left == node) { \
        root = rb_rotate_right(Namespace, root, parent); \
    } \
 \
    grandparent->color = RB_RED; \
    parent->color = RB_BLACK; \
    if (grandparent->left == parent && parent->left == node) { \
        root = rb_rotate_right(Namespace, root, grandparent); \
    } else if (grandparent->right == parent && parent->right == node) { \
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
        root = bst_insert(Namespace, root, node); \
        root = rb_repair(Namespace, root, node); \
    } \
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
        root = bst_insert_compare(Namespace, root, node, compare); \
        root = rb_repair(Namespace, root, node); \
    } \
    return root; \
} \
 \
bool Namespace##_is_balanced(rb(Namespace) root) \
{ \
    int height = rb_height(Namespace, root); \
    int weight = rb_weight(Namespace, root); \
    return height <= 2*log2(1 + weight); \
} \
 \
int Namespace##_black_height(rb(Namespace) root) \
{ \
    if (!root) { \
        return 1; \
    } \
    int left = rb_black_height(Namespace, root->left); \
    int right = rb_black_height(Namespace, root->right); \
    if (left == 0 || right == 0 || left != right) { \
        return 0; \
    } \
    return root->color == RB_BLACK ? left + 1 : left; \
} \
 \
bool Namespace##_red_child_black_parent(rb(Namespace) root) \
{ \
    if (!root) { \
        return true; \
    } \
    if (!rb_red_child_black_parent(Namespace, root->left)) { \
        return false; \
    } \
    if (!rb_red_child_black_parent(Namespace, root->right)) { \
        return false; \
    } \
    return root->color == RB_BLACK || rb_color(Namespace, root->parent) == RB_BLACK; \
} \
 \
bool Namespace##_is_red_black_tree(rb(Namespace) root) \
{ \
    if (!root) { \
        return true; \
    } \
    if (root->color == RB_RED) { \
        return false; \
    } \
    if (!rb_is_binary_search_tree(Namespace, root)) { \
        return false; \
    } \
    return rb_black_height(Namespace, root) && rb_red_child_black_parent(Namespace, root); \
} \
 \
bool Namespace##_is_red_black_tree_compare( \
    rb(Namespace) root, \
    int (*compare)(Type, Type)) \
{ \
    if (!root) { \
        return true; \
    } \
    if (root->color == RB_RED) { \
        return false; \
    } \
    if (!rb_is_binary_search_tree_compare(Namespace, root, compare)) { \
        return false; \
    } \
    return rb_black_height(Namespace, root) && rb_red_child_black_parent(Namespace, root); \
}
