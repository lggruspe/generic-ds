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

#define define_vector_type(_name, _type) struct _name {\
    size_t size;\
    size_t capacity;\
    _type *array;\
};\
\
int _name##_resize(struct _name *vec)\
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
int _name##_push(struct _name *vec, _type data)\
{\
    if (vector_is_full(vec)) {\
        _name##_resize(vec);\
    }\
    if (!vector_is_full(vec)) {\
        vec->array[vec->size++] = data;\
        return 0;\
    }\
    return -1;\
}\
\
_type _name##_peek(struct _name *vec)\
{\
    return vec->array[vec->size - 1];\
}\
\
_type _name##_pop(struct _name *vec)\
{\
    _type top;\
    if (!vector_is_empty(vec)) {\
        vec->size--;\
        top = vec->array[vec->size];\
    }\
    return top;\
}\
\
_type _name##_get(struct _name *vec, size_t i)\
{\
    return vec->array[i];\
}\
\
int _name##_set(struct _name *vec, size_t i, _type data)\
{\
    if (i >= vec->capacity) {\
        return -1;\
    }\
    vec->array[i] = data;\
    return 0;\
}\
\
_type *_name##_get_pointer(struct _name *vec, size_t i)\
{\
    if (i >= vec->capacity) {\
        return NULL;\
    }\
    return vec->array + i;\
}
