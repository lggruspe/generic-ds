#include "vector.h"
#include "test_lib.h"

define_vector_type(Vector, int);

bool test_vector()
{
    bool passed = true;
    struct Vector vector = vector_create();
    check_assertion(vector_is_empty(&vector));

    for (int i = 0; i < 10; ++i) {
        Vector_push(&vector, i);
    }

    check_assertion(!vector_is_empty(&vector));
    for (int i = 0; i < 10; ++i) {
        int j = Vector_get(&vector, i);
        check_assertion(i == j);
    }

    for (int i = 0; i < 10; ++i) {
        Vector_set(&vector, i, i*i);
        int *ptr = Vector_get_pointer(&vector, i);
        *ptr += 1;
    }

    for (int i = 9; i >= 0; --i) {
        int top = Vector_peek(&vector);
        int x = Vector_pop(&vector);
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
