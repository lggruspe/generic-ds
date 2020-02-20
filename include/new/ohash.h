#pragma once
#include <stdbool.h>

// TODO record earliest deleted spot and move result to that spot

#define OHASH_GENERATE(Name, Type, Hash, BucketSize, Equal) \
 \
typedef struct Name##_node { \
    Type data; \
    bool valid; \
    bool deleted; \
} Name##_node; \
 \
typedef struct { \
    Name##_node array[BucketSize]; \
    int size; \
} Name##_type; \
 \
Name##_type Name##_create() \
{ \
    Name##_type m = { .size = 0 }; \
    for (int i = 0; i < (BucketSize); ++i) { \
        m.array[i].valid = false; \
        m.array[i].deleted = false; \
    } \
    return m; \
} \
 \
void Name##_destroy(Name##_type *m) \
{ \
    m->size = 0; \
} \
 \
void Name##_clear(Name##_type *m) \
{ \
    for (int i = 0; i < (BucketSize); ++i) { \
        m->array[i].valid = false; \
        m->array[i].deleted = false; \
    } \
    m->size = 0; \
} \
 \
int Name##_hash(Type data) \
{ \
    return (Hash)(data) % (BucketSize); \
} \
 \
bool Name##_equal(Type a, Type b) \
{ \
    return (Equal)(a, b); \
} \
 \
bool Name##_is_empty(Name##_type const *m) \
{ \
    return m->size == 0; \
} \
 \
bool Name##_is_full(Name##_type const *m) \
{ \
    return m->size >= (BucketSize); \
} \
 \
int Name##_size(Name##_type const *m) \
{ \
    return m->size; \
} \
 \
Type Name##_get(Name##_type const *m, int index) \
{ \
    return m->array[index].data; \
} \
 \
void Name##_set(Name##_type *m, int index, Type data) \
{ \
    m->array[index].data = data; \
} \
 \
int Name##_search(Name##_type const *m, Type data) \
{ \
    int const hash = Name##_hash(data); \
    int i = hash; \
    do { \
        Name##_node entry = m->array[i]; \
        if (!entry.valid) { \
            return -1; \
        } else if (entry.deleted) { \
            continue; \
        } else if (Name##_equal(entry.data, data)) { \
            return i; \
        } \
        if (++i >= (BucketSize)) { \
            i = 0; \
        } \
    } while (i != hash); \
    return -1; \
} \
 \
bool Name##_insert(Name##_type *m, Type data) \
{ \
    int const hash = Name##_hash(data); \
    int i = hash; \
    do { \
        Name##_node entry = m->array[i]; \
        if (!entry.valid || entry.deleted) { \
            m->array[i].data = data; \
            m->array[i].valid = true; \
            m->array[i].deleted = false; \
            m->size++; \
            return true; \
        } else if (Name##_equal(entry.data, data)) { \
            m->array[i].data = data; \
            return true; \
        } \
        if (++i >= (BucketSize)) { \
            i = 0; \
        } \
    } while (i != hash); \
    return false; \
} \
 \
void Name##_delete(Name##_type *m, Type data) \
{ \
    int const hash = Name##_hash(data); \
    int i = hash; \
    do {  \
        Name##_node entry = m->array[i]; \
        if (!entry.valid) { \
            return; \
        } else if (entry.deleted) { \
            continue; \
        } else if (Name##_equal(entry.data, data)) { \
            m->array[i].deleted = true; \
            m->size--; \
            return; \
        } \
        if (++i >= (BucketSize)) { \
            i = 0; \
        } \
    } while (i != hash); \
} \
 \
bool Name##_is_valid(Name##_type const *m, int index) \
{ \
    if (index < 0 || index >= (BucketSize)) { \
        return false; \
    } \
    Name##_node entry = m->array[index]; \
    return entry.valid && !(entry.deleted); \
} \
 \
double Name##_load_factor(Name##_type const *m) \
{ \
    return (double)(m->size)/(BucketSize); \
}
