#pragma once
#include <stdlib.h>

typedef struct node_t {
    struct node_t *prev;
    struct node_t *next;
    int value;
} node_t;

void node_insert_before(node_t *left, node_t *right)
{
    left->next= right;
    left->prev = right->prev;
    left->prev->next = left;
    right->prev = left;
}

void node_insert_after(node_t *left, node_t *right)
{
    right->prev = left;
    right->next = left->next;
    right->next->prev = right;
    left->next = right;
}

node_t* node_delete(node_t *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return node;
}

node_t* node_create(int value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node) {
        node->value = value;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}
