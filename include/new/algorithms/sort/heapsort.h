#pragma once
#include "../heap.h"
#include <stdbool.h>

#define HEAPSORT_GENERATE(Name, Type, LessThan) \
 \
static inline bool Name##_p_is_greater_than(Type a, Type b) \
{ \
    return (LessThan)(b, a); \
} \
 \
HEAP_GENERATE(Name##_p, Type, Name##_p_is_greater_than) \
 \
static inline void Name##_sort(Type *array, int n) \
{ \
    Name##_p_heapify(array, n); \
    while (n > 0) { \
        Type max = array[0]; \
        array[0] = array[n-1]; \
        array[n-1] = max; \
        Name##_p_sift_down(array, --n, 0); \
    } \
}
