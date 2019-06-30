#pragma once

typedef struct node_t {
    struct node_t *prev;
    struct node_t *next;
    int value;
} node_t;

void node_insert_before(node_t *left, node_t *right)
{
    left->right = right;
    left->left = right->left;
    left->left->right = left;
    right->left = left;
}

void node_insert_after(node_t *left, node_t *right)
{
    right->left = left;
    right->right = left->right;
    right->right->left = right;
    left->right = right;
}

node* node_delete(node_t *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return node;
}
