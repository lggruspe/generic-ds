#pragma once
#include "list.h"

typedef struct {
    list_t *list;
} deque_t;

deque_t* deque_init()
{
    deque_t *deque = (deque_t*)malloc(sizeof(deque_t));
    if (deque != NULL) {
        deque->list = list_init();
        if (deque->list == NULL) {
            free(deque);
            deque = NULL;
        }
    }
    return deque;
}

void deque_insert_before(deque_t *deque, int item)
{
    list_insert_before_head(deque->list, item);
}

void deque_insert_after(deque_t *deque, int item)
{
    list_insert_after_tail(deque->list, item);
}

int deque_delete_before(deque_t *deque)
{
    return list_delete_head(deque->list);
}

int deque_delete_after(deque_t *deque)
{
    return list_delete_tail(deque->list);
}
