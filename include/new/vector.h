#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define VECTOR_GENERATE(Name, Type) \
 \
typedef struct { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
} Name##_type; \
 \
static inline Name##_type Name##_create() \
{ \
    return (Name##_type){ .growth_factor = 2.0 }; \
} \
 \
static inline void Name##_destroy(Name##_type *v) \
{ \
    free(v->array); \
    v->size = 0; \
    v->capacity = 0; \
} \
 \
static inline void Name##_clear(Name##_type *v) \
{ \
    v->size = 0; \
} \
 \
static inline bool Name##_is_empty(Name##_type const *v) \
{ \
    return v->size <= 0; \
} \
 \
static inline bool Name##_is_full(Name##_type const *v) \
{ \
    return v->size >= v->capacity; \
} \
 \
static inline int Name##_size(Name##_type const *v) \
{ \
    return v->size; \
} \
 \
static inline bool Name##_grow(Name##_type *v) \
{ \
    int capacity = v->capacity * v->growth_factor; \
    if (capacity <= 0) {\
        capacity = 1;\
    }\
    if (capacity <= v->capacity) { \
        return false; \
    } \
    Type *array = realloc(v->array, capacity * sizeof(Type)); \
    if (!array) { \
        return false; \
    } \
    v->array = array; \
    v->capacity = capacity; \
    return true; \
} \
 \
static inline bool Name##_push(Name##_type *v, Type data) \
{ \
    if (Name##_is_full(v)) { \
        if (!Name##_grow(v)) { \
            return false; \
        } \
    } \
    v->array[v->size++] = data; \
    return true; \
} \
 \
static inline Type Name##_peek(Name##_type const *v) \
{ \
    return v->array[v->size-1]; \
} \
 \
static inline Type Name##_pop(Name##_type *v) \
{ \
    Type data; \
    if (!Name##_is_empty(v)) { \
        data = Name##_peek(v); \
        v->size--; \
    } \
    return data; \
} \
 \
static inline bool Name##_push_front(Name##_type *v, Type data) \
{ \
    if (Name##_is_full(v)) { \
        if (!Name##_grow(v)) { \
            return false; \
        } \
    } \
    for (int i = v->size-1; i >= 0; --i) { \
        v->array[i+1] = v->array[i]; \
    } \
    v->array[0] = data; \
    return true; \
} \
 \
static inline Type Name##_peek_front(Name##_type const *v) \
{ \
    return v->array[0]; \
} \
 \
static inline Type Name##_pop_front(Name##_type *v) \
{ \
    Type data = Name##_peek_front(v); \
    if (!Name##_is_empty(v)) { \
        for (int i = 1; i < v->size; ++i) { \
            v->array[i-1] = v->array[i]; \
        } \
        v->size--; \
    } \
    return data; \
} \
 \
static inline Type Name##_get(Name##_type const *v, int index) \
{ \
    return v->array[index]; \
} \
 \
static inline bool Name##_set(Name##_type *v, int index, Type data) \
{ \
    if (index < 0 || index >= v->size) { \
        return false; \
    } \
    v->array[index] = data; \
    return true; \
}
