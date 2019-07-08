#pragma once
#include "node.h"
#include <stdlib.h>

typedef struct {
    node_t *null;
    size_t size;
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
            list->size = 0;
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
    list->size++;
}

void list_insert_after_tail(list_t *list, node_t *node)
{
    node_insert_after(list->null->prev, node);
    list->size++;
}

int list_delete_head(list_t *list)
{
    node_t *head = node_delete(list->null->next);
    int item = head->value;
    free(head);
    list->size--;
    return item;
}

int list_delete_tail(list_t *list)
{
    node_t *tail = node_delete(list->null->prev);
    int item = tail->value;
    free(tail);
    list->size--;
    return item;
}

// destroys all nodes in the list
void list_destroy(list_t *list)
{
    while (list->size > 0) {
        list_delete_head(list);
    }
    free(list->null);
    list->null = NULL;
}
