#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define LIST_GENERATE(Name, Type) \
 \
typedef struct Name##_node { \
    Type data; \
    struct Name##_node *prev; \
    struct Name##_node *next; \
} Name##_node; \
 \
static inline Name##_node *Name##_new(Type data) \
{ \
    Name##_node *node = malloc(sizeof(Name##_node)); \
    if (node) { \
        node->data = data; \
        node->prev = node; \
        node->next = node; \
    } \
    return node;  \
} \
 \
static inline Name##_node *Name##_delete(Name##_node *n) \
{ \
    if (!n || n->next == n) { \
        free(n); \
        return NULL; \
    } \
    n->prev->next = n->next; \
    n->next->prev = n->prev; \
    Name##_node *head = n->next; \
    free(n); \
    return head; \
} \
 \
static inline bool Name##_is_empty(Name##_node const *n) \
{ \
    return !n; \
} \
 \
static inline Type Name##_get(Name##_node const *n) \
{ \
    return n->data; \
} \
 \
static inline void Name##_set(Name##_node *n, Type data) \
{ \
    if (n) { \
        n->data = data; \
    } \
} \
 \
static inline Name##_node *Name##_prev(Name##_node const *n) \
{ \
    return n ? n->prev : NULL; \
} \
 \
static inline Name##_node *Name##_next(Name##_node const *n) \
{ \
    return n ? n->next : NULL; \
} \
 \
static inline Name##_node *Name##_append(Name##_node *prefix, Name##_node *suffix) \
{ \
    if (!prefix) { \
        return suffix; \
    } \
    if (!suffix) { \
        return prefix; \
    } \
    Name##_node *tail_prefix = prefix->prev; \
    Name##_node *tail_suffix = suffix->prev; \
    tail_prefix->next = suffix; \
    suffix->prev = tail_prefix; \
    tail_suffix->next = prefix; \
    prefix->prev = tail_suffix; \
    return prefix; \
} \
 \
static inline void Name##_destroy(Name##_node *n) \
{ \
    while (n) { \
        n = Name##_delete(n); \
    } \
}
