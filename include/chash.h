#pragma once
#include "list.h"

#define chash(Namespace) struct Namespace##_chash
#define chash_chain(Namespace) list(Namespace)
#define chash_chain_search(Namespace, table, chain, data) Namespace##_chash_chain_search((table), (chain), (data))
#define chash_create(Namespace, Hash, ...) (chash(Namespace)){ .size = 0, .hash = (Hash), __VA_ARGS__ }
#define chash_hash(Namespace, table, data) Namespace##_chash_hash((table), (data))
#define chash_compare(Namespace, table, a, b) Namespace##_chash_compare((table), (a), (b))
#define chash_search(Namespace, table, data) Namespace##_chash_search((table), (data))
#define chash_insert(Namespace, table, data) Namespace##_chash_insert((table), (data))
#define chash_delete(Namespace, table, data) Namespace##_chash_delete((table), (data))
#define chash_destroy(Namespace, table) Namespace##_chash_destroy(table)

#define chash_register(Namespace, Type, Bucket_size) \
 \
list_register(Namespace, Type) \
 \
chash(Namespace) { \
    chash_chain(Namespace) array[Bucket_size]; \
    int size; \
    int (*hash)(Type); \
    int (*compare)(Type, Type); \
}; \
 \
int Namespace##_chash_hash(chash(Namespace) table, Type data) \
{ \
    return table.hash(data) % Bucket_size; \
} \
 \
int Namespace##_chash_compare(chash(Namespace) table, Type a, Type b) \
{ \
    return table.compare ? table.compare(a, b) : a < b ? -1 : a == b ? 0 : 1; \
} \
 \
chash_chain(Namespace) Namespace##_chash_chain_search( \
    chash(Namespace) table, \
    chash_chain(Namespace) chain, \
    Type data) \
{ \
    if (table.compare) { \
        return list_search_compare(Namespace, chain, data, table.compare); \
    } else { \
        return list_search(Namespace, chain, data); \
    } \
} \
         \
chash_chain(Namespace) Namespace##_chash_search(chash(Namespace) table, Type data) \
{ \
    int index = chash_hash(Namespace, table, data); \
    return chash_chain_search(Namespace, table, table.array[index], data); \
} \
 \
chash(Namespace) Namespace##_chash_insert(chash(Namespace) table, Type data) \
{ \
    int index = chash_hash(Namespace, table, data); \
    chash_chain(Namespace) node = chash_chain_search( \
        Namespace,  \
        table,  \
        table.array[index],  \
        data); \
    if (node) { \
        node->data = data; \
        return table; \
    } \
    chash_chain(Namespace) new_node = list_new(Namespace, data); \
    table.array[index] = list_append(Namespace, new_node, table.array[index]); \
    if (table.array[index] == new_node) { \
        table.size++; \
    } \
    return table; \
} \
 \
chash(Namespace) Namespace##_chash_delete(chash(Namespace) table, Type data) \
{ \
    int index = chash_hash(Namespace, table, data); \
    chash_chain(Namespace) node = chash_chain_search( \
        Namespace,  \
        table,  \
        table.array[index],  \
        data); \
    if (node && chash_compare(Namespace, table, data, node->data) == 0) { \
        table.array[index] = list_delete_and_free(Namespace, node); \
        table.size--; \
    } \
    return table; \
} \
 \
chash(Namespace) Namespace##_chash_destroy(chash(Namespace) table) \
{ \
    for (int i = 0; i < Bucket_size; ++i) { \
        table.array[i] = list_destroy(Namespace, table.array[i]); \
    } \
    table.size = 0; \
    return table; \
}
