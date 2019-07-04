#pragma once

const RB_BLACK = 'b';
const RB_RED = 'r';

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

}

void rb_left_rotate(rb_node_t *x, rb_node_t *y)
{

}
