#include "heap_m.h"
#include "test_lib.h"
#include <stdbool.h>
#include <string.h>

typedef const char * string;
define_heap(string);


bool is_heap(struct heap(string) *heap)
{
    for (size_t i = 0; i < heap->size/2; ++i) {
        string parent = heap->array[heap_parent(i)];
        if (heap_left(i) >= heap->size) {
            break;
        }
        string left = heap->array[heap_left(i)];
        if (heap->comparator(parent, left) < 0) {
            return false;
        }
        if (heap_right(i) >= heap->size) {
            break;
        }
        string right = heap->array[heap_right(i)];
        if (heap->comparator(parent, right) < 0) {
            return false;
        }
    }
    return true;
}

bool is_sorted(struct heap(string) *heap)
{
    for (size_t i = 1; i < heap->size; ++i) {
        int comparison = heap->comparator(heap->array[i-1], heap->array[i]);
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

void heap_sort(struct heap(string) *heap)
{
    heap_heapify(heap);
    while (heap->size > 0) {
        heap_swap(heap, 0, heap->size - 1);
        heap->size--;
        heap_sift_down(heap, 0);
    }
}

bool test_heap_swap()
{
    bool passed = true;
    const char *array[] = {"a", "b"};
    struct heap(string) heap = heap_create(
            .array = array,
            .size = 2,
            .comparator = string_comparator);
    heap_swap(&heap, 0, 1);
    check_assertion(strcmp(array[0], "b") == 0);
    check_assertion(strcmp(array[1], "a") == 0);
    return passed;
}

bool test_heap_sift_up()
{
    bool passed = true;
    const char *array[] = {"a", "b"};
    struct heap(string) heap = heap_create(
            .array = array,
            .size = 2,
            .comparator = string_comparator);
    heap_sift_up(&heap, 1);
    check_assertion(strcmp(array[0], "b") == 0);
    check_assertion(strcmp(array[1], "a") == 0);
    return passed;
}

bool test_heap_sift_down()
{
    bool passed = true;
    const char *array[] = {"a", "b"};
    struct heap(string) heap = heap_create(
            .array = array,
            .size = 2,
            .comparator = string_comparator);
    heap_sift_down(&heap, 0);
    check_assertion(strcmp(array[0], "b") == 0);
    check_assertion(strcmp(array[1], "a") == 0);
    return passed;
}

bool test_heap_heapify()
{
    bool passed = true;
    const char *array[] = {"a", "b", "b", "c", "c", "c"};
    struct heap(string) heap = heap_create(
            .array=array, 
            .size=6,
            .comparator=string_comparator);
    heap_heapify(&heap);
    check_assertion(is_heap(&heap));
    return passed;
}
bool test_heap_sort()
{
    bool passed = true;
    const char *array[] = {"a", "b", "b", "c", "c", "c"};
    struct heap(string) heap = heap_create(
            .array=array, 
            .size=6,
            .comparator=string_comparator);
    heap_heapify(&heap);
    check_assertion(is_heap(&heap));
    heap_sort(&heap);
    check_assertion(is_sorted(&heap));
    return passed;
}

int main()
{
    run_test(test_heap_swap);
    run_test(test_heap_sift_up);
    run_test(test_heap_sift_down);
    run_test(test_heap_heapify);
    run_test(test_heap_sort);
    return exit_test();
}
