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
#include <stdlib.h>

#define vector(type) struct {\
    int size;\
    int capacity;\
    type *array;\
    double growth_factor;\
    type dummy;\
}

#define vector_get(vec, i) ((vec)->array[i])

#define vector_is_empty(vector) ((vector)->size == 0)
#define vector_is_full(vector) ((vector)->size >= (vector)->capacity)
#define vector_create(...) {.growth_factor = 2.0, ##__VA_ARGS__}
#define vector_peek(vec) vector_get((vec), (vec)->size - 1)

#define vector_pop(vec) do {\
    if (!vector_is_empty(vec)) {\
        (vec)->size--;\
    }\
} while (0)

#define vector_push(vec, data) do {\
    if (vector_is_full(vec)) {\
        int capacity = (vec)->capacity * (vec)->growth_factor;\
        if (capacity <= (vec)->size) {\
            capacity = (vec)->size + 1;\
        }\
        if (capacity <= 0) {\
            capacity = 1;\
        }\
        void *array = realloc((vec)->array, capacity * sizeof((vec)->dummy));\
        if (array) {\
            (vec)->array = array;\
            (vec)->capacity = capacity;\
        }\
    }\
    if (!vector_is_full(vec)) {\
        (vec)->size++;\
        vector_get((vec), (vec)->size - 1) = (data);\
    }\
} while (0)

#define vector_destroy(vector) do {\
    if ((vector)->array) {\
        free((vector)->array);\
        (vector)->array = NULL;\
    }\
    (vector)->size = 0;\
    (vector)->capacity = 0;\
} while (0)
