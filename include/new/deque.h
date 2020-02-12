#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define DEQUE_GENERATE(Name, Type) \
 \
struct Name##_type { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
    int front; \
    int back; \
}; \
 \
static inline struct Name##_type Name##_create() \
{ \
    return (struct Name##_type){ .growth_factor = 2.0 }; \
} \
 \
static inline void Name##_destroy(struct Name##_type *q) \
{ \
    free(q->array); \
    q->size = 0; \
    q->capacity = 0; \
    q->front = 0; \
    q->back = 0; \
} \
 \
static inline void Name##_clear(struct Name##_type *q) \
{ \
    q->size = 0; \
    q->front = 0; \
    q->back = 0; \
} \
 \
static inline bool Name##_is_empty(struct Name##_type const *q) \
{ \
    return q->size <= 0; \
} \
 \
static inline bool Name##_is_full(struct Name##_type const *q) \
{ \
    return q->size >= q->capacity; \
} \
 \
static inline int Name##_size(struct Name##_type const *q) \
{ \
    return q->size; \
} \
 \
static inline int Name##_p_index(struct Name##_type const *q, int index) \
{ \
  int pos = index + q->front; \
    if (pos >= q->capacity) { \
        pos -= q->capacity; \
    } \
    return pos;    \
} \
 \
static inline Type Name##_get(struct Name##_type const *q, int index) \
{ \
    return q->array[Name##_p_index(q, index)]; \
} \
 \
static inline bool Name##_set(struct Name##_type *q, int index, Type data) \
{ \
    if (index < 0 || index >= q->size) { \
        return false; \
    } \
    q->array[Name##_p_index(q, index)] = data; \
    return true; \
} \
 \
static inline bool Name##_grow(struct Name##_type *q) \
{ \
    int capacity = q->capacity * q->growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= q->capacity) { \
        return false; \
    } \
    Type *array = malloc(capacity * sizeof(Type)); \
    if (!array) { \
        return false; \
    } \
    for (int i = 0; i < q->size; ++i) { \
        array[i] = Name##_get(q, i); \
    } \
    free(q->array); \
    q->array = array; \
    q->capacity = capacity; \
    q->front = 0; \
    q->back = q->size; \
    return true; \
} \
 \
static inline bool Name##_push(struct Name##_type *q, Type data) \
{ \
    if (Name##_is_full(q)) { \
        if (!Name##_grow(q)) { \
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
static inline Type Name##_peek(struct Name##_type const *q) \
{ \
    return q->array[q->back == 0 ? q->capacity - 1 : q->back - 1]; \
} \
 \
static inline Type Name##_pop(struct Name##_type *q) \
{ \
    Type data; \
    if (!Name##_is_empty(q)) { \
        data = Name##_peek(q); \
        q->size--; \
        q->back--; \
        if (q->back < 0) { \
            q->back = q->capacity - 1; \
        } \
    } \
    return data; \
} \
 \
static inline Type Name##_peek_front(struct Name##_type const *q) \
{ \
    return q->array[q->front]; \
} \
 \
static inline bool Name##_push_front(struct Name##_type *q, Type data) \
{ \
    if (Name##_is_full(q)) { \
        if (!Name##_grow(q)) { \
            return false; \
        } \
    } \
    q->front = q->front > 0 ? q->front-1 : q->capacity - 1; \
    q->array[q->front] = data; \
    q->size++; \
    return true; \
} \
 \
static inline Type Name##_pop_front(struct Name##_type *q) \
{ \
    Type data; \
    if (!Name##_is_empty(q)) { \
        data = Name##_peek_front(q); \
        q->size--; \
        q->front++; \
        if (q->front >= q->capacity) { \
            q->front = 0; \
        } \
    } \
    return data; \
}
