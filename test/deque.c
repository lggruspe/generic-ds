#include "deque.h"
#include "test_lib.h"
#include <math.h>
#include <string.h>

deque_register(qi, int)
deque_register(qc, char)
deque_register(qs, const char *)

unit_test(test_deque_init)
{
    deque(qi) deque = deque_create(qi);
    assert_true(!deque.array);
    assert_true(deque_is_empty(qi, deque));
    assert_true(deque_is_full(qi, deque));
    assert_true(!deque.array);
    assert_true(deque.size == 0);
    assert_true(deque.capacity == 0);
    assert_true(deque.front == 0);
    assert_true(deque.back == 0);
    deque_destroy(qi, deque);
}

unit_test(test_deque_is_empty)
{
    deque(qc) deque = deque_create(qc);
    assert_true(deque_is_empty(qc, deque));

    deque = deque_push(qc, deque, 0);
    assert_true(!deque_is_empty(qc, deque));
    deque = deque_pop(qc, deque);
    assert_true(deque_is_empty(qc, deque));

    deque = deque_push_front(qc, deque, 0);
    assert_true(!deque_is_empty(qc, deque));
    deque = deque_pop_front(qc, deque);
    assert_true(deque_is_empty(qc, deque));

    deque = deque_push(qc, deque, 0);
    assert_true(!deque_is_empty(qc, deque));
    deque = deque_pop_front(qc, deque);
    assert_true(deque_is_empty(qc, deque));

    deque = deque_push_front(qc, deque, 0);
    assert_true(!deque_is_empty(qc, deque));
    deque = deque_pop(qc, deque);
    assert_true(deque_is_empty(qc, deque));

    deque_destroy(qc, deque);
    assert_true(deque_is_empty(qc, deque));
}

int required_capacity(double growth_factor, int size)
{
    return (int)(pow(growth_factor, ceil(log(size)/log(growth_factor))));
}

unit_test(test_deque_capacity, double growth_factor)
{
    deque(qi) deque = deque_create(qi, .growth_factor = growth_factor);
    assert_true(deque.capacity == 0);

    int n = (int)(pow(growth_factor, 3)); 
    for (int i = 1; i <= n; ++i) {
        deque = deque_push(qi, deque, i);
        assert_true(required_capacity(growth_factor, deque.size) == deque.capacity);
    }
    deque_destroy(qi, deque);
}

unit_test(test_deque_push_pop)
{
    deque(qi) deque = deque_create(qi);
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            deque = deque_push_front(qi, deque, 0);
        } else {
            deque = deque_push(qi, deque, 1);
        }
    }

    for (int i = 0; i < 5; ++i) {
        int front = deque_peek_front(qi, deque);
        int back = deque_peek(qi, deque);
        deque = deque_pop(qi, deque);
        deque = deque_pop_front(qi, deque);
        assert_true(front == 0 && back == 1);
    }
    deque_destroy(qi, deque);
}

unit_test(test_deque_destroy)
{
    deque(qi) deque = deque_create(qi);
    for (int i = 0; i < 10; ++i) {
        deque = deque_push(qi, deque, i);
    }
    deque = deque_destroy(qi, deque);
    assert_true(!deque.array);
    assert_true(deque.size == 0);
    assert_true(deque.capacity == 0);
    assert_true(deque.front == 0);
    assert_true(deque.back == 0);
}

unit_test(test_deque_pointer_type)
{
    deque(qs) deque = deque_create(qs);
    deque = deque_push(qs, deque, "hello");
    deque = deque_push(qs, deque, ", ");
    deque = deque_push(qs, deque, "world");
    deque = deque_push(qs, deque, "!\n");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (int i = 0; i < 4; ++i) {
        assert_true(strcmp(array[i], deque.array[i]) == 0);
    }

    for (int i = 0; i < 4; ++i) {
        assert_true(strcmp(deque_peek_front(qs, deque), array[i]) == 0);
        deque = deque_pop_front(qs, deque);
    }
    deque_destroy(qs, deque);
}

unit_test(test_deque_get)
{
    deque(qi) deque = deque_create(qi);
    for (int i = 0; i < 10; ++i) {
        deque = deque_push(qi, deque, 0);
    }
    for (int i = 0; i < 10; ++i) {
        DEQUE_GET(qi, deque, i) = i;
    }
    for (int i = 0; i < 10; ++i) {
        assert_true(DEQUE_GET(qi, deque, i) == i);
    }
    deque_destroy(qi, deque);
}

int main()
{
    run_unit_test(test_deque_init);
    run_unit_test(test_deque_is_empty);
    for (int i = 1; i <= 3; ++i) {
        run_unit_test(test_deque_capacity, i);
    }
    run_unit_test(test_deque_push_pop);
    run_unit_test(test_deque_destroy);
    run_unit_test(test_deque_pointer_type);
    run_unit_test(test_deque_get);
    return exit_test();
}
