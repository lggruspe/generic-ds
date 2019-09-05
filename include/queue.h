#pragma once
#include <stdlib.h>
#include <string.h>

#define queue(type) struct {\
    type dummy;\
    type *array;\
    int size;\
    int capacity;\
    int front;\
    int back;\
    double growth_factor;\
}

#define queue_create(...) {.growth_factor = 2.0, ##__VA_ARGS__}

#define queue_is_empty(queue) ((queue)->size == 0)

#define queue_is_full(queue) ((queue)->size >= (queue)->capacity)

#define queue_increase_capacity(queue) do {\
    int capacity = (queue)->growth_factor*(queue)->capacity;\
    capacity = capacity ? capacity : 1;\
    void *array = malloc(capacity * sizeof((queue)->dummy));\
    if (array) {\
        if ((queue)->front < (queue)->back) {\
            memcpy(array, (queue)->array, ((queue)->back - (queue)->front) * sizeof((queue)->dummy));\
        } else if (!queue_is_empty(queue)) {\
            memcpy(array, (queue)->array + (queue)->front, ((queue)->capacity - (queue)->front) * sizeof((queue)->dummy));\
            memcpy((char*)array + ((queue)->capacity - (queue)->front) * sizeof((queue)->dummy),\
                    (queue)->array, (queue)->back * sizeof((queue)->dummy));\
        }\
        free((queue)->array);\
        (queue)->array = array;\
        (queue)->capacity = capacity;\
        (queue)->front = 0;\
        (queue)->back = (queue)->size;\
    }\
} while (0)

#define queue_enqueue(queue, item) do {\
    if (queue_is_full(queue)) {\
        queue_increase_capacity(queue);\
    }\
    if (!queue_is_full(queue)) {\
        (queue)->array[(queue)->back++] = (item);\
        if ((queue)->back >= (queue)->capacity) {\
            (queue)->back = 0;\
        }\
        (queue)->size++;\
    }\
} while (0)

#define queue_peek(queue) ((queue)->array[(queue)->front])

#define queue_peek_pointer(queue) (queue_is_empty(queue) ? NULL : (queue)->array + (queue)->front)

#define queue_index(queue, index) ((index) + (queue)->front < (queue)->capacity ?\
        (queue)->front + (index) : (queue)->front + (index) - (queue)->capacity)

#define queue_get(queue, index) ((queue)->array[queue_index((queue), (index))])

#define queue_get_pointer(queue, index) \
   (((index) < 0 || (index) >= (queue)->size) ? NULL : \
        (queue)->array + queue_index((queue), (index)))

#define queue_set(queue, index, value) do {\
    if (0 <= (index) && (index) < (queue)->size) {\
        (queue)->array[queue_index((queue), (index))] = (value);\
    }\
} while (0)

#define queue_dequeue(queue) do {\
    if (!queue_is_empty(queue)) {\
        (queue)->front++;\
        if ((queue)->front >= (queue)->capacity) {\
            (queue)->front = 0;\
        }\
        (queue)->size--;\
    }\
    if (queue_is_empty(queue)) {\
        (queue)->front = 0;\
        (queue)->back = 0;\
    }\
} while (0)

#define queue_destroy(queue) do {\
    if ((queue)->array) {\
        free((queue)->array);\
        (queue)->array = NULL;\
    }\
    (queue)->size = 0;\
    (queue)->capacity = 0;\
    (queue)->front = 0;\
    (queue)->back = 0;\
} while (0)
