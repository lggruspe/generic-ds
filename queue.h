#pragma once
#include <stdlib.h>

typedef struct {
    int *array;
    size_t capacity;
    size_t size;
    size_t front;
    size_t back;
} queue_t;

queue_t* queue_init(size_t capacity)
{
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
    if (queue != NULL) {
        queue->array = (int*)malloc(sizeof(int) * capacity);
        queue->size = 0;
        queue->front = 0;
        queue->back = 0;
        queue->capacity = (queue->array != NULL ? capacity : 0);
    }
    return queue;
}

int queue_enqueue(queue_t *queue, int item)
{
    if (queue->size < queue->capacity) {
        queue->array[queue->back++] = item;
        if (queue->back == queue->capacity) {
            queue->back = 0;
        }
        return 1;
    }
    return 0;
}

int queue_dequeue(queue_t *queue)
{
    int item;
    if (queue->size > 0) {
        queue->size--;
        int item = queue->array[queue->front++];
        if (queue->front == queue->capacity) {
            queue->front = 0;
        }
    }
    if (queue->size == 0) {
        queue->front = queue->back = 0;
    }
    return item;
}

void stack_destroy(queue_t *queue)
{
    while (queue->size > 0) {
        queue_dequeue(queue);
    }
    free(queue->array);
    free(queue);
}
