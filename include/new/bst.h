#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define BST_GENERATE(Name, Type, LessThan, ...)  \
 \
typedef struct Name##_node { \
    Type data; \
    struct Name##_node *left; \
    struct Name##_node *right; \
    struct Name##_node *parent; \
    __VA_ARGS__ \
} Name##_node; \
 \
static inline Name##_node *Name##_new(Type data) \
{ \
    Name##_node *node = malloc(sizeof(struct Name##_node)); \
    if (node) { \
        node->data = data; \
        node->left = NULL; \
        node->right = NULL; \
        node->parent = NULL; \
    } \
    return node; \
} \
 \
static inline bool Name##_less_than(Type a, Type b) \
{ \
    return (LessThan)(a, b); \
} \
 \
static inline bool Name##_is_empty(Name##_node const *t) \
{ \
    return !t; \
} \
 \
static inline Type Name##_get(Name##_node const *n) \
{ \
    return n->data; \
} \
 \
static inline void Name##_set(Name##_node *n, Type data) \
{ \
    if (n) { \
        n->data = data; \
    } \
} \
 \
static inline Name##_node *Name##_search(Name##_node *t, Type data) \
{ \
    bool (*lt)(Type, Type) = Name##_less_than; \
    while (t) { \
        if (lt(data, t->data)) { \
            t = t->left; \
        } else if (lt(t->data, data)) { \
            t = t->right; \
        } else { \
            break; \
        } \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_insert(Name##_node *t, Name##_node *n) \
{ \
    if (!n) { \
        return t; \
    } \
    if (!t) { \
        return n; \
    } \
    bool (*lt)(Type, Type) = Name##_less_than; \
    Name##_node *parent = NULL; \
    Name##_node *child = t; \
    while (child) { \
        parent = child; \
        if (lt(n->data, child->data)) { \
            child = child->left; \
        } else if (lt(child->data, n->data)) { \
            child = child->right; \
        } else { \
            break; \
        } \
    } \
    if (child) { \
        return t; \
    } \
    n->parent = parent; \
    if (lt(n->data, parent->data)) { \
        parent->left = n; \
    } else { \
        parent->right = n; \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_minimum(Name##_node *t) \
{ \
    if (!t) { \
        return NULL; \
    } \
    while (t->left) { \
        t = t->left; \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_maximum(Name##_node *t) \
{ \
    if (!t) { \
        return NULL; \
    } \
    while (t->right) { \
        t = t->right; \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_next(Name##_node const *n) \
{ \
    if (!n) { \
        return NULL; \
    } \
    if (n->right) { \
        return Name##_minimum(n->right); \
    } \
    Name##_node *parent = n->parent; \
    while (parent && n != parent->left) { \
        n = parent; \
        parent = parent->parent; \
    } \
    return parent; \
} \
 \
static inline Name##_node *Name##_prev(Name##_node const *n) \
{ \
    if (!n) { \
        return NULL; \
    } \
    if (n->left) { \
        return Name##_maximum(n->left); \
    } \
    Name##_node *parent = n->parent; \
    while (parent && n != parent->right) { \
        n = parent; \
        parent = parent->parent; \
    } \
    return parent; \
} \
 \
static inline Name##_node *Name##_transplant( \
    Name##_node *t,  \
    Name##_node *n,  \
    Name##_node *replacement) \
{ \
    if (replacement) { \
        replacement->parent = n->parent; \
    } \
    if (!n->parent) { \
        t = replacement; \
    } else if (n->parent->left == n) { \
        n->parent->left = replacement; \
    } else { \
        n->parent->right = replacement; \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_delete_impl(Name##_node *t, Name##_node *n) \
{ \
    if (!t || !n) { \
        return NULL; \
    } \
    if (!n->left && !n->right) { \
        return Name##_transplant(t, n, NULL); \
    } \
    if (!n->left || !n->right) { \
        Name##_node *child = n->left ? n->left : n->right; \
        return Name##_transplant(t, n, child); \
    } \
 \
    Name##_node *next = Name##_next(n); \
    Name##_node *next_parent = next->parent; \
    Name##_node *next_child = next->right; \
 \
    t = Name##_transplant(t, n, next); \
    next->left = n->left; \
    if (next != n->right) { \
        if (next_child) { \
            next_child->parent = next_parent; \
        } \
        next_parent->left = next_child; \
    } \
    return t; \
} \
 \
static inline Name##_node *Name##_delete(Name##_node *t, Name##_node *n) \
{ \
    t = Name##_delete_impl(t, n); \
    free(n); \
    return t; \
} \
 \
static inline void Name##_destroy(Name##_node *t) \
{ \
    while (t) { \
        t = Name##_delete(t, t); \
    } \
} \
 \
Type Name##_peek_front(Name##_node *t) \
{ \
    return Name##_minimum(t)->data; \
} \
 \
Type Name##_peek(Name##_node *t) \
{ \
    return Name##_maximum(t)->data; \
} \
 \
Name##_node *Name##_pop_front(Name##_node *t) \
{ \
    return Name##_delete(t, Name##_minimum(t)); \
} \
 \
Name##_node *Name##_pop(Name##_node *t) \
{ \
    return Name##_delete(t, Name##_maximum(t)); \
}

/*
int Name##_height(Name##_node *t)
{
    if (!t) {
        return 0;
    }
    int left = Name##_height(t->left);
    int right = Name##_height(t->right);
    return 1 + (left > right ? left : right);
}

int Name##_weight(Name##_node *t)
{
     if (!t) {
        return 0;
    }
    int left = Name##_weight(t->left);
    int right = Name##_weight(t->right);
    return left + right + 1;
}

bool Name##_is_bst(Name##_node *t)
{
    if (!t) {
        return true;
    }
    if (t->left && t->left->data > t->data) {
        return false;
    }
    if (t->right && t->right->data < t->data) {
        return false;
    }
    if (!Name##_is_bst(t->left)) {
        return false;
    }
    if (!Name##_is_bst(t->right)) {
        return false;
    }
    return true;
}

static inline void \
Namespace##_delete_node(BST_T(Namespace) *tree, NODE_T(Namespace) *node) \
{ \
    if (!node->left) { \
        if (!node->right) { \
            Namespace##_replace_node(tree, node, NULL); \
        } else { \
            Namespace##_replace_node(tree, node, node->right); \
        } \
    } else if (!node->right) { \
        Namespace##_replace_node(tree, node, node->left); \
    } else { \
        NODE_T(Namespace) *successor = Namespace##_successor_node(node); \
        node->left->parent = successor; \
        successor->left = node->left; \
        if (node->right == successor) { \
            Namespace##_replace_node(tree, node, successor); \
        } else { \
            Namespace##_replace_node(tree, successor, successor->right); \
            Namespace##_replace_node(tree, node, successor); \
        } \
    } \
} \
*/
