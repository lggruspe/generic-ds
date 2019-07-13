#pragma once
#include <stdlib.h>
#include <string.h>
#define heap_parent(i) (((i) - 1)/2)

// implements a max heap

struct heap {
    void *array;
    size_t size;
    size_t nbytes;  // # of bytes per element
    int (*comparator)(const void*, const void*);
};

void *heap_get(struct heap *heap, size_t i)
{
    if (i >= heap->size) {
        return NULL;
    }
    return (char*)(heap->array) + i*(heap->nbytes);
}

void heap_set(struct heap *heap, size_t i, void *value)
{
    void *ptr = heap_get(heap, i);
    memcpy(ptr, value, heap->nbytes);
}

void heap_swap(struct heap *heap, size_t i, size_t j)
{
    void *ptr = malloc(heap->nbytes);
    memcpy(ptr, heap_get(heap, i), heap->nbytes);
    memcpy((char*)(heap->array) + i, (char*)(heap->array) + j, heap->nbytes);
    memcpy((char*)(heap->array) + j, ptr, heap->nbytes);
    free(ptr);
}

void heap_sift_up(struct heap *heap, size_t i)
{
    void *ptr = heap_get(heap, i);
    while (i > 0 && heap->comparator(ptr, heap_get(heap, heap_parent(i))) > 0) {
        heap_set(heap, i, heap_get(heap, heap_parent(i)));
        i = heap_parent(i);
    }
    heap_set(heap, i, ptr);
}

void heap_sift_down(struct heap *heap, size_t i)
{
    for (;;) {
        size_t l = 2*i + 1;
        size_t r = l + 1;
        size_t p = i;
        void *left = heap_get(heap, l);
        void *right = heap_get(heap, r);
        if (l < heap->size && heap->comparator(heap_get(heap, p), left) < 0) {
            p = l;
        }
        if (r < heap->size && heap->comparator(heap_get(heap, p), right) < 0) {
            p = r;
        }
        if (i != p) {
            heap_swap(heap, i, p);
            i = p;
        } else {
            break;
        }
    }
}

void heap_heapify(struct heap *heap)
{
    for (size_t i = (heap->size - 1)/2; i > 0; --i) {
        heap_sift_down(heap, i);
    }
}

// does not run heap_heapify
struct heap heap_create(void *array, size_t size, size_t nbytes, 
        int (*comparator)(const void*, const void*))
{
    struct heap heap;
    heap.array = array;
    heap.size = size;
    heap.nbytes = nbytes;
    heap.comparator = comparator;
    return heap;
}
