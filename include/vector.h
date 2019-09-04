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

#define vector_growth_factor 2.0
#define vector_register(type) \
struct vector_##type {\
    int size;\
    int capacity;\
    type *array;\
};

#define vector_get(vec, i) ((vec)->array[i])

#define vector_set(vec, j, data) do {\
    if ((j) < (vec)->size) {\
        (vec)->array[(j)] = (data);\
    }\
} while (0)

#define vector_is_empty(vector) ((vector)->size == 0)
#define vector_is_full(vector) ((vector)->size == (vector)->capacity)
#define vector_create() { .array = NULL, .size = 0, .capacity = 0 }
#define vector_peek(vec) vector_get((vec), (vec)->size - 1)

#define vector_pop(vec) do {\
    if (!vector_is_empty(vec)) {\
        (vec)->size--;\
    }\
} while (0)

#define vector_push(vec, data) do {\
    if (vector_is_full(vec)) {\
        int capacity = (vec)->capacity * vector_growth_factor;\
        if (capacity <= 0) {\
            capacity = 1;\
        }\
        void *array = realloc((vec)->array, capacity * sizeof(data));\
        if (array) {\
            (vec)->array = array;\
            (vec)->capacity = capacity;\
        }\
    }\
    if (!vector_is_full(vec)) {\
        (vec)->size++;\
        vector_set((vec), (vec)->size - 1, (data));\
    }\
} while (0)

#define vector_get_pointer(vec, i) \
    ((i) >= (vec)->size) ? NULL : (vec)->array + (i)

#define vector_destroy(vector) do {\
    if ((vector)->array) {\
        free((vector)->array);\
    }\
    (vector)->array = NULL;\
    (vector)->size = 0;\
    (vector)->capacity = 0;\
} while (0)
