#pragma once
#include "ds.h"
#include <stdbool.h>
#include <stdlib.h>

#define BST_T(Namespace) struct Namespace##_bst

#define BST(Namespace) (BST_T(Namespace)){ .root = NULL }

#define BST_GENERATE(Namespace, Type, LessThan) \
 \
NODE_T(Namespace) { \
    Type data; \
    NODE_T(Namespace) *left; \
    NODE_T(Namespace) *right; \
    NODE_T(Namespace) *parent; \
}; \
 \
static inline NODE_T(Namespace) *Namespace##_new_node(Type data) \
{ \
    NODE_T(Namespace) *node = malloc(sizeof(NODE_T(Namespace))); \
    if (node) { \
        node->data = data; \
        node->left = NULL; \
        node->right = NULL; \
        node->parent = NULL; \
    } \
    return node; \
} \
 \
static inline NODE_T(Namespace)* \
Namespace##_search_node(NODE_T(Namespace) *node, Type data) \
{ \
    while (node) { \
        if ((LessThan)(data, node->data)) { \
            node = node->left; \
        } else if ((LessThan)(node->data, data)) { \
            node = node->right; \
        } else { \
            break; \
        } \
    } \
    return node; \
} \
 \
static inline NODE_T(Namespace)* \
Namespace##_minimum_node(NODE_T(Namespace) *node) \
{ \
    if (!node) { \
        return NULL; \
    } \
    while (node->left) { \
        node = node->left; \
    } \
    return node; \
} \
 \
static inline NODE_T(Namespace)* \
Namespace##_maximum_node(NODE_T(Namespace) *node) \
{ \
    if (!node) { \
        return NULL; \
    } \
    while (node->right) { \
        node = node->right; \
    } \
    return node; \
} \
 \
static inline NODE_T(Namespace)* \
Namespace##_successor_node(NODE_T(Namespace) *node) \
{ \
    if (!node) { \
        return NULL; \
    } else if (node->right) { \
        return Namespace##_minimum_node(node->right); \
    } \
    NODE_T(Namespace) *parent = node->parent; \
    while (parent && parent->left != node) { \
        node = parent; \
        parent = parent->parent; \
    } \
    return parent; \
} \
 \
BST_T(Namespace) { \
    NODE_T(Namespace) *root; \
}; \
 \
static inline bool Namespace##_is_empty(BST_T(Namespace) const *tree) \
{ \
    return !tree->root; \
} \
 \
static inline NODE_T(Namespace)* \
Namespace##_insert_node(BST_T(Namespace) *tree, NODE_T(Namespace) *node) \
{ \
    /* assume node is a non-null singleton \
     * returns inserted/existing node */ \
    if (IS_EMPTY(Namespace, tree)) { \
        return tree->root = node; \
    } \
    NODE_T(Namespace) *parent = NULL; \
    NODE_T(Namespace) *child = tree->root; \
    while (child) { \
        parent = child; \
        if ((LessThan)(node->data, child->data)) { \
            child = child->left; \
        } else if ((LessThan)(child->data, node->data)) { \
            child = child->right; \
        } else { \
            break; \
        } \
    } \
    if (child) { \
        return child; \
    } \
    node->parent = parent; \
    if ((LessThan)(node->data, parent->data)) { \
        parent->left = node; \
    } else { \
        parent->right = node; \
    } \
    return node; \
} \
 \
static inline void Namespace##_replace_node( \
        BST_T(Namespace) *tree, \
        NODE_T(Namespace) *node, \
        NODE_T(Namespace) *replacement) \
{ \
    /* node must be nonnull */ \
    NODE_T(Namespace) *parent = node->parent; \
    if (replacement) { \
        replacement->parent = parent; \
    } \
    if (!parent) { \
        tree->root = replacement; \
    } else if (parent->left == node) { \
        parent->left = replacement; \
    } else { \
        parent->right = replacement; \
    } \
} \
 \
static inline void \
Namespace##_delete_node(BST_T(Namespace) *tree, NODE_T(Namespace) *node) \
{ \
    /* assume node is in tree */ \
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
 \
static inline bool Namespace##_insert(BST_T(Namespace) *tree, Type data) \
{ \
    NODE_T(Namespace) *node = Namespace##_new_node(data); \
    if (!node) { \
        return false; \
    } else if (node == Namespace##_insert_node(tree, node)) { \
        return true; \
    } else { \
        free(node); \
        return false; \
    } \
} \
 \
static inline bool Namespace##_delete(BST_T(Namespace) *tree, Type data) \
{ \
    NODE_T(Namespace) *node = Namespace##_search_node(tree->root, data);  \
    if (!node) { \
        return false; \
    } \
    Namespace##_delete_node(tree, node); \
    free(node); \
    return true; \
} \
 \
static inline Type Namespace##_peek(BST_T(Namespace) *tree) \
{ \
    return Namespace##_maximum_node(tree->root)->data; \
} \
 \
static inline Type Namespace##_pop(BST_T(Namespace) *tree) \
{ \
    NODE_T(Namespace) *node = Namespace##_maximum_node(tree->root); \
    Type data = node->data; \
    Namespace##_delete_node(tree, node); \
    free(node); \
    return data; \
} \
 \
static inline Type Namespace##_peek_left(BST_T(Namespace) *tree) \
{ \
    return Namespace##_minimum_node(tree->root)->data; \
} \
 \
static inline Type Namespace##_pop_left(BST_T(Namespace) *tree) \
{ \
    NODE_T(Namespace) *node = Namespace##_minimum_node(tree->root); \
    Type data = node->data; \
    Namespace##_delete_node(tree, node); \
    free(node); \
    return data; \
} \
 \
static inline void Namespace##_clear(BST_T(Namespace) *tree) \
{ \
    while (!IS_EMPTY(Namespace, tree)) { \
        NODE_T(Namespace) *node = tree->root; \
        Namespace##_delete_node(tree, node); \
        free(node); \
    } \
} \
 \
static inline void Namespace##_destroy(BST_T(Namespace) *tree) \
{ \
    CLEAR(Namespace, tree); \
} \
 \
ITER_T(Namespace) { \
    BST_T(Namespace) *tree; \
    NODE_T(Namespace) *current; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin(BST_T(Namespace) *tree) \
{ \
    ITER_T(Namespace) it = { .tree = tree, .done = true }; \
    if (!IS_EMPTY(Namespace, tree)) { \
        it.done = false; \
        it.current = Namespace##_minimum_node(tree->root), \
        it.value = it.current->data; \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.current = Namespace##_successor_node(it.current); \
        if (!it.current) { \
            it.done = true; \
        } else { \
            it.value = it.current->data; \
        } \
    } \
    return it; \
}
