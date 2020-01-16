#pragma once

#define PAIR_T(Namespace) struct Namespace##_pair

#define PAIR(Namespace, Value1, Value2) (PAIR_T(Namespace)){ \
    .first = (Value1), \
    .second = (Value2) \
}

#define PAIR_GENERATE(Namespace, Type1, Type2) \
 \
PAIR_T(Namespace) { \
    Type1 first; \
    Type2 second; \
};
