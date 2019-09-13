#pragma once
#include <stdbool.h>
#include <stdlib.h>

// slist_delete_after returns deleted node
// slist_delete returns new head
// insert and operations return leftmost available node

#define slist_struct(Namespace) struct Namespace##_slist
#define slist(Namespace) slist_struct(Namespace) *
#define slist_new(Namespace, Data, ...) Namespace##_slist_new((slist_struct(Namespace)){ .data = (Data), ##__VA_ARGS__ })
#define slist_head(Namespace, list) Namespace##_slist_head(list)
#define slist_tail(Namespace, list) Namespace##_slist_tail(list)
#define slist_delete(Namespace, list) Namespace##_slist_delete(list)
#define slist_delete_and_free(Namespace, list) Namespace##_slist_delete_and_free(list)
#define slist_delete_after(Namespace, list) Namespace##_slist_delete_after(list)
#define slist_delete_and_free_after(Namespace, list) Namespace##_slist_delete_and_free_after(list)
#define slist_destroy(Namespace, list) Namespace##_slist_destroy(list)
#define slist_search(Namespace, list, data) Namespace##_slist_search((list), (data))
#define slist_search_if(Namespace, list, predicate) Namespace##_slist_search_if((list), (predicate))
#define slist_search_compare(Namespace, list, data, compare) Namespace##_slist_search_compare((list), (data), (compare))
#define slist_insert(Namespace, list, node) Namespace##_slist_insert((list), (node))
#define slist_insert_after(Namespace, list, node) Namespace##_slist_insert_after((list), (node))
#define slist_append(Namespace, list, suffix) Namespace##_slist_append((list), (suffix))

#define slist_register(Namespace, Type) \
 \
slist_struct(Namespace) { \
    Type data; \
    slist(Namespace) next; \
}; \
 \
slist(Namespace) Namespace##_slist_new(slist_struct(Namespace) args) \
{ \
    slist(Namespace) list = malloc(sizeof(slist_struct(Namespace))); \
    if (list) { \
        *list = args; \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_head(slist(Namespace) list) \
{ \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_tail(slist(Namespace) list) \
{ \
    if (!list) { \
        return NULL; \
    } \
    while (list->next) { \
        list = list->next; \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_delete_after(slist(Namespace) list) \
{ \
    if (!list || !(list->next)) { \
        return NULL; \
    } \
    slist(Namespace) node = list->next; \
    list->next = node->next; \
    return node; \
} \
 \
slist(Namespace) Namespace##_slist_delete_and_free_after(slist(Namespace) list) \
{ \
    slist(Namespace) node = slist_delete_after(Namespace, list); \
    if (node) { \
        free(node); \
    } \
    return NULL; \
} \
 \
slist(Namespace) Namespace##_slist_delete(slist(Namespace) list) \
{ \
    if (!list || !(list->next)) { \
        return NULL; \
    } \
    return list->next; \
} \
 \
slist(Namespace) Namespace##_slist_delete_and_free(slist(Namespace) list) \
{ \
    slist(Namespace) head = list; \
    list = slist_delete(Namespace, list); \
    if (head) { \
        free(head); \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_destroy(slist(Namespace) list) \
{ \
    while (list) { \
        list = slist_delete_and_free(Namespace, list); \
    } \
    return NULL; \
} \
 \
slist(Namespace) Namespace##_slist_search(slist(Namespace) list, Type data) \
{ \
    while (list && list->data != data) { \
        list = list->next; \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_search_if( \
    slist(Namespace) list,  \
    bool (*predicate)(Type)) \
{ \
    while (list && !predicate(list->data)) { \
        list = list->next; \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_search_compare( \
    slist(Namespace) list, \
    Type data, \
    int (*compare)(Type, Type)) \
{ \
    while (list && compare(data, list->data) != 0) { \
        list = list->next; \
    } \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_insert( \
    slist(Namespace) list,  \
    slist(Namespace) node) \
{ \
    if (!list) { \
        return node; \
    } \
    if (!node) { \
        return list; \
    } \
    node->next = list; \
    return node; \
} \
 \
slist(Namespace) Namespace##_slist_insert_after( \
    slist(Namespace) list,  \
    slist(Namespace) node) \
{ \
    if (!list) { \
        return node; \
    } \
    if (!node) { \
        return list; \
    } \
    node->next = list->next; \
    list->next = node; \
    return list; \
} \
 \
slist(Namespace) Namespace##_slist_append( \
    slist(Namespace) list, \
    slist(Namespace) suffix) \
{ \
    if (!list) { \
        return suffix; \
    } \
    slist(Namespace) tail = slist_tail(Namespace, list); \
    tail->next = suffix; \
    return list; \
}
