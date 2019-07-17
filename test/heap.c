#include "heap.h"
#include "test_lib.h"
#include <string.h>


#define test_heap_setup(array, n, type, comparator) bool passed = true;\
struct heap heap = heap_create((array), (n), sizeof(type), (comparator))

#define test_heap_teardown() return passed

bool is_heap(struct heap *heap)
{
    for (size_t i = 0; i < heap->size/2; ++i) {
        void *parent = heap_get(heap, i);
        void *left = heap_get(heap, heap_left(i));
        void *right = heap_get(heap, heap_right(i));
        if (parent && left && right) {
            if (heap->comparator(parent, left) < 0 
                    || heap->comparator(parent, right) < 0) {
                return false;
            }
        }
    }
    return true;
}

bool is_heap_sorted(struct heap *heap)
{
    for (size_t i = 1; i < heap->size; ++i) {
        int comparison = heap->comparator(heap_get(heap, i-1), 
                heap_get(heap, i));
        if (comparison > 0) {
            return false;
        }
    }
    return true;
}

int string_comparator(const void *p, const void *q)
{
    return strcmp((const char*)p, (const char*)q);
}

void heap_sort(struct heap *heap)
{
    heap_heapify(heap);
    while (heap->size > 0) {
        heap_swap(heap, 0, heap->size - 1);
        heap->size--;
        heap_sift_down(heap, 0);
    }
}

bool test_heap_get()
{
    const char *array[] = {"hello"};
    test_heap_setup(array, 1, const char*, string_comparator);

    void *ptr = heap_get(&heap, 0);
    check_assertion(ptr && heap.comparator(ptr, array) == 0);
    check_assertion(!heap_get(&heap, 1));

    test_heap_teardown();
}

bool test_heap_set()
{
    const char *array[] = {"foo"};
    test_heap_setup(array, 1, const char*, string_comparator);

    const char *bar = "bar";
    heap_set(&heap, 0, &bar);

    void *ptr = heap_get(&heap, 0);
    check_assertion(ptr && heap.comparator(ptr, &bar) == 0);
    test_heap_teardown();
}

bool test_heap_swap()
{
    const char *array[] = {"foo", "bar"};
    test_heap_setup(array, 2, const char*, string_comparator);

    heap_swap(&heap, 0, 1);
    const char *foo = "foo";
    const char *bar = "bar";
    
    void *ptr = heap_get(&heap, 0);
    check_assertion(ptr && heap.comparator(ptr, &bar) == 0);
    ptr = heap_get(&heap, 1);
    check_assertion(ptr && heap.comparator(ptr, &foo) == 0);
    test_heap_teardown();
}

bool test_heap_heapify()
{
    const char *array[] = {"a", "b", "b", "c", "c", "c"};
    test_heap_setup(array, 6, const char*, string_comparator);
    heap_heapify(&heap);
    check_assertion(is_heap(&heap));
    test_heap_teardown();
}

bool test_heap_sort()
{
    const char *array[] = {"a", "b", "b", "c", "c", "c"};
    test_heap_setup(array, 6, const char*, string_comparator);
    heap_heapify(&heap);
    check_assertion(is_heap(&heap));
    heap_sort(&heap);
    check_assertion(is_heap_sorted(&heap));
    test_heap_teardown();
}

int main()
{
    run_test(test_heap_get);
    run_test(test_heap_set);
    run_test(test_heap_swap);
    run_test(test_heap_heapify);
    run_test(test_heap_sort);
    return exit_test();
}
