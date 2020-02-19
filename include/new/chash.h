#pragma once
#include "list.h"
#include <stdbool.h>

#define CHASH_GENERATE(Name, Type, Hash, BucketSize, Equal) \
 \
LIST_GENERATE(Name##_chain, Type) \
 \
typedef Name##_chain_node Name##_node; \
 \
typedef struct Name##_type { \
    Name##_node *array[BucketSize]; \
    int size; \
} Name##_type; \
 \
Name##_type Name##_create() \
{ \
    Name##_type m = { .size = 0 }; \
    for (int i = 0; i < (BucketSize); ++i) { \
        m.array[i] = NULL; \
    } \
    return m; \
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
    return m->size == 0;     \
} \
 \
Type (*const Name##_get)(Name##_node const*) = Name##_chain_get; \
 \
void (*const Name##_set)(Name##_node*, Type) = Name##_chain_set; \
 \
Name##_node *Name##_chain_search(Name##_node *head, Type data) \
{ \
    if (!head) { \
        return NULL; \
    } \
    Name##_node *n = head; \
    do { \
        if (Name##_equal(Name##_get(n), data)) { \
            return n; \
        } \
        n = Name##_chain_next(n); \
    } while (n != head); \
    return NULL; \
} \
 \
Name##_node *Name##_search(Name##_type *m, Type data) \
{ \
    int index = Name##_hash(data); \
    return Name##_chain_search(m->array[index], data); \
} \
 \
void Name##_destroy(Name##_type *m) \
{ \
    for (int i = 0; i < (BucketSize); ++i) { \
        Name##_chain_destroy(m->array[i]); \
        m->array[i] = NULL; \
    } \
    m->size = 0; \
} \
 \
bool Name##_insert(Name##_type *m, Type data) \
{ \
    int index = Name##_hash(data); \
    Name##_node *n = Name##_chain_search(m->array[index], data); \
    if (n) { \
        n->data = data; \
        return true; \
    } \
    Name##_node *head = Name##_chain_new(data); \
    m->array[index] = Name##_chain_append(head, m->array[index]); \
    if (head && m->array[index] == head) { \
        m->size++; \
        return true; \
    } \
    return false; \
} \
 \
void Name##_delete(Name##_type *m, Type data) \
{ \
    int index = Name##_hash(data); \
    Name##_node *n = Name##_chain_search(m->array[index], data); \
    if (n) { \
        if (n == m->array[index]) { \
            m->array[index] = n->next; \
            if (m->array[index] == n) { \
                m->array[index] = NULL; \
            } \
        } \
        Name##_chain_delete(n); \
        m->size--; \
    } \
}
