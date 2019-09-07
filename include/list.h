#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define list(Namespace) struct Namespace##_list *
#define list_head(Namespace, list) Namespace##_head(list)
#define list_tail(Namespace, list) Namespace##_tail(list)
#define list_is_empty(Namespace, list) Namespace##_is_empty(list)
#define list_append(Namespace, list, suffix) Namespace##_append((list), (suffix))
#define list_new(Namespace, data) Namespace##_new(data)
#define list_delete(Namespace, list) Namespace##_delete(list)
#define list_delete_and_free(Namespace, list) Namespace##_delete_and_free(list)
#define list_search(Namespace, list, data) Namespace##_search((list), (data))
#define list_search_if(Namespace, list, predicate) Namespace##_search_if((list), (predicate))
#define list_search_compare(Namespace, list, data, compare) Namespace##_search_compare((list), (data), (compare))
#define list_destroy(Namespace, list) Namespace##_destroy(list)

#define LIST_RETURN_SEARCH_RESULT(condition) \
    if (!list) { \
        return NULL; \
    } \
    tail->next = NULL; \
    while (list && !(condition)) { \
        list = list->next; \
    } \
    tail->next = head; \
    return list

#define list_register(Namespace, Type) \
 \
struct Namespace##_list { \
    Type data; \
    list(Namespace) prev; \
    list(Namespace) next; \
}; \
 \
list(Namespace) Namespace##_head(list(Namespace) list) \
{ \
    return list; \
} \
 \
list(Namespace) Namespace##_tail(list(Namespace) list) \
{ \
    return list ? list->prev : NULL; \
} \
 \
bool Namespace##_is_empty(list(Namespace) list) \
{ \
    return !list; \
} \
 \
list(Namespace) Namespace##_append( \
    list(Namespace) list,  \
    list(Namespace) suffix) \
{ \
    if (!list) { \
        return suffix; \
    } \
    if (!suffix) { \
        return list; \
    } \
    list(Namespace) tail_list = list_tail(Namespace, list); \
    list(Namespace) tail_suffix = list_tail(Namespace, suffix); \
    tail_list->next = suffix; \
    suffix->prev = tail_list; \
    tail_suffix->next = list; \
    list->prev = tail_suffix; \
    return list; \
} \
 \
list(Namespace) Namespace##_delete(list(Namespace) list) \
{ \
    if (!list) { \
        return NULL; \
    } \
    list->prev->next = list->next; \
    list->next->prev = list->prev; \
    return list->next != list ? list->next : NULL; \
} \
 \
list(Namespace) Namespace##_new(Type data) \
{ \
    list(Namespace) node = malloc(sizeof(struct Namespace##_list)); \
    if (node) { \
        node->data = data; \
        node->prev = node; \
        node->next = node; \
    } \
    return node; \
} \
 \
list(Namespace) Namespace##_delete_and_free(list(Namespace) list) \
{ \
    list(Namespace) new_list = list_delete(Namespace, list); \
    if (list) { \
        free(list); \
    } \
    return new_list; \
} \
 \
list(Namespace) Namespace##_search( \
    list(Namespace) list,  \
    Type data) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(list->data == data); \
} \
 \
list(Namespace) Namespace##_search_if( \
    list(Namespace) list,  \
    bool (*predicate)(Type)) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(predicate(list->data)); \
} \
 \
list(Namespace) Namespace##_search_compare( \
    list(Namespace) list, \
    Type data, \
    int (*compare)(Type, Type)) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(compare(list->data, data) == 0); \
} \
 \
list(Namespace) Namespace##_destroy(list(Namespace) list) \
{ \
    if (!list) { \
        return NULL; \
    } \
    list(Namespace) tail = list_tail(Namespace, list); \
    tail->next = NULL; \
    while (!list_is_empty(Namespace, list)) { \
        list = list_delete_and_free(Namespace, list); \
    } \
    return list; \
}
