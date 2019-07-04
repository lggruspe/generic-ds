#pragma once
#include "bst_node.h"

typedef struct {
    bst_node_t *root;
} bst_t;

// returns true on success
void bst_insert(bst_t *tree, bst_node_t *node)
{
    bst_node_t *parent = NULL;
    bst_node_t *child = tree->root;
    while (child) {
        parent = child;
        child = (node->key < child->key 
                ? child->left 
                : child->right);
    }
    node->parent = parent;
    if (!parent) {
        tree->root = node;
    } else if (node->key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

void bst_transplant(bst_t *tree, bst_node_t *u, bst_node_t *v)
{
    if (!u->parent) {
        tree->root = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

void bst_delete(bst_t *tree, bst_node_t *node)
{
    if (!node) {
        return;
    }
    if (!node->left && !node->right) {
        return bst_transplant(node, NULL);
    }
    if (!node->left || !node->right) {
        return bst_transplant(tree, node, 
                node->left ? node->left : node->right);
    }
    bst_node_t *successor = bst_node_successor(node);
    if (node->right != successor) {
        bst_transplant(tree, successor, successor->right);
        successor->right = node->right;
        successor->right->parent = successor;
    }
    successor->left = node->left;
    successor->left->parent = successor;
    return bst_transplant(tree, node, successor);
}
