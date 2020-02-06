#pragma once

#define Pair(Namespace) struct Namespace##_pair_type

#define PAIR_GENERATE(Namespace, Type1, Type2) \
 \
Pair(Namespace) { \
    Type1 first; \
    Type2 second; \
}; \
 \
static inline Pair(Namespace) Namespace##_make(Type1 first, Type2 second) \
{ \
    return (Pair(Namespace)){ .first = first, .second = second }; \
} \
 \
struct { \
    Pair(Namespace) (*make)(Type1, Type2); \
} Namespace = { \
    .make = Namespace##_make, \
};
