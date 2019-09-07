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
#include <stdbool.h>
#include <stdlib.h>

#define Namespace
#define Type

#define vector(Namespace) struct Namespace##_vector
#define vector_is_full(Namespace, vector) Namespace##_is_full(vector)
#define vector_is_empty(Namespace, vector) Namespace##_is_empty(vector)
#define vector_resize(Namespace, vector) Namespace##_resize(vector)
#define vector_peek(Namespace, vector) Namespace##_peek(vector)
#define vector_push(Namespace, vector, data) Namespace##_push((vector), (data))
#define vector_pop(Namespace, vector) Namespace##_pop(vector)
#define vector_create(Namespace, ...) (struct Namespace##_vector){ .growth_factor = 2.0, ##__VA_ARGS__ }
#define vector_destroy(Namespace, vector) Namespace##_destroy(vector)

#define vector_register(Namespace, Type) \
 \
struct Namespace##_vector { \
    Type *array; \
    int size; \
    int capacity; \
    double growth_factor; \
}; \
 \
vector(Namespace) Namespace##_resize(vector(Namespace) vector) \
{ \
    int capacity = vector.capacity * vector.growth_factor; \
    if (capacity <= 0) {\
        capacity = 1;\
    }\
    if (capacity <= vector.size) { \
        return vector; \
    } \
    Type *array = realloc(vector.array, capacity * sizeof(Type)); \
    if (!array) { \
        return vector; \
    } \
    vector.capacity = capacity; \
    vector.array = array; \
    return vector; \
} \
 \
bool Namespace##_is_empty(vector(Namespace) vector) \
{ \
    return vector.size <= 0; \
} \
 \
bool Namespace##_is_full(vector(Namespace) vector) \
{ \
    return vector.size >= vector.capacity; \
} \
 \
vector(Namespace) Namespace##_push(vector(Namespace) vector, Type data) \
{ \
    if (vector_is_full(Namespace, vector)) { \
        vector = vector_resize(Namespace, vector); \
    } \
    if (!vector_is_full(Namespace, vector)) { \
        vector.array[vector.size++] = data; \
    } \
    return vector; \
} \
 \
Type Namespace##_peek(vector(Namespace) vector) \
{ \
    return vector.array[vector.size - 1]; \
} \
 \
vector(Namespace) Namespace##_pop(vector(Namespace) vector) \
{ \
    if (!vector_is_empty(Namespace, vector)) { \
        vector.size--; \
    } \
    return vector; \
} \
 \
vector(Namespace) Namespace##_destroy(vector(Namespace) vector) \
{ \
    if (vector.array) { \
        free(vector.array); \
        vector.array = NULL; \
    } \
    vector.size = 0; \
    vector.capacity = 0; \
    return vector; \
}
