#include "vector.h"
#include "test_lib.h"
#include <math.h>
#include <string.h>

unit_test(test_vector)
{
    vector(int) vector = vector_create();
    assert_true(vector_is_empty(&vector));

    for (int i = 0; i < 10; ++i) {
        vector_push(&vector, i);
    }

    assert_true(!vector_is_empty(&vector));
    for (int i = 0; i < 10; ++i) {
        int j = vector_get(&vector, i);
        assert_true(i == j);
    }

    for (int i = 0; i < 10; ++i) {
        vector_get(&vector, i) = i*i;
        int *ptr = &(vector_get(&vector, i));
        *ptr += 1;
    }

    for (int i = 9; i >= 0; --i) {
        int top = vector_peek(&vector);
        vector_pop(&vector);
        assert_true(top == i*i + 1);
    }

    assert_true(vector_is_empty(&vector));
    vector_destroy(&vector);
}

unit_test(test_vector_push_peek_pop)
{
    vector(char) vector = vector_create();
    char array[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26; ++i) {
        vector_push(&vector, array[i]);
        assert_true(!vector_is_empty(&vector));
    }
    assert_true(vector.size == 26);

    for (int i = 25; !vector_is_empty(&vector); --i) {
        char *ptr = &(vector_get(&vector, i));
        char top = vector_peek(&vector);
        assert_true(ptr && *ptr == top);
        assert_true(top == array[i]);
        vector_pop(&vector);
    }
    vector_destroy(&vector);
}

unit_test(test_pointer_type)
{
    vector(const char*) vector = vector_create();
    vector_push(&vector, "!\n");
    vector_push(&vector, "world");
    vector_push(&vector, ", ");
    vector_push(&vector, "hello");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (int i = 0; i < 4; ++i) {
        const char *ptr = vector_peek(&vector);
        vector_pop(&vector);
        assert_true(ptr && strcmp(ptr, array[i]) == 0);
    }
    vector_destroy(&vector);
}

unit_test(test_vector_create)
{
    typedef vector(int) vector_int;
    vector_int vector = vector_create();
    assert_true(!vector.array);
    assert_true(vector.size == 0);
    assert_true(vector.capacity == 0);
    assert_true(vector.growth_factor == 2.0);
    assert_true(vector_is_empty(&vector));
    assert_true(vector_is_full(&vector));
    vector_destroy(&vector);
    assert_true(vector_is_full(&vector));
    assert_true(vector_is_empty(&vector));
    vector = (vector_int)vector_create(.growth_factor = 3.0);
    assert_true(vector.growth_factor == 3.0);
    vector_destroy(&vector);
}

int required_capacity(double growth_factor, int size)
{
    return (int)(pow(growth_factor, ceil(log(size)/log(growth_factor))));
}

unit_test(test_resize, double growth_factor)
{
    vector(int) vector = vector_create(.growth_factor = growth_factor);
    assert_true(vector.capacity == 0);

    int n = (int)(pow(growth_factor, 3));
    for (int i = 1; i <= n; ++i) {
            vector_push(&vector, i);
        assert_true(required_capacity(growth_factor, vector.size) == vector.capacity);
    }
    vector_destroy(&vector);
}

int main()
{
    run_unit_test(test_vector);
    run_unit_test(test_vector_create);
    run_unit_test(test_vector_push_peek_pop);
    run_unit_test(test_pointer_type);
    run_unit_test(test_resize, 1.0);
    run_unit_test(test_resize, 2.0);
    run_unit_test(test_resize, 3.0);
    return exit_test();
}
