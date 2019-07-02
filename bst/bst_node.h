#pragma once

typedef struct bst_node_t {
    int key;
    struct bst_node_t *left, *right;
} bst_node_t;

bst_node_t *bst_node_search(bst_node_t *root, int key)
{
    bst_node_t *node = root;
    while (node && node->key != key) {
        node = (key < node->key ? node->left : node->right);
    }
    return node;
}

bst_node_t *bst_node_minimum(bst_node_t *root)
{
    if (!root) {
        return root;
    }
    bst_node_t *node = root;
    while (node->left) {
        node = node->left;
    }
    return node;
}

bst_node_t *bst_node_maximum(bst_node_t *root)
{
    if (!root) {
        return root;
    }
    bst_node_t *node = root;
    while (node->right) {
        node = node->right;
    }
    return node;
}

bst_node_t *bst_node_successor(bst_node_t *node)
{
    if (!node) {
        return node;
    }
    if (node->right) {
        return bst_node_minimum(node->right);
    }

    bst_node_t *parent = node->parent;
    while (parent && parent->left != node) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

bst_node_t *bst_node_predecessor(bst_node_t *node)
{
    if (!node) {
        return node;
    }
    if (node->left) {
        return bst_node_maximum(node->left);
    }
    bst_node_t *parent = node->parent;
    while (parent && parent->right != node) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}
