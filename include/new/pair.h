#pragma once

#define PAIR_GENERATE(Name, Type1, Type2) \
 \
struct Name##_type { \
    Type1 first; \
    Type2 second; \
}; \
 \
static inline struct Name##_type Name##_make(Type1 first, Type2 second) \
{ \
    return (struct Name##_type){ .first = first, .second = second }; \
}
