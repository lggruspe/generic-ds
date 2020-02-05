#pragma once
#include "generator.h"
#include <stdbool.h>
#include <stdlib.h>

#define Deque(Namespace) struct Namespace##_deque_type

#define DEQUE_GENERATE(Namespace, Type) \
 \
Deque(Namespace) { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
    int front; \
    int back; \
}; \
 \
static inline Deque(Namespace) Namespace##_create() \
{ \
    return (Deque(Namespace)){ .growth_factor = 2.0 }; \
} \
 \
static inline void Namespace##_destroy(Deque(Namespace) *q)  \
{ \
    free(q->array); \
    q->size = 0; \
    q->capacity = 0; \
    q->front = 0; \
    q->back = 0; \
} \
 \
static inline bool Namespace##_is_empty(Deque(Namespace) const *q) \
{ \
    return q->size <= 0; \
} \
 \
static inline bool Namespace##_is_full(Deque(Namespace) const *q) \
{ \
    return q->size >= q->capacity; \
} \
 \
static inline int Namespace##_size(Deque(Namespace) const *q) \
{ \
    return q->size; \
} \
 \
static inline Type Namespace##_get(Deque(Namespace) const *q, int index) \
{ \
    int pos = q->front + index; \
    if (pos >= q->capacity) { \
        pos -= q->capacity; \
    } \
    return q->array[pos]; \
} \
 \
static inline bool Namespace##_set( \
    Deque(Namespace) *q, \
    int index, \
    Type data) \
{ \
    if (index < 0 || index >= q->size) { \
        return false; \
    } \
    int pos = q->front + index; \
    if (pos >= q->capacity) { \
        pos -= q->capacity; \
    } \
    q->array[pos] = data; \
    return true; \
} \
 \
static inline bool Namespace##_grow(Deque(Namespace) *q) \
{ \
    int capacity = q->capacity * q->growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= q->capacity) { \
        return false; \
    } \
    Type *array = malloc(capacity*sizeof(Type)); \
    if (!array) { \
        return false; \
    } \
    for (int i = 0; i < q->size; ++i) { \
        array[i] = Namespace##_get(q, i); \
    } \
    free(q->array); \
    q->array = array; \
    q->capacity = capacity; \
    q->front = 0; \
    q->back = q->size; \
    return true; \
} \
 \
static inline bool Namespace##_push(Deque(Namespace) *q, Type data) \
{ \
    if (Namespace##_is_full(q)) { \
        if (!Namespace##_grow(q)) { \
            return false; \
        } \
    } \
    q->array[q->back++] = data; \
    q->size++; \
    if (q->back >= q->capacity) { \
        q->back = 0; \
    } \
    return true; \
} \
 \
static inline Type Namespace##_peek(Deque(Namespace) const *q) \
{ \
    int index = q->back > 0 ? q->back-1 : q->capacity - 1; \
    return q->array[index]; \
} \
 \
static inline Type Namespace##_pop(Deque(Namespace) *q) \
{ \
    Type data; \
    if (!Namespace##_is_empty(q)) { \
        data = Namespace##_peek(q); \
        q->size--; \
        q->back--; \
        if (q->back < 0) { \
            q->back = q->capacity - 1; \
        } \
    } \
    return data; \
} \
 \
static inline bool Namespace##_push_left(Deque(Namespace) *q, Type data) \
{ \
    if (Namespace##_is_full(q)) { \
        if (!Namespace##_grow(q)) { \
            return false; \
        } \
    } \
    q->front = q->front > 0 ? q->front-1 : q->capacity - 1; \
    q->array[q->front] = data; \
    q->size++; \
    return true; \
} \
 \
static inline Type Namespace##_peek_left(Deque(Namespace) const *q) \
{ \
    return q->array[q->front]; \
} \
 \
static inline Type Namespace##_pop_left(Deque(Namespace) *q) \
{ \
    Type data; \
    if (!Namespace##_is_empty(q)) { \
        data = Namespace##_peek_left(q); \
        q->size--; \
        q->front++; \
        if (q->front >= q->capacity) { \
            q->front = 0; \
        } \
    } \
    return data; \
} \
 \
static inline void Namespace##_clear(Deque(Namespace) *q) \
{ \
    q->size = 0; \
    q->front = 0; \
    q->back = 0; \
} \
 \
static inline GENERATOR(Type, Namespace##_iterate, Deque(Namespace) const *q) \
{ \
    static int i; \
    for (i = 0; i < q->size; ++i) { \
        yield(Namespace##_get(q, i)); \
    } \
    stop_generator(); \
} \
 \
struct { \
    Deque(Namespace) (*create)(void); \
    void (*destroy)(Deque(Namespace)*); \
    bool (*is_empty)(Deque(Namespace) const*); \
    bool (*is_full)(Deque(Namespace) const*); \
    int (*size)(Deque(Namespace) const*); \
    Type (*get)(Deque(Namespace) const*, int); \
    bool (*set)(Deque(Namespace)*, int, Type); \
    bool (*push)(Deque(Namespace)*, Type); \
    Type (*peek)(Deque(Namespace) const*); \
    Type (*pop)(Deque(Namespace)*); \
    bool (*push_left)(Deque(Namespace)*, Type); \
    Type (*peek_left)(Deque(Namespace) const*); \
    Type (*pop_left)(Deque(Namespace)*); \
    void (*clear)(Deque(Namespace)*); \
    Type (*iterate)(Iterator*, Deque(Namespace) const*); \
} Namespace = { \
    .create = Namespace##_create, \
    .destroy = Namespace##_destroy, \
    .is_empty = Namespace##_is_empty, \
    .is_full = Namespace##_is_full, \
    .size = Namespace##_size, \
    .get = Namespace##_get, \
    .set = Namespace##_set, \
    .push = Namespace##_push, \
    .peek = Namespace##_peek, \
    .pop = Namespace##_pop, \
    .push_left = Namespace##_push_left, \
    .peek_left = Namespace##_peek_left, \
    .pop_left = Namespace##_pop_left, \
    .clear = Namespace##_clear, \
    .iterate = Namespace##_iterate, \
};
