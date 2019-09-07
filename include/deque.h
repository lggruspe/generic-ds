#pragma once

#define deque(Namespace) struct Namespace##_deque
#define deque_create(Namespace, ...) (struct Namespace##_deque){ .growth_factor = 2.0, ##__VA_ARGS__ }
#define deque_is_full(Namespace, deque) Namespace##_is_full(deque)
#define deque_is_empty(Namespace, deque) Namespace##_is_empty(deque)
#define deque_resize(Namespace, deque) Namespace##_resize(deque)
#define deque_push(Namespace, deque, data) Namespace##_push((deque), (data))
#define deque_peek(Namespace, deque) Namespace##_peek(deque)
#define deque_pop(Namespace, deque) Namespace##_pop(deque)
#define deque_push_front(Namespace, deque, data) Namespace##_push_front((deque), (data))
#define deque_peek_front(Namespace, deque) Namespace##_peek_front(deque)
#define deque_pop_front(Namespace, deque) Namespace##_pop_front(deque)
#define deque_destroy(Namespace, deque) Namespace##_destroy(deque)

#define deque_index(Namespace, deque, index) Namespace##_index((deque), (index))
#define DEQUE_GET(Namespace, deque, index) (deque).array[deque_index(Namespace, (deque), (index))]

#define deque_register(Namespace, Type) \
 \
struct Namespace##_deque { \
    Type *array; \
    int size; \
    int capacity; \
    int front; \
    int back; \
    double growth_factor; \
}; \
 \
bool Namespace##_is_full(deque(Namespace) deque) \
{ \
    return deque.size >= deque.capacity; \
} \
 \
bool Namespace##_is_empty(deque(Namespace) deque) \
{ \
    return deque.size <= 0; \
} \
 \
deque(Namespace) Namespace##_resize(deque(Namespace) deque) \
{ \
    int capacity = deque.capacity * deque.growth_factor; \
    if (capacity <= 0) { \
        capacity = 1; \
    } \
    if (capacity <= deque.size) { \
        return deque; \
    } \
    Type *array = malloc(capacity * sizeof(Type)); \
    if (!array) { \
        return deque; \
    } \
    for (int i = deque.front; i < deque.capacity; ++i) { \
        array[i - deque.front] = deque.array[i]; \
    } \
    for (int i = 0; i < deque.back; ++i) { \
        array[i + deque.capacity - deque.front] = deque.array[i]; \
    } \
    free(deque.array); \
    deque.array = array; \
    deque.capacity = capacity; \
    deque.front = 0; \
    deque.back = deque.size; \
    return deque; \
} \
 \
deque(Namespace) Namespace##_push(deque(Namespace) deque, Type data) \
{ \
    if (deque_is_full(Namespace, deque)) { \
        deque = deque_resize(Namespace, deque); \
    } \
    if (!deque_is_full(Namespace, deque)) { \
        deque.array[deque.back++] = data; \
        if (deque.back >= deque.capacity) { \
            deque.back = 0; \
        } \
        deque.size++; \
    } \
    return deque; \
} \
 \
Type Namespace##_peek(deque(Namespace) deque) \
{ \
    return deque.array[deque.back == 0 ? deque.capacity - 1 : deque.back - 1]; \
} \
 \
deque(Namespace) Namespace##_pop(deque(Namespace) deque) \
{ \
    if (!deque_is_empty(Namespace, deque)) { \
        deque.back--; \
        if (deque.back < 0) { \
            deque.back = deque.capacity - 1; \
        } \
        deque.size--; \
    } \
    return deque; \
} \
 \
Type Namespace##_peek_front(deque(Namespace) deque) \
{ \
    return deque.array[deque.front]; \
} \
 \
deque(Namespace) Namespace##_push_front(deque(Namespace) deque, Type data) \
{ \
    if (deque_is_full(Namespace, deque)) { \
        deque = deque_resize(Namespace, deque); \
    } \
    if (!deque_is_full(Namespace, deque)) { \
        deque.front--; \
        if (deque.front < 0) { \
            deque.front = deque.capacity - 1; \
        } \
        deque.array[deque.front] = data; \
        deque.size++; \
    } \
    return deque; \
} \
 \
deque(Namespace) Namespace##_pop_front(deque(Namespace) deque) \
{ \
    if (!deque_is_empty(Namespace, deque)) { \
        deque.front++; \
        if (deque.front >= deque.capacity) { \
            deque.front = 0; \
        } \
        deque.size--; \
    } \
    return deque; \
} \
 \
deque(Namespace) Namespace##_destroy(deque(Namespace) deque) \
{ \
    if (deque.array) { \
        free(deque.array); \
        deque.array = NULL; \
    } \
    deque.size = 0; \
    deque.capacity = 0; \
    deque.front = 0; \
    deque.back = 0; \
    return deque; \
} \
 \
int Namespace##_index(deque(Namespace) deque, int index) \
{ \
  int logical_index = index + deque.front; \
    if (logical_index >= deque.capacity) { \
        logical_index -= deque.capacity; \
    } \
    return logical_index;    \
} \
 \
Type Namespace##_get(deque(Namespace) deque, int index) \
{ \
    int logical_index = index + deque.front; \
    if (logical_index >= deque.capacity) { \
        logical_index -= deque.capacity; \
    } \
    return deque.array[logical_index]; \
}
