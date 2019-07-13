#pragma once
#include <stdlib.h>

// dummy is used to get size of an item
#define stack(type) struct {\
    type dummy;\
    type *array;\
    size_t size;\
    size_t capacity;\
}

#define stack_init(stack) do {\
    (stack).array = NULL;\
    (stack).size = 0;\
    (stack).capacity = 0;\
} while (0)

#define stack_increase_capacity(stack) do {\
    size_t new_capacity = 2*(stack).capacity;\
    new_capacity = new_capacity ? new_capacity : 1;\
    void *tmp = realloc((stack).array, new_capacity * sizeof((stack).dummy));\
    if (tmp) {\
        (stack).array = tmp;\
        (stack).capacity = new_capacity;\
    }\
} while (0)

#define stack_is_empty(stack) ((stack).size == 0)
#define stack_is_full(stack) ((stack).size >= (stack).capacity)

#define stack_push(stack, item) do {\
    if (stack_is_full(stack)) {\
        stack_increase_capacity(stack);\
    }\
    if (!stack_is_full(stack)) {\
        (stack).array[(stack).size++] = (item);\
    }\
} while (0)

#define stack_peek(stack) (stack_is_empty(stack) ? NULL : &((stack).array[(stack).size - 1]))

#define stack_pop(stack) do {\
    if (!stack_is_empty(stack)) {\
        (stack).size--;\
    }\
} while (0)

#define stack_destroy(stack) do {\
    if ((stack).array) {\
        free((stack).array);\
        (stack).array = NULL;\
        (stack).size = 0;\
        (stack).capacity = 0;\
    }\
} while (0)
