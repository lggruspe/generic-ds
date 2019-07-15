#pragma once
#include <assert.h>
#include <stdbool.h>
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
    assert(heap && heap->array && i < heap->size);
    void *result = (char*)(heap->array) + i*(heap->nbytes);
    assert(result);
    return result;
}

void heap_set(struct heap *heap, size_t i, void *value)
{
    assert(heap && value);
    void *ptr = heap_get(heap, i);
    memcpy(ptr, value, heap->nbytes);
}

// returns true if successful
bool heap_swap(struct heap *heap, size_t i, size_t j)
{
    assert(heap);
    void *it = heap_get(heap, i);
    void *jt = heap_get(heap, j);

    void *temp = malloc(heap->nbytes);
    if (!temp) {
        return false;
    }
    memcpy(temp, it, heap->nbytes);
    memcpy(it, jt, heap->nbytes);
    memcpy(jt, temp, heap->nbytes);
    free(temp);
    return true;
}

void heap_sift_up(struct heap *heap, size_t i)
{
    assert(heap && heap->comparator);
    void *ptr = heap_get(heap, i);
    while (i > 0 && heap->comparator(ptr, heap_get(heap, heap_parent(i))) > 0) {
        heap_set(heap, i, heap_get(heap, heap_parent(i)));
        i = heap_parent(i);
    }
    heap_set(heap, i, ptr);
}

// returns true if successful
bool heap_sift_down(struct heap *heap, size_t i)
{
    assert(heap && heap->comparator);
    for (;;) {
        size_t l = 2*i + 1;
        size_t r = l + 1;
        size_t p = i;
        if (l < heap->size) {
            void *left = heap_get(heap, l);
            if (heap->comparator(heap_get(heap, p), left) < 0) {
                p = l;
            }
            if (r < heap->size) {
                void *right = heap_get(heap, r);
                if (heap->comparator(heap_get(heap, p), right) < 0) {
                    p = r;
                }
            }
        }
        if (i != p) {
            if (!heap_swap(heap, i, p)) {
                return false;
            }
            i = p;
        } else {
            break;
        }
    }
    return true;
}

bool heap_heapify(struct heap *heap)
{
    assert(heap);
    for (size_t i = (heap->size - 1)/2; i > 0; --i) {
        if (!heap_sift_down(heap, i)) {
            return false;
        }
    }
    return heap_sift_down(heap, 0);
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
