#pragma once

#define IS_EMPTY(Namespace, Container) Namespace##_is_empty(Container)

#define IS_FULL(Namespace, Container) Namespace##_is_full(Container)

#define RESIZE(Namespace, Container) Namespace##_resize(Container)

#define PUSH(Namespace, Container, Data) Namespace##_push((Container), (Data))

#define PEEK(Namespace, Container) Namespace##_peek(Container)

#define POP(Namespace, Container) Namespace##_pop(Container)

#define PUSH_LEFT(Namespace, Container, Data) Namespace##_push_left((Container), (Data))

#define PEEK_LEFT(Namespace, Container) Namespace##_peek_left(Container)

#define POP_LEFT(Namespace, Container) Namespace##_pop_left(Container)

#define GET(Namespace, Container, Key) Namespace##_get((Container), (Key))

#define SET(Namespace, Container, Key, Value) Namespace##_set((Container), (Key), (Value))

#define CLEAR(Namespace, Container) Namespace##_clear(Container)

#define DESTROY(Namespace, Container) Namespace##_destroy(Container)

#define ITER_T(Namespace) struct Namespace##_iterator

#define BEGIN(Namespace, Container) Namespace##_begin(Container)

#define NEXT(Namespace, Iterator) Namespace##_next(Iterator)
