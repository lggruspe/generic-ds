#include "vector.h"
#include "test_lib.h"
#include <math.h>
#include <string.h>

vector_register(vi, int)
vector_register(vc, char)
vector_register(vs, const char *)

unit_test(test_vector)
{
    vector(vi) vector = vector_create(vi);
    assert_true(vector_is_empty(vi, vector));

    for (int i = 0; i < 10; ++i) {
        vector = vector_push(vi, vector, i);
    }

    assert_true(!vector_is_empty(vi, vector));

    for (int i = 0; i < 10; ++i) {
        assert_true(vector_get(vi, vector, i) == i);
    }

    for (int i = 0; i < 10; ++i) {
        vector = vector_set(vi, vector, i, i*i);
    }

    for (int i = 9; i >= 0; --i) {
        int top = vector_peek(vi, vector);
        vector = vector_pop(vi, vector);
        assert_true(top == i*i);
    }

    assert_true(vector_is_empty(vi, vector));
    vector_destroy(vi, vector);
}

unit_test(test_vector_push_peek_pop)
{
    vector(vc) vector = vector_create(vc);
    assert_true(vector_is_empty(vc, vector));

    char array[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26; ++i) {
        vector = vector_push(vc, vector, array[i]);
    }
    assert_true(vector.size == 26);

    for (int i = 25; !vector_is_empty(vc, vector); --i) {
        char top = vector_peek(vc, vector);
        assert_true(top == array[i]);
        vector = vector_pop(vc, vector);
    }
    vector_destroy(vc, vector);
}

unit_test(test_pointer_type)
{
    vector(vs) vector = vector_create(vs);
    vector = vector_push(vs, vector, "!\n");
    vector = vector_push(vs, vector, "world");
    vector = vector_push(vs, vector, ", ");
    vector = vector_push(vs, vector, "hello");

    const char *array[] = { "hello", ", ", "world", "!\n" };
    for (int i = 0; i < 4; ++i) {
        const char *top = vector_peek(vs, vector);
        assert_true(top && strcmp(top, array[i]) == 0);
        vector = vector_pop(vs, vector);
    }
    vector_destroy(vs, vector);
}

unit_test(test_vector_create)
{
    vector(vi) vector = vector_create(vi);
    assert_true(!vector.array);
    assert_true(vector.size == 0);
    assert_true(vector.capacity == 0);
    assert_true(vector.growth_factor == 2.0);
    assert_true(vector_is_full(vi, vector));
    assert_true(vector_is_empty(vi, vector));
    vector_destroy(vi, vector);

    assert_true(vector_is_full(vi, vector));
    assert_true(vector_is_empty(vi, vector));

    vector = vector_create(vi, .growth_factor = 3.0);
    assert_true(vector.growth_factor == 3.0);
    vector_destroy(vi, vector);
}

int required_capacity(double growth_factor, int size)
{
    return (int)(pow(growth_factor, ceil(log(size)/log(growth_factor))));
}

unit_test(test_resize, double growth_factor)
{
    vector(vi) vector = vector_create(vi, .growth_factor = growth_factor);
    assert_true(vector.capacity == 0);

    int n = (int)(pow(growth_factor, 3));
    for (int i = 1; i <= n; ++i) {
        vector = vector_push(vi, vector, i);
        assert_true(required_capacity(growth_factor, vector.size) == vector.capacity);
    }
    vector_destroy(vi, vector);
}

unit_test(test_vector_get_set)
{
    vector(vi) vector = vector_create(vi);
    for (int i = 0; i < 10; ++i) {
        vector = vector_push(vi, vector, i);
    }
    for (int i = 0; i < 10; ++i) {
        vector = vector_set(vi, vector, i, i*i+1);
    }
    for (int i = 0; i < 10; ++i) {
        assert_true(vector_get(vi, vector, i) == i*i + 1);
    }
    vector_destroy(vi, vector);
}

int main()
{
    run_unit_test(test_vector);
    run_unit_test(test_vector_push_peek_pop);
    run_unit_test(test_pointer_type);
    run_unit_test(test_vector_create);
    for (int i = 1; i <= 3; ++i) {
        run_unit_test(test_resize, (double)i);
    }
    run_unit_test(test_vector_get_set);
    return exit_test();
}
