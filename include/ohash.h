#pragma once
#include <stdbool.h>
#include <stdlib.h>

// TODO record earliest deleted spot and move result to that spot

#define ohash(Namespace) struct Namespace##_ohash
#define ohash_entry(Namespace) struct Namespace##_ohash_entry
#define ohash_create(Namespace, Hash, ...) Namespace##_ohash_create((ohash(Namespace)){ .hash = (Hash), __VA_ARGS__ })
#define ohash_load_factor(Namespace, table) Namespace##_ohash_load_factor(table)
#define ohash_hash(Namespace, table, data) Namespace##_ohash_hash((table), (data))
#define ohash_compare(Namespace, table, a, b) Namespace##_ohash_compare((table), (a), (b))
#define ohash_search(Namespace, table, data) Namespace##_ohash_search((table), (data))
#define ohash_insert(Namespace, table, data) Namespace##_ohash_insert((table), (data))
#define ohash_delete(Namespace, table, data) Namespace##_ohash_delete((table), (data))
#define ohash_destroy(Namespace, table) Namespace##_ohash_destroy(table)

#define ohash_register(Namespace, Type, Bucket_size) \
 \
int Namespace##_ohash_bucket_size = Bucket_size; \
 \
struct Namespace##_ohash_entry { \
    Type data; \
    bool valid; \
    bool deleted; \
}; \
 \
struct Namespace##_ohash { \
    ohash_entry(Namespace) *array; \
    int size; \
    int (*hash)(Type); \
    int (*compare)(Type, Type); \
}; \
 \
ohash(Namespace) Namespace##_ohash_create(ohash(Namespace) args) \
{ \
    ohash(Namespace) table = { \
        .array = malloc(sizeof(ohash_entry(Namespace)) * Bucket_size), \
        .hash = args.hash, \
        .compare = args.compare, \
    }; \
    if (table.array) { \
        for (int i = 0; i < Bucket_size; ++i) { \
            table.array[i].valid = false; \
            table.array[i].deleted = false; \
        } \
    } \
    return table; \
} \
 \
double Namespace##_ohash_load_factor(ohash(Namespace) table) \
{ \
    return (double)(table.size)/Bucket_size; \
} \
 \
int Namespace##_ohash_hash(ohash(Namespace) table, Type data) \
{ \
    return (table.hash(data)) % Bucket_size; \
} \
 \
int Namespace##_ohash_compare(ohash(Namespace) table, Type a, Type b) \
{ \
    return table.compare ? table.compare(a, b) : a < b ? -1 : a == b ? 0 : 1; \
} \
 \
int Namespace##_ohash_search(ohash(Namespace) table, Type data) \
{ \
    int hash = ohash_hash(Namespace, table, data); \
    for (int i = hash; i < Bucket_size; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid)) { \
            return -1; \
        } \
        if (entry.deleted) { \
            continue; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            return i; \
        } \
    } \
    for (int i = 0; i < hash; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid)) { \
            return -1; \
        } \
        if (entry.deleted) { \
            continue; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            return i; \
        } \
    } \
    return -1; \
} \
 \
ohash(Namespace) Namespace##_ohash_insert(ohash(Namespace) table, Type data) \
{ \
    int hash = ohash_hash(Namespace, table, data); \
    for (int i = hash; i < Bucket_size; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid) || entry.deleted) { \
            table.array[i] = (ohash_entry(Namespace)){  \
                .data = data,  \
                .valid = true, \
            }; \
            table.size++; \
            return table; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            table.array[i].data = data; \
            return table; \
        } \
    } \
    for (int i = 0; i < hash; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid) || entry.deleted) { \
            table.array[i] = (ohash_entry(Namespace)){  \
                .data = data,  \
                .valid = true, \
            }; \
            table.size++; \
            return table; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            table.array[i].data = data; \
            return table; \
        } \
    } \
    return table; \
} \
 \
ohash(Namespace) Namespace##_ohash_delete(ohash(Namespace) table, Type data) \
{ \
    int hash = ohash_hash(Namespace, table, data); \
    for (int i = hash; i < Bucket_size; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid)) { \
            return table; \
        } \
        if (entry.deleted) { \
            continue; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            table.array[i].deleted = true; \
            table.size--; \
            return table; \
        } \
    } \
    for (int i = 0; i < hash; ++i) { \
        ohash_entry(Namespace) entry = table.array[i]; \
        if (!(entry.valid)) { \
            return table; \
        } \
        if (entry.deleted) { \
            continue; \
        } \
        if (ohash_compare(Namespace, table, entry.data, data) == 0) { \
            table.array[i].deleted = true; \
            table.size--; \
            return table; \
        } \
    } \
    return table; \
} \
 \
ohash(Namespace) Namespace##_ohash_destroy(ohash(Namespace) table) \
{ \
    if (table.array) { \
        free(table.array); \
        table.array = NULL; \
    } \
    table.size = 0; \
    return table; \
}
