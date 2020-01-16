#pragma once
#include "ds.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

#define CHASH_T(Namespace) struct Namespace##_chash

#define CHASH(Namespace) Namespace##_chash_constructor()

#define CHASH_GENERATE(Namespace, Type, Buckets, Hash, Equal) \
 \
LIST_GENERATE(Namespace##_chash, Type) \
 \
CHASH_T(Namespace) { \
    LIST_T(Namespace##_chash) chains[Buckets]; \
    int size; \
}; \
 \
CHASH_T(Namespace) Namespace##_chash_constructor() \
{ \
    CHASH_T(Namespace) table = { .size = 0 }; \
    for (int i = 0; i < (Buckets); ++i) { \
        table.chains[i] = LIST(Namespace##_chash); \
    } \
    return table; \
} \
 \
static inline bool Namespace##_is_empty(CHASH_T(Namespace) const *table) \
{ \
    return table->size == 0; \
} \
 \
static inline NODE_T(Namespace##_chash)* \
Namespace##_search_chain(LIST_T(Namespace##_chash) *chain, Type data) \
{ \
    ITER_T(Namespace##_chash) it = BEGIN(Namespace##_chash, chain); \
    while (!it.done) { \
        if ((Equal)(data, it.value)) { \
            return it.current; \
        } \
        it = NEXT(Namespace##_chash, it); \
    } \
    return NULL; \
} \
 \
static inline LIST_T(Namespace##_chash)* \
Namespace##_get_chain_pointer(CHASH_T(Namespace) *table, Type data) \
{ \
    int index = (Hash)(data); \
    return table->chains + index; \
} \
 \
static inline NODE_T(Namespace##_chash)* \
Namespace##_search_node(CHASH_T(Namespace) *table, Type data) \
{ \
    LIST_T(Namespace##_chash) *chain = Namespace##_get_chain_pointer(table, data); \
    return Namespace##_search_chain(chain, data); \
} \
 \
static inline bool Namespace##_insert(CHASH_T(Namespace) *table, Type data) \
{ \
    LIST_T(Namespace##_chash) *chain = Namespace##_get_chain_pointer(table, data); \
    NODE_T(Namespace##_chash) *node = Namespace##_search_chain(chain, data); \
    if (node) { \
        return false; \
    } \
    PUSH_LEFT(Namespace##_chash, chain, data); \
    table->size++; \
    return true; \
} \
 \
static inline bool Namespace##_delete(CHASH_T(Namespace) *table, Type data) \
{ \
    NODE_T(Namespace##_chash) *node = Namespace##_search_node(table, data); \
    if (!node) { \
        return false; \
    } \
    if (Namespace##_chash_delete_node(node)) { \
        free(node); \
    } \
    table->size--; \
    return true; \
} \
 \
static inline void Namespace##_clear(CHASH_T(Namespace) *table) \
{ \
    for (int i = 0; i < (Buckets); ++i) { \
        CLEAR(Namespace##_chash, table->chains+i); \
    } \
    table->size = 0; \
} \
 \
static inline void Namespace##_destroy(CHASH_T(Namespace) *table) \
{ \
    CLEAR(Namespace, table); \
} \
 \
ITER_T(Namespace) { \
    CHASH_T(Namespace) *table; \
    int index; \
    ITER_T(Namespace##_chash) chain_iter; \
    Type value; \
    bool done; \
}; \
 \
static inline ITER_T(Namespace) Namespace##_begin(CHASH_T(Namespace) *table) \
{ \
    ITER_T(Namespace) it = { .table = table, .done = true }; \
    if (!IS_EMPTY(Namespace, table)) { \
        for (int i = 0; i < (Buckets); ++i) { \
            ITER_T(Namespace##_chash) jt = BEGIN(Namespace##_chash, table->chains+i); \
            if (!jt.done) { \
                it.done = false; \
                it.index = i; \
                it.chain_iter = jt; \
                it.value = jt.value; \
                break; \
            } \
        } \
        return it; \
    } \
} \
 \
static inline ITER_T(Namespace) Namespace##_next(ITER_T(Namespace) it) \
{ \
    if (!it.done) { \
        it.chain_iter = NEXT(Namespace##_chash, it.chain_iter); \
        if (!it.chain_iter.done) { \
            it.value = it.chain_iter.value; \
            return it; \
        } \
        for (int i = it.index+1; i < (Buckets); ++i) { \
            ITER_T(Namespace##_chash) jt = BEGIN(Namespace##_chash, it.table->chains+i); \
            if (!jt.done) { \
                it.index = i; \
                it.chain_iter = jt; \
                it.value = jt.value; \
                return it; \
            } \
        } \
        it.done = true; \
    } \
    return it; \
}
