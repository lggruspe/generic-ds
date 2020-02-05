#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define Vector(Namespace) struct Namespace##_vector_type

#define VECTOR_GENERATE(Namespace, Type) \
 \
Vector(Namespace) { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
}; \
 \
static inline Vector(Namespace) Namespace##_create() \
{ \
    return (Vector(Namespace)){ .growth_factor = 2.0 }; \
} \
 \
static inline void Namespace##_destroy(Vector(Namespace) *v) \
{ \
    free(v->array); \
    v->size = 0; \
    v->capacity = 0; \
} \
 \
static inline bool Namespace##_is_empty(Vector(Namespace) *v) \
{ \
    return v->size == 0; \
} \
 \
static inline bool Namespace##_is_full(Vector(Namespace) *v) \
{ \
    return v->size == v->capacity; \
} \
 \
static inline int Namespace##_size(Vector(Namespace) *v) \
{ \
    return v->size; \
} \
 \
static inline bool Namespace##_grow(Vector(Namespace) *v) \
{ \
    int capacity = v->capacity * v->growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= v->capacity) { \
        return false; \
    } \
    Type *array = realloc(v->array, sizeof(Type) * capacity); \
    if (!array) { \
        return false; \
    } \
    v->array = array; \
    v->capacity = capacity; \
    return true;  \
} \
 \
static inline bool Namespace##_push(Vector(Namespace) *v, Type data) \
{ \
    if (Namespace##_is_full(v)) { \
        if (!Namespace##_grow(v)) { \
            return false; \
        } \
    } \
    v->array[v->size++] = data; \
    return true; \
} \
 \
static inline Type Namespace##_peek(Vector(Namespace) *v) \
{ \
    return v->array[v->size-1]; \
} \
 \
static inline Type Namespace##_pop(Vector(Namespace) *v) \
{ \
    Type data; \
    if (!Namespace##_is_empty(v)) { \
        v->size--; \
        data = v->array[v->size]; \
    } \
    return data; \
} \
 \
static inline Type Namespace##_get(Vector(Namespace) *v, int index) \
{ \
    return v->array[index]; \
} \
 \
static inline bool Namespace##_set(Vector(Namespace) *v, int index, Type data) \
{ \
    if (index < 0 || index >= v->size) { \
        return false; \
    } \
    v->array[index] = data; \
    return true; \
} \
 \
static inline void Namespace##_clear(Vector(Namespace) *v) \
{ \
    v->size = 0; \
} \
 \
struct { \
    Vector(Namespace) (*create)(void); \
    void (*destroy)(Vector(Namespace)*); \
    bool (*is_empty)(Vector(Namespace)*); \
    bool (*is_full)(Vector(Namespace)*); \
    int (*size)(Vector(Namespace)*); \
    bool (*push)(Vector(Namespace)*, Type); \
    Type (*peek)(Vector(Namespace)*); \
    Type (*pop)(Vector(Namespace)*); \
    Type (*get)(Vector(Namespace)*, int); \
    bool (*set)(Vector(Namespace)*, int, Type); \
    void (*clear)(Vector(Namespace)*); \
} Namespace = { \
    .create = Namespace##_create, \
    .destroy = Namespace##_destroy, \
    .is_empty = Namespace##_is_empty, \
    .is_full = Namespace##_is_full, \
    .size = Namespace##_size, \
    .push = Namespace##_push, \
    .peek = Namespace##_peek, \
    .pop = Namespace##_pop, \
    .get = Namespace##_get, \
    .set = Namespace##_set, \
    .clear = Namespace##_clear, \
};
