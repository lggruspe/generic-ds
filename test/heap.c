#include "heap.h"
#include "test_lib.h"
#include <string.h>

#define test_heap_setup() bool passed = false;\
int array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};\
struct heap heap = heap_create(array, 10, sizeof(int), test_heap_comparator)

#define test_heap_teardown() return passed

int test_heap_comparator(const void *p, const void *q)
{
    int a = *((int*)p);
    int b = *((int*)q);
    if (a < b) {
        return -1;
    } else if (a == b) {
        return 0;
    } else {
        return 1;
    }
}

bool test_heap_get_set()
{
    test_heap_setup();
    for (size_t i = 0; i < 10; ++i) {
        void *ptr = heap_get(&heap, i);
        check_assertion(ptr);
        if (!ptr) {
            continue;
        }
        check_assertion(test_heap_comparator(ptr, array + i));
    }
    int new_value = 11;
    heap_set(&heap, 0, &new_value);
    check_assertion(array[0] == new_value);
    test_heap_teardown();
}

bool test_heap_swap()
{
    test_heap_setup();
    for (size_t i = 0; i < heap.size/2; ++i) {
        heap_swap(&heap, i, 9 - i);
    }
    for (size_t i = 0; i < heap.size; ++i) {
        check_assertion(array[i] == i);
    }
    test_heap_teardown();
}

bool test_heap_heapify()
{
    test_heap_setup();
    array[0] = 0;
    heap_heapify(&heap);
    for (size_t i = 0; i < (heap.size-2)/2; ++i) {
        void *parent = heap_get(&heap, i);
        void *left = heap_get(&heap, 2*i + 1);
        void *right = heap_get(&heap, 2*i + 2);
        check_assertion(test_heap_comparator(parent, left) >= 0);
        check_assertion(test_heap_comparator(parent, right) >= 0);
    }
    test_heap_teardown();
}

void test_heap_sort(struct heap *heap)
{
    heap_heapify(heap);
    for (size_t i = heap->size - 1; i > 0; --i) {
        heap_swap(heap, 0, i);
        heap->size--;
        heap_sift_down(heap, 0);
    }
}

bool test_heap()
{
    test_heap_setup();
    test_heap_sort(&heap);
    for (size_t i = 0; i < 9; ++i) {
        check_assertion(array[i] <= array[i+1]);
    }
    test_heap_teardown();
}

int test_heap_string_comparator(const void *p, const void *q)
{
    return strcmp((const char*)p, (const char*)q);
}

bool test_heap_sort_strings()
{
    bool passed = false;
    const char *array[] = {"bc", "cde", "aa", "aaa", "aa"};
    struct heap heap = heap_create(array, 5, sizeof(const char*), test_heap_string_comparator);
    //test_heap_sort(&heap);

    heap_swap(&heap, 0, 1);
    heap_swap(&heap, 2, 3);
    heap_swap(&heap, 0, 4);
    heap_swap(&heap, 1, 3);

    for (size_t i = 1; i < 5; ++i) {
        int comparison = test_heap_string_comparator(array[i-1], array[i]);
        check_assertion(comparison <= 0);
    }
    return passed;
}

int main()
{
    run_test(test_heap_get_set, "test_heap_get_set");
    run_test(test_heap_swap, "test_heap_swap");
    run_test(test_heap_heapify, "test_heap_heapify");
    run_test(test_heap, "test_heap");
    run_test(test_heap_sort_strings, "test_heap_sort_strings");
    return exit_test();
}
