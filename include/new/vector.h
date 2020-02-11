#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define VECTOR_GENERATE(Name, Type) \
 \
struct Name##_type { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
}; \
 \
static inline struct Name##_type Name##_create() \
{ \
    return (struct Name##_type){ .growth_factor = 2.0 }; \
} \
 \
static inline void Name##_destroy(struct Name##_type *v) \
{ \
    free(v->array); \
    v->size = 0; \
    v->capacity = 0; \
} \
 \
static inline void Name##_clear(struct Name##_type *v) \
{ \
    v->size = 0; \
} \
 \
static inline bool Name##_is_empty(struct Name##_type const *v) \
{ \
    return v->size <= 0; \
} \
 \
static inline bool Name##_is_full(struct Name##_type const *v) \
{ \
    return v->size >= v->capacity; \
} \
 \
static inline int Name##_size(struct Name##_type const *v) \
{ \
    return v->size; \
} \
 \
static inline bool Name##_grow(struct Name##_type *v) \
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
static inline bool Name##_push(struct Name##_type *v, Type data) \
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
static inline Type Name##_peek(struct Name##_type const *v) \
{ \
    return v->array[v->size-1]; \
} \
 \
static inline Type Name##_pop(struct Name##_type *v) \
{ \
    Type data; \
    if (!Name##_is_empty(v)) { \
        data = Name##_peek(v); \
        v->size--; \
    } \
    return data; \
} \
 \
static inline Type Name##_get(struct Name##_type const *v, int index) \
{ \
    return v->array[index]; \
} \
 \
static inline bool Name##_set(struct Name##_type *v, int index, Type data) \
{ \
    if (index < 0 || index >= v->size) { \
        return false; \
    } \
    v->array[index] = data; \
    return true; \
}
