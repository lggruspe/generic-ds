#pragma once
#include "bst.h"
// #include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// rb_insert assumes inserted node is a singleton and is red

enum rb_color { RB_BLACK = 0, RB_RED };

#define RB_GENERATE(Name, Type, LessThan) \
 \
BST_GENERATE(Name##_bst, Type, (LessThan), enum rb_color color;) \
 \
typedef Name##_bst_node Name##_node; \
 \
static inline Name##_node *Name##_new(Type data) \
{ \
    Name##_node *node = Name##_bst_new(data); \
    if (node) { \
        node->color = RB_BLACK; \
        /* or RB_RED? */ \
    } \
    return node; \
} \
 \
bool (*const Name##_less_than)(Type, Type) = Name##_bst_less_than; \
 \
bool (*const Name##_is_empty)(Name##_node const*) = Name##_bst_is_empty; \
 \
Type (*const Name##_get)(Name##_node const*) = Name##_bst_get; \
 \
void (*const Name##_set)(Name##_node*, Type) = Name##_bst_set; \
 \
static inline enum rb_color Name##_color(Name##_node *n) \
{ \
    return n ? n->color : RB_BLACK; \
} \
 \
Name##_node* (*const Name##_search)(Name##_node*, Type) = Name##_bst_search; \
 \
Name##_node *Name##_rotate_left(Name##_node *t, Name##_node *x) \
{ \
    Name##_node *y = x->right; \
    x->right = y->left; \
    if (y->left) { \
        y->left->parent = x; \
    } \
    y->parent = x->parent; \
    x->parent = y; \
    y->left = x; \
    if (!y->parent) { \
        t = y; \
    } else if (y->parent->left == x) { \
        y->parent->left = y; \
    } else { \
        y->parent->right = y; \
    } \
    return t; \
} \
 \
Name##_node *Name##_rotate_right(Name##_node *t, Name##_node *y) \
{ \
    Name##_node *x = y->left; \
    y->left = x->right; \
    if (x->right) { \
        x->right->parent = y; \
    } \
    x->parent = y->parent; \
    y->parent = x; \
    x->right = y; \
    if (!x->parent) { \
        t = x; \
    } else if (x->parent->right == y) { \
        x->parent->right = x; \
    } else { \
        x->parent->left = x; \
    } \
    return t; \
} \
 \
Name##_node *Name##_repair(Name##_node *t, Name##_node *n) \
{ \
    if (!t) { \
        return NULL; \
    } \
    if (!n || Name##_color(n->parent) == RB_BLACK) { \
        t->color = RB_BLACK; \
        return t; \
    } \
    Name##_node *parent = n->parent; \
    Name##_node *grandparent = parent->parent; \
    Name##_node *uncle = grandparent->left == parent  \
        ? grandparent->right  \
        : grandparent->left; \
    if (Name##_color(uncle) == RB_RED) { \
        grandparent->color = RB_RED; \
        parent->color = RB_BLACK; \
        uncle->color = RB_BLACK; \
        return Name##_repair(t, grandparent); \
    } \
    if (grandparent->left == parent && parent->right == n) { \
        t = Name##_rotate_left(t, parent); \
    } else if (grandparent->right == parent && parent->left == n) { \
        t = Name##_rotate_right(t, parent); \
    } \
    grandparent->color = RB_RED; \
    parent->color = RB_BLACK; \
    if (grandparent->left == parent && parent->left == n) { \
        t = Name##_rotate_right(t, grandparent); \
    } else if (grandparent->right == parent && parent->right == n) { \
        t = Name##_rotate_left(t, grandparent); \
    } \
    t->color = RB_BLACK; \
    return t; \
} \
 \
Name##_node *Name##_insert(Name##_node *t, Name##_node *n) \
{ \
    if (n) { \
        n->color = RB_RED; \
        t = Name##_bst_insert(t, n); \
        t = Name##_repair(t, n); \
    } \
    return t; \
} \
 \
Name##_node* (*const Name##_minimum)(Name##_node*) = Name##_bst_minimum; \
 \
Name##_node* (*const Name##_maximum)(Name##_node*) = Name##_bst_maximum; \
 \
Name##_node* (*const Name##_next)(Name##_node const*) = Name##_bst_next; \
 \
Name##_node* (*const Name##_prev)(Name##_node const*) = Name##_bst_prev; \
 \
Name##_node *Name##_destroy(Name##_node *t) \
{ \
    /* or piggyback off Name##_bst_destroy? */ \
    if (t) { \
        t->left = Name##_destroy(t->left); \
        t->right = Name##_destroy(t->right); \
        free(t); \
    } \
    return NULL; \
} \
 \
Type (*const Name##_peek)(Name##_node*) = Name##_bst_peek; \
 \
Type (*const Name##_peek_front)(Name##_node*) = Name##_bst_peek_front;

/*
bool Name##_rb_is_balanced(Name##_node *root)
{
    int height = rb_height(Name, root);
    int weight = rb_weight(Name, root);
    return height <= 2*log2(1 + weight);
}

int Name##_rb_black_height(Name##_node *root)
{
    if (!root) {
        return 1;
    }
    int left = rb_black_height(Name, root->left);
    int right = rb_black_height(Name, root->right);
    if (left == 0 || right == 0 || left != right) {
        return 0;
    }
    return root->color == RB_BLACK ? left + 1 : left;
}

bool Name##_rb_red_child_black_parent(Name##_node *root)
{
    if (!root) {
        return true;
    }
    if (!rb_red_child_black_parent(Name, root->left)) {
        return false;
    }
    if (!rb_red_child_black_parent(Name, root->right)) {
        return false;
    }
    return root->color == RB_BLACK || rb_color(Name, root->parent) == RB_BLACK;
}

bool Name##_rb_is_red_black_tree(Name##_node *root)
{
    if (!root) {
        return true;
    }
    if (root->color == RB_RED) {
        return false;
    }
    if (!rb_is_binary_search_tree(Name, root)) {
        return false;
    }
    return rb_black_height(Name, root) && rb_red_child_black_parent(Name, root);
}

// TODO pop, pop_front
*/
