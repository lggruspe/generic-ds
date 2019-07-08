#pragma once

const char RB_BLACK = 'b';
const char RB_RED = 'r';

typedef struct rb_node_t {
    int key;
    struct rb_node_t *left, *right, *parent;
    char color;
} rb_node_t;

rb_node_t *rb_node_create(
        int key, 
        rb_node_t *left, 
        rb_node_t *right, 
        rb_node_t *parent, 
        char color)
{
    rb_node_t *node = malloc(sizeof(rb_node_t));
    if (node) {
        node->key = key;
        node->left = left;
        node->right = right;
        node->parent = parent;
        node->color = color;
    }
    return node;
}

rb_node_t *rb_node_search(rb_node_t *root, int key)
{
    rb_node_t *node = root;
    while (node && node->key != key) {
        node = (key < node->key ? node->left : node->right);
    }
    return node;
}

// should only be called if x and y are not null
void rb_left_rotate(rb_node_t *x, rb_node_t *y)
{
    if (!x || !y) {
        exit(EXIT_FAILURE);
    }
    y->parent = x->parent;
    if (y->parent) {
        if (y->parent->left == x) {
            y->parent->left = y;
        } else {
            y->parent->right = y;
        }
    }

    x->right = y->left;
    if (x->right) {
        x->right->parent = x;
    }

    y->left = x;
    x->parent = y;
}

void rb_right_rotate(rb_node_t *x, rb_node_t *y)
{
    if (!x || !y) {
        exit(EXIT_FAILURE);
    }
    x->parent = y->parent;
    if (x->parent) {
        if (x->parent->left == y) {
            x->parent->left = x;
        } else {
            x->parent->right = x;
        }
    }

    y->left = x->right;
    if (y->left) {
        y->left->parent = y;
    }

    x->right = y;
    y->parent = x;
}
