#pragma once
#include "node.h"
#include <stdlib.h>

typedef struct {
    node_t *null;
} list_t;

list_t* list_init()
{
    list_t *list = (list_t*)malloc(sizeof(list_t));
    if (list != NULL) {
        node_t *node = (node_t*)malloc(sizeof(list_t));
        if (node != NULL) {
            node->prev = node;
            node->next = node;
            list->null = node;
        } else {
            free(list);
            list = NULL;
        }
    }
    return list;
}

node_t* list_search(list_t *list, int value)
{
    list->null->value = value;
    node_t *node = list->null->next;
    while (node->value != value) {
        node = node->next;
    }
    return node;
}

void list_insert_before_head(list_t *list, node_t *node)
{
    node_insert_before(node, list->null->next);
}

void list_insert_after_tail(list_t *list, node_t *node)
{
    node_insert_after(list->null->prev, node);
}

int list_delete_head(list_t *list)
{
    node *head = node_delete(list->null->next);
    int item = head->value;
    free(head);
    return item;
}

int list_delete_tail(list_t *list)
{
    node *tail = node_delete(list->null->prev);
    int item = tail->value;
    free(tail);
    return item;
}
