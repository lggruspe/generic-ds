#pragma once
#include "vector.h"
#include <stdbool.h>

// don't resize if heap.growth_factor = 0

#define heap(Namespace) vector(heap_##Namespace)
#define heap_is_empty(Namespace, Heap) vector_is_empty(heap_##Namespace, (Heap))
#define heap_is_full(Namespace, Heap) vector_is_full(heap_##Namespace, (Heap))
#define heap_resize(Namespace, heap) Namespace##_heap_resize(heap)
#define heap_peek(Namespace, heap) Namespace##_heap_peek(heap)
#define heap_pop(Namespace, heap) Namespace##_heap_pop(heap)
#define heap_push(Namespace, heap, data) Namespace##_heap_push((heap), (data))
#define heap_create(Namespace, ...) (heap(Namespace)){ .growth_factor = 2.0, ##__VA_ARGS__ }
#define heap_destroy(Namespace, heap) Namespace##_heap_destroy(heap)
#define heap_sift_up(Namespace, heap, index) Namespace##_heap_sift_up((heap), (index))
#define heap_sift_down(Namespace, heap, index) Namespace##_heap_sift_down((heap), (index))
#define heap_heapify(Namespace, array, size) Namespace##_heap_heapify((array), (size))
#define heap_heapify_compare(Namespace, array, size, compare) Namespace##_heap_heapify_compare((array), (size), (compare))
#define heap_compare(Namespace, heap, a, b) Namespace##_heap_compare((heap), (a), (b))
#define heap_is_heap(Namespace, heap) Namespace##_heap_is_heap(heap)
#define heap_sort(Namespace, heap) Namespace##_heap_sort(heap)

int heap_parent(int i)
{
    return (i - 1)/2;
}

int heap_left(int i)
{
    return 2*i + 1;
}

int heap_right(int i)
{
    return 2*i + 2;
}

#define heap_register(Namespace, Type) \
 \
vector_register(heap_##Namespace, Type, int (*compare)(Type, Type);) \
 \
heap(Namespace) Namespace##_heap_resize(heap(Namespace) heap) \
{ \
    if (heap.growth_factor == 0.0) { \
        return heap; \
    } \
    return vector_resize(heap_##Namespace, heap); \
} \
 \
Type Namespace##_heap_peek(heap(Namespace) heap) \
{ \
    return heap.array[0]; \
} \
 \
int Namespace##_heap_compare(heap(Namespace) heap, Type a, Type b) \
{ \
    if (!heap.compare) { \
        return a < b ? -1 : a == b ? 0 : 1; \
    } \
    return heap.compare(a, b); \
} \
heap(Namespace) Namespace##_heap_sift_up(heap(Namespace) heap, int i) \
{ \
    while (i > 0) { \
        int p = heap_parent(i); \
        Type a = heap.array[i]; \
        if (heap_compare(Namespace, heap, a, heap.array[p]) <= 0) { \
            break; \
        } \
        heap.array[i] = heap.array[p]; \
        heap.array[p] = a; \
        i = p; \
    } \
    return heap; \
} \
 \
heap(Namespace) Namespace##_heap_push(heap(Namespace) heap, Type data) \
{ \
    if (heap.growth_factor == 0.0) { \
        return heap; \
    } \
    if (heap_is_full(Namespace, heap)) { \
        heap = heap_resize(Namespace, heap); \
    } \
    if (!heap_is_full(Namespace, heap)) { \
        heap.array[heap.size++] = data; \
        heap = heap_sift_up(Namespace, heap, heap.size-1); \
    } \
    return heap; \
} \
 \
heap(Namespace) Namespace##_heap_sift_down(heap(Namespace) heap, int i) \
{ \
    while (i < heap.size) { \
        int l = heap_left(i); \
        int r = heap_right(i); \
        int p = i; \
        if (l < heap.size && heap_compare(Namespace, heap, heap.array[l], heap.array[p]) > 0) { \
            p = l; \
        } \
        if (r < heap.size && heap_compare(Namespace, heap, heap.array[r], heap.array[p]) > 0) { \
            p = r; \
        } \
        if (i == p) { \
            break; \
        } \
 \
        Type a = heap.array[i]; \
        heap.array[i] = heap.array[p]; \
        heap.array[p] = a; \
        i = p; \
    } \
    return heap; \
} \
 \
heap(Namespace) Namespace##_heap_pop(heap(Namespace) heap) \
{ \
    Type max = heap.array[0]; \
    heap.size--; \
    heap.array[0] = heap.array[heap.size]; \
    heap.array[heap.size] = max; \
    return heap_sift_down(Namespace, heap, 0); \
} \
 \
heap(Namespace) Namespace##_heap_destroy(heap(Namespace) heap) \
{ \
    if (heap.growth_factor == 0.0) { \
        heap.array = NULL; \
    } \
    return vector_destroy(heap_##Namespace, heap); \
} \
 \
heap(Namespace) Namespace##_heap_heapify(Type array[], int size) \
{ \
    heap(Namespace) heap = heap_create( \
        Namespace, \
        .array = array, \
        .growth_factor = 0.0, \
        .size = size, \
        .capacity = size); \
    for (int i = heap.size/2 - 1; i >= 0; --i) { \
        heap = heap_sift_down(Namespace, heap, i); \
    } \
    return heap; \
} \
 \
heap(Namespace) Namespace##_heap_heapify_compare( \
    Type array[], \
    int size, \
    int (*compare)(Type, Type)) \
{ \
    heap(Namespace) heap = heap_create( \
        Namespace, \
        .array = array, \
        .growth_factor = 0.0, \
        .size = size, \
        .capacity = size, \
        .compare = compare); \
    for (int i = heap.size/2 - 1; i >= 0; --i) { \
        heap = heap_sift_down(Namespace, heap, i); \
    } \
    return heap; \
} \
 \
bool Namespace##_heap_is_heap(heap(Namespace) heap) \
{ \
    for (int i = 0; i < heap.size; ++i) { \
        int l = heap_left(i); \
        int r = heap_right(i); \
        Type a = heap.array[i]; \
        if (l < heap.size && heap_compare(Namespace, heap, a, heap.array[l]) < 0) { \
            return false; \
        } \
        if (r < heap.size && heap_compare(Namespace, heap, a, heap.array[r]) < 0) { \
            return false; \
        } \
    } \
    return true; \
} \
 \
heap(Namespace) Namespace##_heap_sort(heap(Namespace) heap) \
{ \
    while (heap.size > 0) { \
        Type max = heap_peek(Namespace, heap); \
        heap = heap_pop(Namespace, heap); \
        heap.array[heap.size] = max; \
    } \
    return heap; \
}
