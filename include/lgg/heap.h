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

#define SIFT_UP(Namespace) (Namespace##_sift_up)

#define SIFT_DOWN(Namespace) (Namespace##_sift_down)

#define HEAPIFY(Namespace) (Namespace##_heapify)

#define HEAP_GENERATE(Namespace, Type, LessThan) \
 \
static inline void Namespace##_sift_up(Type *array, int i) \
{ \
    while (i > 0) { \
        int p = heap_parent(i); \
        Type a = array[i]; \
        if (!(LessThan)(a, array[p])) { \
            break; \
        } \
        array[i] = array[p]; \
        array[p] = a; \
        i = p; \
    } \
} \
 \
static inline void Namespace##_sift_down(Type *array, int n, int i) \
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
static inline void Namespace##_heapify(Type *array, int n) \
{ \
    for (int i = (n-1)/2; i >= 0; --i) { \
        SIFT_DOWN(Namespace)(array, n, i); \
    } \
}
