#include "heap.h"
#include "test_lib.h"
#include <string.h>

heap_register(hi, int)
heap_register(hs, const char *)

unit_test(test_heap_static)
{
    const char *array[] = {"1", "0", "2", "9", "3", "8", "4", "7", "5", "6"};
    heap(hs) heap = heap_heapify_compare(hs, array, 10, strcmp);
    assert_true(heap_is_heap(hs, heap));
    heap = heap_sort(hs, heap);
    assert_true(heap_is_empty(hs, heap));
    assert_true(heap_is_heap(hs, heap));
    for (int i = 1; i < 10; ++i) {
        assert_true(strcmp(array[i-1], array[i]) < 0);
    }
    heap_destroy(hs, heap);
}

unit_test(test_heap_hs_dynamic)
{
    const char *array[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    heap(hs) heap = heap_create(hs, .compare = strcmp);
    for (int i = 0; i < 10; ++i) {
        heap = heap_push(hs, heap, array[i]);
    }

    assert_true(heap_is_heap(hs, heap));

    for (int i = 9; i >= 0; --i) {
        const char *max = heap_peek(hs, heap);
        heap = heap_pop(hs, heap);
        assert_true(max && strcmp(max, array[i]) == 0);
    }
    assert_true(heap_is_empty(hs, heap));
    heap_destroy(hs, heap);
}

unit_test(test_heap_dynamic)
{
    heap(hi) heap = heap_create(hi);
    for (int i = 0; i < 10; ++i) {
        heap = heap_push(hi, heap, i);
    }
    assert_true(heap_is_heap(hi, heap));
    for (int i = 9; i >= 0; --i) {
        int max = heap_peek(hi, heap);
        heap = heap_pop(hi, heap);
        assert_true(max == i);
    }
    assert_true(heap_is_empty(hi, heap));
    heap_destroy(hi, heap);
}

int main()
{
    run_unit_test(test_heap_static);
    run_unit_test(test_heap_hs_dynamic);
    run_unit_test(test_heap_dynamic);
    return exit_test();
}
