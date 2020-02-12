#pragma once

/* min-heap */

static inline int heap_parent(int i)
{
    return (i-1)/2;
}

static inline int heap_left(int i)
{
    return 2*i + 1;
}

static inline int heap_right(int i)
{
    return 2*i + 2;
}

#define HEAP_GENERATE(Name, Type, LessThan) \
 \
static inline void Name##_sift_up(Type *array, int i) \
{ \
    Type a = array[i]; \
    int p = heap_parent(i); \
    while (i > 0 && (LessThan)(a, array[p])) { \
        array[i] = array[p]; \
        i = p; \
        p = heap_parent(p); \
    } \
    array[i] = a; \
} \
 \
static inline void Name##_sift_down(Type *array, int n, int i) \
{ \
    while (i < n) { \
        int p = i; \
        int l = heap_left(i); \
        if (l < n && (LessThan)(array[l], array[p])) { \
            p = l; \
        } \
        int r = heap_right(i); \
        if (r < n && (LessThan)(array[r], array[p])) { \
            p = r; \
        } \
        if (i == p) { \
            break; \
        } \
        Type a = array[i]; \
        array[i] = array[p]; \
        array[p] = a; \
        i = p; \
    } \
} \
 \
static inline void Name##_heapify(Type *array, int n) \
{ \
    for (int i = n/2 - 1; i >= 0; --i) { \
        Name##_sift_down(array, n, i); \
    } \
}
