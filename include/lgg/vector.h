#pragma once
#include "ds.h"
#include <stdbool.h>
#include <stdlib.h>

#define VECTOR_T(Namespace) struct Namespace##_vector

#define VECTOR(Namespace, ...) (VECTOR_T(Namespace)){ \
    .growth_factor = 2.0, \
    ##__VA_ARGS__ \
}

#define VECTOR_GENERATE(Namespace, Type, ...) \
 \
VECTOR_T(Namespace) { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
    __VA_ARGS__ \
}; \
 \
static inline bool Namespace##_is_empty(VECTOR_T(Namespace) const *vector) \
{ \
    return vector->size <= 0; \
} \
 \
static inline bool Namespace##_is_full(VECTOR_T(Namespace) const *vector) \
{ \
    return vector->size >= vector->capacity; \
} \
 \
static inline bool Namespace##_resize(VECTOR_T(Namespace) *vector) \
{ \
    int capacity = vector->capacity * vector->growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= vector->capacity) { \
        return false; \
    } \
    Type *array = realloc(vector->array, capacity*sizeof(Type)); \
    if (!array) { \
        return false; \
    } \
    vector->array = array; \
    vector->capacity = capacity; \
    return true; \
} \
 \
static inline bool Namespace##_push(VECTOR_T(Namespace) *vector, Type data) \
{ \
    if (IS_FULL(Namespace, vector)) { \
        bool ok = RESIZE(Namespace, vector); \
        if (!ok) { \
            return false; \
        } \
    } \
    vector->array[vector->size++] = data; \
    return true; \
} \
 \
static inline Type Namespace##_peek(VECTOR_T(Namespace) const *vector) \
{ \
    return vector->array[vector->size-1]; \
} \
 \
static inline Type Namespace##_pop(VECTOR_T(Namespace) *vector) \
{ \
    Type data; \
    if (!IS_EMPTY(Namespace, vector)) { \
        data = PEEK(Namespace, vector); \
        vector->size--; \
    } \
    return data; \
} \
 \
static inline Type Namespace##_get(VECTOR_T(Namespace) const *vector, int index) \
{ \
    return vector->array[index]; \
} \
 \
static inline bool Namespace##_set( \
        VECTOR_T(Namespace) *vector, \
        int index, \
        Type data) \
{ \
    vector->array[index] = data; \
} \
 \
static inline void Namespace##_clear(VECTOR_T(Namespace) *vector) \
{ \
    vector->size = 0; \
} \
 \
static inline void Namespace##_destroy(VECTOR_T(Namespace) *vector) \
{ \
    free(vector->array); \
    vector->size = 0; \
    vector->capacity = 0; \
} \
 \
ITER_T(Namespace) { \
    VECTOR_T(Namespace) *vector; \
    int index; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin( \
        VECTOR_T(Namespace) *vector) \
{ \
    ITER_T(Namespace) it = { .vector = vector, .done = true }; \
    if (!IS_EMPTY(Namespace, vector)) { \
        it.done = false; \
        it.value = it.vector->array[0]; \
    } \
    return it; \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.index++; \
        if (it.index == it.vector->size) { \
            it.done = true; \
        } else { \
            it.value = it.vector->array[it.index]; \
        } \
    } \
    return it; \
} \
 \
static inline Type Namespace##_value(ITER_T(Namespace) it) \
{ \
    return it.vector->array[it.index]; \
}
