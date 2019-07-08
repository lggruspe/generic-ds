#pragma once
#ifndef stack_item_type
#define stack_item_type int
#endif
#include <stdlib.h>

typedef struct {
    stack_item_type *array;
    size_t size;
    size_t capacity;
} stack_t;

stack_t* stack_init(size_t capacity)
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack != NULL) {
        stack->array = malloc(sizeof(stack_item_type) * capacity);
        stack->size = 0;
        stack->capacity = (stack->array != NULL) ? capacity : 0;
    }
    return stack;
}

int stack_push(stack_t *stack, stack_item_type item)
{
    if (stack->size < stack->capacity) {
        stack->array[stack->size] = item;
        stack->size++;
        return 1;
    }
    return 0;
}

stack_item_type stack_pop(stack_t *stack)
{
    stack_item_type top;
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
