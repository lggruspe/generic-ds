#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define bst(Namespace) struct Namespace##_bst *
#define bst_new(Namespace, data) Namespace##_new(data)
#define bst_search(Namespace, root, data) Namespace##_search((root), (data))
#define bst_search_compare(Namespace, root, data, compare) Namespace##_search_compare((root), (data), (compare))
#define bst_minimum(Namespace, root) Namespace##_minimum(root)
#define bst_maximum(Namespace, root) Namespace##_maximum(root)
#define bst_predecessor(Namespace, node) Namespace##_predecessor(node)
#define bst_successor(Namespace, node) Namespace##_successor(node)
#define bst_insert(Namespace, root, node) Namespace##_insert((root), (node))
#define bst_insert_compare(Namespace, root, node, compare) Namespace##_insert_compare((root), (node), (compare))
#define bst_delete(Namespace, root, node) Namespace##_delete((root), (node))
#define bst_transplant(Namespace, root, node, replacement) Namespace##_transplant((root), (node), (replacement))
#define bst_delete_and_free(Namespace, root, node) Namespace##_delete_and_free((root), (node))
#define bst_destroy(Namespace, root) Namespace##_destroy(root)

#define bst_height(Namespace, root) Namespace##_bst_height(root)
#define bst_weight(Namespace, root) Namespace##_bst_weight(root)
#define bst_is_binary_search_tree(Namespace, root) Namespace##_is_binary_search_tree(root)
#define bst_is_binary_search_tree_compare(Namespace, root, compare) Namespace##_is_binary_search_tree_compare((root), (compare))

#define bst_register(Namespace, Type, ...) \
 \
struct Namespace##_bst { \
    Type data; \
    struct Namespace##_bst *left; \
    struct Namespace##_bst *right; \
    struct Namespace##_bst *parent; \
    __VA_ARGS__ \
}; \
 \
bst(Namespace) Namespace##_new(Type data) \
{ \
    bst(Namespace) node = malloc(sizeof(struct Namespace##_bst)); \
    if (node) { \
        node->data = data; \
        node->left = NULL; \
        node->right = NULL; \
        node->parent = NULL; \
    } \
    return node; \
} \
bst(Namespace) Namespace##_search(bst(Namespace) root, Type data) \
{ \
    while (root && root->data != data) { \
        root = data < root->data ? root->left : root->right; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_search_compare( \
    bst(Namespace) root,  \
    Type data, \
    int (*compare)(Type, Type)) \
{ \
    int comparison; \
    while (root && (comparison = compare(data, root->data)) != 0) { \
        root = comparison < 0 ? root->left : root->right; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_minimum(bst(Namespace) root) \
{ \
    if (!root) { \
        return NULL; \
    } \
    while (root->left) { \
        root = root->left; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_maximum(bst(Namespace) root) \
{ \
    if (!root) { \
        return NULL; \
    } \
    while (root->right) { \
        root = root->right; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_successor(bst(Namespace) node) \
{ \
    if (!node) { \
        return NULL; \
    } \
    if (node->right) { \
        return bst_minimum(Namespace, node->right); \
    } \
    bst(Namespace) parent = node->parent; \
    while (parent && node != parent->left) { \
        node = parent; \
        parent = parent->parent; \
    } \
    return parent; \
} \
 \
bst(Namespace) Namespace##_predecessor(bst(Namespace) node) \
{ \
    if (!node) { \
        return NULL; \
    } \
    if (node->left) { \
        return bst_maximum(Namespace, node->left); \
    } \
    bst(Namespace) parent = node->parent; \
    while (parent && node != parent->right) { \
        node = parent; \
        parent = parent->parent; \
    } \
    return parent; \
} \
 \
bst(Namespace) Namespace##_insert(bst(Namespace) root, bst(Namespace) node) \
{ \
    if (!node) { \
        return root; \
    } \
    if (!root) { \
        return node; \
    } \
    bst(Namespace) parent = NULL; \
    bst(Namespace) child = root; \
    while (child && child->data != node->data) { \
        parent = child; \
        child = node->data < child->data ? child->left : child->right; \
    } \
    if (child) { \
        return root; \
    } \
    node->parent = parent; \
    if (node->data < parent->data) { \
        parent->left = node; \
    } else { \
        parent->right = node; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_insert_compare( \
    bst(Namespace) root,  \
    bst(Namespace) node, \
    int (*compare)(Type, Type)) \
{ \
    if (!node) { \
        return root; \
    } \
    if (!root) { \
        return node; \
    } \
    bst(Namespace) parent = NULL; \
    bst(Namespace) child = root; \
    int comparison; \
    while (child && (comparison = compare(node->data, child->data)) != 0) { \
        parent = child; \
        child = comparison < 0 ? child->left : child->right; \
    } \
    if (child) { \
        return root; \
    } \
    node->parent = parent; \
    if (compare(node->data, parent->data) < 0) { \
        parent->left = node; \
    } else { \
        parent->right = node; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_transplant( \
    bst(Namespace) root,  \
    bst(Namespace) node,  \
    bst(Namespace) replacement) \
{ \
    if (replacement) { \
        replacement->parent = node->parent; \
    } \
    if (!node->parent) { \
        root = replacement; \
    } else if (node->parent->left == node) { \
        node->parent->left = replacement; \
    } else { \
        node->parent->right = replacement; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_delete(bst(Namespace) root, bst(Namespace) node) \
{ \
    if (!root || !node) { \
        return NULL; \
    } \
    if (!node->left && !node->right) { \
        return bst_transplant(Namespace, root, node, NULL); \
    } \
    if (!node->left || !node->right) { \
        bst(Namespace) child = node->left ? node->left : node->right; \
        return bst_transplant(Namespace, root, node, child); \
    } \
 \
    bst(Namespace) successor = bst_successor(Namespace, node); \
    bst(Namespace) successor_parent = successor->parent; \
    bst(Namespace) successor_child = successor->right; \
 \
    root = bst_transplant(Namespace, root, node, successor); \
    successor->left = node->left; \
    if (successor != node->right) { \
        if (successor_child) { \
            successor_child->parent = successor_parent; \
        } \
        successor_parent->left = successor_child; \
    } \
    return root; \
} \
 \
bst(Namespace) Namespace##_delete_and_free( \
    bst(Namespace) root, \
    bst(Namespace) node) \
{ \
    bst(Namespace) new_root = bst_delete(Namespace, root, node); \
    free(node); \
    return new_root; \
} \
 \
bst(Namespace) Namespace##_destroy(bst(Namespace) root) \
{ \
    while (root) { \
        root = bst_delete_and_free(Namespace, root, root); \
    } \
    return NULL; \
} \
 \
int Namespace##_bst_height(bst(Namespace) root) \
{ \
    if (!root) { \
        return 0; \
    } \
    int left = bst_height(Namespace, root->left); \
    int right = bst_height(Namespace, root->right); \
    return 1 + (left > right ? left : right); \
} \
 \
int Namespace##_bst_weight(bst(Namespace) root) \
{ \
     if (!root) { \
        return 0; \
    } \
    int left = bst_height(Namespace, root->left); \
    int right = bst_height(Namespace, root->right); \
    return left + right + 1; \
} \
 \
bool Namespace##_is_binary_search_tree(bst(Namespace) root) \
{ \
    if (!root) { \
        return true; \
    } \
    if (root->left && root->left->data > root->data) { \
        return false; \
    } \
    if (root->right && root->right->data < root->data) { \
        return false; \
    } \
    if (!bst_is_binary_search_tree(Namespace, root->left)) { \
        return false; \
    } \
    if (!bst_is_binary_search_tree(Namespace, root->right)) { \
        return false; \
    } \
    return true; \
} \
 \
bool Namespace##_is_binary_search_tree_compare( \
    bst(Namespace) root,  \
    int (*compare)(Type, Type)) \
{ \
    if (!root) { \
        return true; \
    } \
    if (root->left && compare(root->left->data, root->data) > 0) { \
        return false; \
    } \
     if (root->right && compare(root->right->data, root->data) < 0) { \
        return false; \
    } \
    if (!bst_is_binary_search_tree_compare(Namespace, root->left, compare)) { \
        return false; \
    } \
    if (!bst_is_binary_search_tree_compare(Namespace, root->right, compare)) { \
        return false; \
    } \
    return true; \
}
