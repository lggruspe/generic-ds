#pragma once
#include <stddef.h>
#include <stdint.h>
#define heap_parent(i) (((i) - 1)/2)
#define heap_left(i) (2*(i) + 1)
#define heap_right(i) (heap_left(i) + 1)

// implements a max heap

#define heap(type) heap_##type

#define heap_create(...) {\
    .array = NULL,\
    .size = 0,\
    .comparator = NULL,\
    __VA_ARGS__\
}

#define heap_swap(heap, i, j) do {\
    if ((i) < (heap)->size && (j) < (heap)->size) {\
        if ((heap)->array[i] != (heap)->array[j]) {\
            uintptr_t temp = (uintptr_t)((heap)->array[i]);\
            (heap)->array[i] = (heap)->array[j];\
            (heap)->array[j] = (void*)temp;\
        }\
    }\
} while (0)

#define define_heap(type) \
struct heap_##type {\
    type *array;\
    size_t size;\
    int (*comparator)(const void *, const void *);\
};\

#define heap_sift_up(heap, j) do {\
    size_t i = (j);\
    if ((heap)->comparator) {\
        while (i > 0 && (heap)->comparator((heap)->array[i], (heap)->array[heap_parent(i)]) > 0) {\
            heap_swap(heap, i, heap_parent(i));\
            i = heap_parent(i);\
        }\
    } else {\
        while (i > 0 && (heap)->array[i] > (heap)->array[heap_parent(i)]) {\
            heap_swap(heap, i, heap_parent(i));\
            i = heap_parent(i);\
        }\
    }\
} while (0)

#define heap_sift_down(heap, j) do {\
    size_t i = (j);\
    while (i < (heap)->size) {\
        size_t p = i;\
        if (heap_left(i) < (heap)->size && (heap)->array[p] < (heap)->array[heap_left(i)]) {\
            p = heap_left(i);\
        }\
        if (heap_right(i) < (heap)->size && (heap)->array[p] < (heap)->array[heap_right(i)]) {\
            p = heap_right(i);\
        }\
        if (i != p) {\
            heap_swap((heap), i, p);\
            i = p;\
        } else {\
            break;\
        }\
    }\
} while (0)
        
#define heap_heapify(heap) do {\
    for (size_t i = ((heap)->size - 1)/2; i > 0; --i) {\
        heap_sift_down((heap), i);\
    }\
    heap_sift_down((heap), i);\
} while (0)
