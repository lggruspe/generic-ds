#pragma once
#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} stack_t;

stack_t* stack_init(size_t capacity)
{
    stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
    if (stack != NULL) {
        stack->array = (int*)malloc(sizeof(int) * capacity);
        stack->size = 0;
        stack->capacity = (stack->array != NULL) ? capacity : 0;
    }
    return stack;
}

int stack_push(stack_t *stack, int item)
{
    if (stack->size < stack->capacity) {
        stack->array[stack->size] = item;
        stack->size++;
        return 1;
    }
    return 0;
}

int stack_pop(stack_t *stack)
{
    int top;
    if (stack->size > 0) {
        stack->size--;
        top = stack->array[stack->size];
    }
    return top;
}

void stack_destroy(stack_t *stack)
{
    while (stack->size > 0) {
        stack_pop(stack);
    }
    free(stack->array);
    free(stack);
}
