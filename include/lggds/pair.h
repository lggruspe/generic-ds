#pragma once

#define pair(Namespace) struct Namespace##_pair

#define pair_register(Namespace, Type1, Type2) \
 \
struct Namespace##_pair { \
    Type1 first; \
    Type2 second; \
};
