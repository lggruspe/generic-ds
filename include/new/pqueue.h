#pragma once
#include "algorithms/heap.h"
#include "vector.h"
#include <stdbool.h>

/* min-priority q */

#define PQUEUE_GENERATE(Name, Type, LessThan) \
 \
VECTOR_GENERATE(Name##_p, Type) \
 \
typedef Name##_p_type Name##_type; \
 \
HEAP_GENERATE(Name##_p, Type, (LessThan)) \
 \
Name##_type (*const Name##_create)(void) = Name##_p_create; \
 \
void (*const Name##_destroy)(Name##_type*) = Name##_p_destroy; \
 \
void (*const Name##_clear)(Name##_type*) = Name##_p_clear; \
 \
bool (*const Name##_is_empty)(Name##_type const*) = Name##_p_is_empty; \
 \
int (*const Name##_size)(Name##_type const*) = Name##_p_size; \
 \
static inline bool Name##_insert(Name##_type *q, Type data) \
{ \
    if (!Name##_p_push(q, data)) { \
        return false; \
    } \
    Name##_p_sift_up(q->array, q->size-1); \
    return true; \
} \
 \
static inline Type Name##_peek_front(Name##_type const *q) \
{ \
    return q->array[0]; \
} \
 \
static inline Type Name##_pop_front(Name##_type *q) \
{ \
    Type data = Name##_peek_front(q); \
    q->array[0] = Name##_p_pop(q); \
    Name##_p_sift_down(q->array, q->size, 0); \
    return data; \
}
