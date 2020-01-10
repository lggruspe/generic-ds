#pragma once

#define IS_EMPTY(Namespace, Container) Namespace##_is_empty(Container)

#define IS_FULL(Namespace, Container) Namespace##_is_full(Container)

#define RESIZE(Namespace, Container) Namespace##_resize(Container)

#define PUSH(Namespace, Container, Data) Namespace##_push((Container), (Data))

#define PEEK(Namespace, Container) Namespace##_peek(Container)

#define POP(Namespace, Container) Namespace##_pop(Container)

#define GET(Namespace, Container, Key) Namespace##_get((Container), (Key))

#define SET(Namespace, Container, Key, Value) Namespace##_set((Container), (Key), (Value))

#define CLEAR(Namespace, Container) Namespace##_clear(Container)

#define DESTROY(Namespace, Container) Namespace##_destroy(Container)

#define ITER_T(Namespace) struct Namespace##_iterator

#define BEGIN(Namespace, Container) Namespace##_begin(Container)

#define DONE(Namespace, Iterator) Namespace##_done(Iterator)

#define NEXT(Namespace, Iterator) Namespace##_next(Iterator)

#define VALUE(Namespace, Iterator) Namespace##_value(Iterator)