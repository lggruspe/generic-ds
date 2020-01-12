#pragma once
#include "heap.h"
#include "vector.h"
#include <stdbool.h>

#define PQUEUE_T(Namespace) VECTOR_T(Namespace##_pqueue)

#define PQUEUE(Namespace, ...) VECTOR(Namespace##_pqueue, ##__VA_ARGS__)

#define PQUEUE_GENERATE(Namespace, Type, LessThan) \
 \
VECTOR_GENERATE(Namespace##_pqueue, Type) \
 \
HEAP_GENERATE(Namespace##_pqueue, Type, (LessThan)) \
 \
static inline bool Namespace##_is_empty(PQUEUE_T(Namespace) const *queue) \
{ \
    return IS_EMPTY(Namespace##_pqueue, queue); \
} \
 \
static inline bool Namespace##_insert(PQUEUE_T(Namespace) *queue, Type data) \
{ \
    PUSH(Namespace##_pqueue, queue, data); \
    SIFT_UP(Namespace##_pqueue)(queue->array, queue->size-1); \
} \
 \
static inline Type Namespace##_peek_left(PQUEUE_T(Namespace) const *queue) \
{ \
    return queue->array[0]; \
} \
 \
static inline Type Namespace##_pop_left(PQUEUE_T(Namespace) *queue) \
{ \
    Type data = PEEK_LEFT(Namespace, queue); \
    queue->array[0] = POP(Namespace##_pqueue, queue); \
    SIFT_DOWN(Namespace##_pqueue)(queue->array, queue->size, 0); \
    return data; \
} \
 \
static inline void Namespace##_clear(PQUEUE_T(Namespace) *queue) \
{ \
    CLEAR(Namespace##_pqueue, queue); \
} \
 \
static inline void Namespace##_destroy(PQUEUE_T(Namespace) *queue) \
{ \
    DESTROY(Namespace##_pqueue, queue); \
} \
 \
ITER_T(Namespace) { \
    PQUEUE_T(Namespace) *queue; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin(PQUEUE_T(Namespace) *queue) \
{ \
    /* NOTE: iterates by deleting elements from queue */ \
    ITER_T(Namespace) it = { .queue = queue, .done = true }; \
    if (!IS_EMPTY(Namespace, queue)) { \
        it.done = false; \
        it.value = POP_LEFT(Namespace, queue); \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.value = POP_LEFT(Namespace, it.queue); \
        if (IS_EMPTY(Namespace, it.queue)) { \
            it.done = true; \
        } \
    } \
    return it; \
}
