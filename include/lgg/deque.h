#pragma once
#include "ds.h"
#include <stdbool.h>
#include <stdlib.h>

#define DEQUE_T(Namespace) struct Namespace##_deque

#define DEQUE(Namespace, ...) (DEQUE_T(Namespace)){ \
    .growth_factor = 2.0, \
    ##__VA_ARGS__ \
}

#define DEQUE_GENERATE(Namespace, Type, ...) \
 \
DEQUE_T(Namespace) { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
    int front; \
    int back; \
    __VA_ARGS__ \
}; \
 \
static inline bool Namespace##_is_empty(DEQUE_T(Namespace) const *deque) \
{ \
    return deque->size <= 0; \
} \
 \
static inline bool Namespace##_is_full(DEQUE_T(Namespace) const *deque) \
{ \
    return deque->size >= deque->capacity; \
} \
 \
static inline Type Namespace##_get(DEQUE_T(Namespace) const *deque, int index) \
{ \
    int pos = deque->front + index; \
    if (pos >= deque->capacity) { \
        pos -= deque->capacity; \
    } \
    return deque->array[pos]; \
} \
 \
static inline void Namespace##_set( \
    DEQUE_T(Namespace) *deque, \
    int index, \
    Type data) \
{ \
    int pos = deque->front + index; \
    if (pos >= deque->capacity) { \
        pos -= deque->capacity; \
    } \
    deque->array[pos] = data; \
} \
 \
static inline bool Namespace##_resize(DEQUE_T(Namespace) *deque) \
{ \
    int capacity = deque->capacity * deque->growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= deque->capacity) { \
        return false; \
    } \
    Type *array = malloc(capacity*sizeof(Type)); \
    if (!array) { \
        return false; \
    } \
    for (int i = 0; i < deque->size; ++i) { \
        array[i] = GET(Namespace, deque, i); \
    } \
    free(deque->array); \
    deque->array = array; \
    deque->capacity = capacity; \
    deque->front = 0; \
    deque->back = deque->size; \
    return true; \
} \
 \
static inline bool Namespace##_push(DEQUE_T(Namespace) *deque, Type data) \
{ \
    if (IS_FULL(Namespace, deque)) { \
        if (!RESIZE(Namespace, deque)) { \
            return false; \
        } \
    } \
    deque->array[deque->back++] = data; \
    deque->size++; \
    if (deque->back >= deque->capacity) { \
        deque->back = 0; \
    } \
    return true; \
} \
 \
static inline Type Namespace##_peek(DEQUE_T(Namespace) const *deque) \
{ \
    int index = deque->back > 0 ? deque->back-1 : deque->capacity - 1; \
    return deque->array[index]; \
} \
 \
static inline Type Namespace##_pop(DEQUE_T(Namespace) *deque) \
{ \
    Type data; \
    if (!IS_EMPTY(Namespace, deque)) { \
        data = PEEK(Namespace, deque); \
        deque->size--; \
        deque->back--; \
        if (deque->back < 0) { \
            deque->back = deque->capacity - 1; \
        } \
    } \
    return data; \
} \
 \
static inline bool Namespace##_push_left(DEQUE_T(Namespace) *deque, Type data) \
{ \
    if (IS_FULL(Namespace, deque)) { \
        if (!RESIZE(Namespace, deque)) { \
            return false; \
        } \
    } \
    deque->front = deque->front > 0 ? deque->front-1 : deque->capacity - 1; \
    deque->array[deque->front] = data; \
    deque->size++; \
    return true; \
} \
 \
static inline Type Namespace##_peek_left(DEQUE_T(Namespace) const *deque) \
{ \
    return deque->array[deque->front]; \
} \
 \
static inline Type Namespace##_pop_left(DEQUE_T(Namespace) *deque) \
{ \
    Type data; \
    if (!IS_EMPTY(Namespace, deque)) { \
        data = PEEK(Namespace, deque); \
        deque->size--; \
        deque->front++; \
        if (deque->front >= deque->capacity) { \
            deque->front = 0; \
        } \
    } \
    return data; \
} \
 \
static inline void Namespace##_clear(DEQUE_T(Namespace) *deque) \
{ \
    deque->size = 0; \
    deque->front = 0; \
    deque->back = 0; \
} \
 \
static inline void Namespace##_destroy(DEQUE_T(Namespace) *deque) \
{ \
    free(deque->array); \
    deque->size = 0; \
    deque->capacity = 0; \
    deque->front = 0; \
    deque->back = 0; \
} \
 \
ITER_T(Namespace) { \
    DEQUE_T(Namespace) *deque; \
    int index; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin(DEQUE_T(Namespace) *deque) \
{ \
    ITER_T(Namespace) it = { .deque = deque, .done = true }; \
    if (!IS_EMPTY(Namespace, deque)) { \
        it.done = false; \
        it.value = GET(Namespace, deque, 0); \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.index++; \
        if (it.index == it.deque->size) { \
            it.done = true; \
        } else { \
            it.value = GET(Namespace, it.deque, it.index); \
        } \
    } \
    return it; \
} \
 \
static inline Type Namespace##_value(ITER_T(Namespace) it) \
{ \
    return it.deque->array[it.index]; \
}
