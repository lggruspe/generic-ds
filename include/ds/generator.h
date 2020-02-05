#pragma once
#include <stdbool.h>
#include <stddef.h>

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

typedef struct {
    void *label;
    bool done;
} Iterator;

#define GENERATOR(Type, Name, ...) \
Type Name(Iterator *prev, ##__VA_ARGS__) \
{ \
    struct { Type garbage; void *null; } impl = { .null = NULL }; \
    if (prev->done) { \
        goto end; \
    } \
    if (prev->label) { \
        goto *(prev->label); \
    }

#define yield(Value) \
        YIELD_IMPL((Value), CONCAT(l, __COUNTER__))

#define YIELD_IMPL(Value, Label) \
        prev->label = &&Label; \
        return (Value); \
    Label:

#define stop_generator() \
    end: \
        prev->done = true; \
        return impl.garbage; \
}

static inline Iterator create_iterator()
{
    return (Iterator){ .done = false, .label = NULL };
}
