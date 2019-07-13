#pragma once
#include <stdlib.h>
#include <string.h>

#define queue(type) struct {\
    type dummy;\
    type *array;\
    size_t size;\
    size_t capacity;\
    size_t front;\
    size_t back;\
}

#define queue_init(queue) do {\
    (queue).array = NULL;\
    (queue).size = 0;\
    (queue).capacity = 0;\
    (queue).front = 0;\
    (queue).back = 0;\
} while (0)

#define queue_is_empty(queue) ((queue).size == 0)

#define queue_is_full(queue) ((queue).size >= (queue).capacity)

#define queue_increase_capacity(queue) do {\
    size_t new_capacity = 2*(queue).capacity;\
    new_capacity = new_capacity ? new_capacity : 1;\
    void *temp = malloc(new_capacity * sizeof((queue).dummy));\
    if (temp) {\
        if ((queue).front < (queue).back) {\
            memcpy(temp, (queue).array, ((queue).back - (queue).front) * sizeof((queue).dummy));\
        } else if (!queue_is_empty(queue)) {\
            memcpy(temp, (queue).array + (queue).front, ((queue).capacity - (queue).front) * sizeof((queue).dummy));\
            memcpy((char*)temp + ((queue).capacity - (queue).front) * sizeof((queue).dummy),\
                    (queue).array, (queue).back * sizeof((queue).dummy));\
        }\
        (queue).array = temp;\
        (queue).capacity = new_capacity;\
        (queue).front = 0;\
        (queue).back = (queue).size;\
    }\
} while (0)

#define queue_enqueue(queue, item) do {\
    if (queue_is_full(queue)) {\
        queue_increase_capacity(queue);\
    }\
    if (!queue_is_full(queue)) {\
        (queue).array[(queue).back++] = (item);\
        if ((queue).back >= (queue).capacity) {\
            (queue).back = 0;\
        }\
        (queue).size++;\
    }\
} while (0)

// returns pointer to front
#define queue_peek(queue) (queue_is_empty(queue) ? NULL : (queue).array + (queue).front)

#define queue_dequeue(queue) do {\
    if (!queue_is_empty(queue)) {\
        (queue).front++;\
        if ((queue).front >= (queue).capacity) {\
            (queue).front = 0;\
        }\
        (queue).size--;\
    }\
    if (queue_is_empty(queue)) {\
        (queue).front = 0;\
        (queue).back = 0;\
    }\
} while (0)

#define queue_destroy(queue) do {\
    if ((queue).array) {\
        free((queue).array);\
        (queue).array = NULL;\
        (queue).size = 0;\
        (queue).capacity = 0;\
        (queue).front = 0;\
        (queue).back = 0;\
    }\
} while (0)
