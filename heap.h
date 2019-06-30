#pragma once
#define HEAP_PARENT(i)  (((i) - 1)/2)
#define HEAP_LEFT(i)    (2*(i) + 1)
#define HEAP_RIGHT(i)   (HEAP_LEFT(i) + 1)

void heap_swap(int A[], size_t i, size_t j)
{
    int a = A[i];
    A[i] = A[j];
    A[j] = a;
}

void heap_max_sift_up(int A[], size_t i)
{
    int a = A[i];
    while (i > 0 && a > A[HEAP_PARENT(i)]) {
        A[i] = A[HEAP_PARENT(i)];
        i = HEAP_PARENT(i);
    }
    A[i] = a;
}

void heap_max_sift_down(int A[], size_t n, size_t i)
{
    for (;;) {
        int l = HEAP_LEFT(i);
        int r = HEAP_RIGHT(i);
        int p = i;
        p = (l < n && A[p] < A[l] ? l : p);
        p = (r < n && A[p] < A[r] ? r : p);
        if (i != p) {
            heap_swap(A, i, p);
            i = p;
        } else {
            break;
        }
    }
}

void heap_max_heapify(int A[], size_t n)
{
    for (size_t i = (n - 1)/2; i >= 0; --i) {
        heap_max_sift_down(A, n, i);
    }
}

void heap_min_sift_up(int A[], size_t i)
{
    int a = A[i];
    while (i > 0 && a < A[HEAP_PARENT(i)]) {
        A[i] = A[HEAP_PARENT(i)];
        i = HEAP_PARENT(i);
    }
    A[i] = a;
}

void heap_min_sift_down(int A[], size_t n, size_t i)
{
    for (;;) {
        int l = HEAP_LEFT(i);
        int r = HEAP_RIGHT(i);
        int p = i;
        p = (l < n && A[p] > A[l] ? l : p);
        p = (r < n && A[p] > A[r] ? r : p);
        if (i != p) {
            heap_swap(A, i, p);
            i = p;
        } else {
            break;
        }
    }
}

void heap_min_heapify(int A[], size_t n)
{
    for (size_t i = (n - 1)/2; i >= 0; --i) {
        heap_min_sift_down(A, n, i);
    }
}
