// MIT License
// 
// Copyright (c) 2019 Levi Gruspe
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <stddef.h>
#include <stdlib.h>

#define vector_is_empty(vector) ((vector)->size == 0)
#define vector_is_full(vector) ((vector)->size == (vector)->capacity)
#define vector_create() {\
    .size = 0,\
    .capacity = 0,\
    .array = NULL\
}

#define vector_destroy(vector) do {\
    free((vector)->array);\
    (vector)->array = NULL;\
    (vector)->size = 0;\
    (vector)->capacity = 0;\
} while (0)

#define vector_register(_type) \
struct vector_##_type {\
    size_t size;\
    size_t capacity;\
    _type *array;\
};\
\
int vector_##_type##_resize(struct vector_##_type *vec)\
{\
    size_t capacity = vec->capacity ? 2*vec->capacity : 1;\
    _type *array = realloc(vec->array, capacity * sizeof(_type));\
    if (array) {\
        vec->array = array;\
        vec->capacity = capacity;\
        return 0;\
    }\
    return -1;\
}\
\
int vector_##_type##_push(struct vector_##_type *vec, _type data)\
{\
    if (vector_is_full(vec)) {\
        vector_##_type##_resize(vec);\
    }\
    if (!vector_is_full(vec)) {\
        vec->array[vec->size++] = data;\
        return 0;\
    }\
    return -1;\
}\
\
_type vector_##_type##_peek(struct vector_##_type *vec)\
{\
    return vec->array[vec->size - 1];\
}\
\
_type vector_##_type##_pop(struct vector_##_type *vec)\
{\
    _type top = vector_##_type##_peek(vec);\
    if (!vector_is_empty(vec)) {\
        vec->size--;\
    }\
    return top;\
}\
\
_type vector_##_type##_get(struct vector_##_type *vec, size_t i)\
{\
    return vec->array[i];\
}\
\
int vector_##_type##_set(struct vector_##_type *vec, size_t i, _type data)\
{\
    if (i >= vec->capacity) {\
        return -1;\
    }\
    vec->array[i] = data;\
    return 0;\
}\
\
_type *vector_##_type##_get_pointer(struct vector_##_type *vec, size_t i)\
{\
    if (i >= vec->capacity) {\
        return NULL;\
    }\
    return vec->array + i;\
}
