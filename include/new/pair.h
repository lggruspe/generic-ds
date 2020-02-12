#pragma once

#define PAIR_GENERATE(Name, Type1, Type2) \
 \
typedef struct { \
    Type1 first; \
    Type2 second; \
} Name##_type; \
 \
static inline Name##_type Name##_make(Type1 first, Type2 second) \
{ \
    return (Name##_type){ .first = first, .second = second }; \
}
