#include "vector.h"
#include "test_lib.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef const char* string;
vector_register(int)
vector_register(char)
vector_register(string)

unit_test(test_vector)
{
    vector(int) vector = vector_create();
    check_assertion(vector_is_empty(&vector));

    for (int i = 0; i < 10; ++i) {
        vector_push(&vector, i);
    }

    check_assertion(!vector_is_empty(&vector));
    for (int i = 0; i < 10; ++i) {
        int j = vector_get(&vector, i);
        check_assertion(i == j);
    }

    for (int i = 0; i < 10; ++i) {
        vector_set(&vector, i, i*i);
        int *ptr = vector_get_pointer(&vector, i);
        *ptr += 1;
    }

    for (int i = 9; i >= 0; --i) {
        int top = vector_peek(&vector);
        vector_pop(&vector);
        check_assertion(top == i*i + 1);
    }

    check_assertion(vector_is_empty(&vector));
    vector_destroy(&vector);
    test_teardown();
}

unit_test(test_vector_push_peek_pop)
{
    vector(char) vector = vector_create();
    char array[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26; ++i) {
        vector_push(&vector, array[i]);
        check_assertion(!vector_is_empty(&vector));
    }
    check_assertion(vector.size == 26);

    for (int i = 25; !vector_is_empty(&vector); --i) {
        char *ptr = vector_get_pointer(&vector, i);
        char top = vector_peek(&vector);
        check_assertion(ptr && *ptr == top);
        check_assertion(top == array[i]);
        vector_pop(&vector);
    }
    check_assertion(!vector_get_pointer(&vector, 0));
    vector_destroy(&vector);
    test_teardown();
}

unit_test(test_pointer_type)
{
    vector(string) vector = vector_create();
    vector_push(&vector, "!\n");
    vector_push(&vector, "world");
    vector_push(&vector, ", ");
    vector_push(&vector, "hello");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (int i = 0; i < 4; ++i) {
        const char *ptr = vector_peek(&vector);
        vector_pop(&vector);
        check_assertion(ptr);
        if (ptr) {
            check_assertion(strcmp(ptr, array[i]) == 0);
        }
    }
    vector_destroy(&vector);
    test_teardown();
}

unit_test(test_vector_create)
{
    vector(int) vector = vector_create();
    check_assertion(!vector.array);
    check_assertion(vector.size == 0);
    check_assertion(vector.capacity == 0);
    check_assertion(vector.growth_factor == 2.0);
    check_assertion(vector_is_empty(&vector));
    check_assertion(vector_is_full(&vector));
    vector_destroy(&vector);
    check_assertion(vector_is_full(&vector));
    check_assertion(vector_is_empty(&vector));
    vector = (vector(int))vector_create(.growth_factor = 3.0);
    check_assertion(vector.growth_factor == 3.0);
    vector_destroy(&vector);
    test_teardown();
}

int required_capacity(double growth_factor, int size)
{
    return (int)(pow(growth_factor, ceil(log(size)/log(growth_factor))));
}

unit_test(test_resize, double growth_factor)
{
    vector(int) vector = vector_create(.growth_factor = growth_factor);
    check_assertion(vector.capacity == 0);

    int n = (int)(pow(growth_factor, 3));
    for (int i = 1; i <= n; ++i) {
        printf("size: %d, capacity: %d, required: %d\n",
                vector.size,
                vector.capacity,
                required_capacity(growth_factor,vector.size));
        vector_push(&vector, i);
        check_assertion(required_capacity(growth_factor, vector.size) == vector.capacity);
    }
    vector_destroy(&vector);

    printf("\n");
    printf("\n");
    test_teardown();
}

int main()
{
    run_unit_test(test_vector);
    run_unit_test(test_vector_create);
    run_unit_test(test_vector_push_peek_pop);
    run_unit_test(test_pointer_type);
    run_unit_test(test_resize, 1.0);
    run_unit_test(test_resize, 1.5);
    run_unit_test(test_resize, 2.0);
    run_unit_test(test_resize, 3.0);
    return exit_test();
}
