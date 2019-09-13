#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define list_struct(Namespace) struct Namespace##_list
#define list(Namespace) list_struct(Namespace) *
#define list_head(Namespace, list) Namespace##_list_head(list)
#define list_tail(Namespace, list) Namespace##_list_tail(list)
#define list_is_empty(Namespace, list) Namespace##_list_is_empty(list)
#define list_append(Namespace, list, suffix) Namespace##_list_append((list), (suffix))
#define list_new(Namespace, Data, ...) Namespace##_list_new((list_struct(Namespace)){ .data = (Data), ##__VA_ARGS__ })
#define list_delete(Namespace, list) Namespace##_list_delete(list)
#define list_delete_and_free(Namespace, list) Namespace##_list_delete_and_free(list)
#define list_search(Namespace, list, data) Namespace##_list_search((list), (data))
#define list_search_if(Namespace, list, predicate) Namespace##_list_search_if((list), (predicate))
#define list_search_compare(Namespace, list, data, compare) Namespace##_list_search_compare((list), (data), (compare))
#define list_destroy(Namespace, list) Namespace##_list_destroy(list)

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
list_struct(Namespace) { \
    Type data; \
    list(Namespace) prev; \
    list(Namespace) next; \
}; \
 \
list(Namespace) Namespace##_list_head(list(Namespace) list) \
{ \
    return list; \
} \
 \
list(Namespace) Namespace##_list_tail(list(Namespace) list) \
{ \
    return list ? list->prev : NULL; \
} \
 \
bool Namespace##_list_is_empty(list(Namespace) list) \
{ \
    return !list; \
} \
 \
list(Namespace) Namespace##_list_append( \
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
list(Namespace) Namespace##_list_delete(list(Namespace) list) \
{ \
    if (!list) { \
        return NULL; \
    } \
    list->prev->next = list->next; \
    list->next->prev = list->prev; \
    return list->next != list ? list->next : NULL; \
} \
 \
\
list(Namespace) Namespace##_list_new(list_struct(Namespace) args) \
{ \
    list(Namespace) node = malloc(sizeof(list_struct(Namespace))); \
    if (node) { \
        *node = args; \
        node->prev = node; \
        node->next = node; \
    } \
    return node; \
} \
 \
list(Namespace) Namespace##_list_delete_and_free(list(Namespace) list) \
{ \
    list(Namespace) new_list = list_delete(Namespace, list); \
    if (list) { \
        free(list); \
    } \
    return new_list; \
} \
 \
list(Namespace) Namespace##_list_search( \
    list(Namespace) list,  \
    Type data) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(list->data == data); \
} \
 \
list(Namespace) Namespace##_list_search_if( \
    list(Namespace) list,  \
    bool (*predicate)(Type)) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(predicate(list->data)); \
} \
 \
list(Namespace) Namespace##_list_search_compare( \
    list(Namespace) list, \
    Type data, \
    int (*compare)(Type, Type)) \
{ \
    list(Namespace) head = list_head(Namespace, list); \
    list(Namespace) tail = list_tail(Namespace, list); \
    LIST_RETURN_SEARCH_RESULT(compare(list->data, data) == 0); \
} \
 \
list(Namespace) Namespace##_list_destroy(list(Namespace) list) \
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
