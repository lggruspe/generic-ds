#include "vector.h"
#include "test_lib.h"

vector_register(int)

bool test_vector()
{
    bool passed = true;
    struct vector_int vector = vector_create();
    check_assertion(vector_is_empty(&vector));

    for (int i = 0; i < 10; ++i) {
        vector_int_push(&vector, i);
    }

    check_assertion(!vector_is_empty(&vector));
    for (int i = 0; i < 10; ++i) {
        int j = vector_int_get(&vector, i);
        check_assertion(i == j);
    }

    for (int i = 0; i < 10; ++i) {
        vector_int_set(&vector, i, i*i);
        int *ptr = vector_int_get_pointer(&vector, i);
        *ptr += 1;
    }

    for (int i = 9; i >= 0; --i) {
        int top = vector_int_peek(&vector);
        int x = vector_int_pop(&vector);
        check_assertion(x == top);
        check_assertion(x == i*i + 1);
    }

    check_assertion(vector_is_empty(&vector));
    vector_destroy(&vector);
    return passed;
}

int main()
{
    run_test(test_vector);
    return exit_test();
}
