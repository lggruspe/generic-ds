#pragma once
#include "algorithms/heap.h"
#include <stdbool.h>

#define HEAPSORT_GENERATE(Name, Type, LessThan) \
 \
static inline bool Name##_p_is_greater_than(Type a, Type b) \
{ \
    return (LessThan)(b, a); \
} \
 \
HEAP_GENERATE(Name, Type, Name##_p_is_greater_than) \
 \
static inline void Name##_sort(Type *array, int n) \
{ \
    while (n > 0) { \
        Type max = array[0]; \
        array[0] = array[--n]; \
        array[n] = max; \
    } \
}
