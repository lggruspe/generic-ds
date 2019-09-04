#include "vector.h"
#include "test_lib.h"
//#include <string.h>

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
        check_assertion(top == array[25 - i]);
        vector_pop(&vector);
    }
    check_assertion(!vector_get_pointer(&vector, 0));
    vector_destroy(&vector);
    test_teardown();
}

/*
unit_test(test_pointer_type)
{
    vector(string) vector = vector_create();
    vector_push(&vector, "!\n");
    vector_push(&vector, "world");
    vector_push(&vector, ", ");
    vector_push(&vector, "hello");

    const char *array[] = {"hello", ", ", "world", "!\n"};
    for (size_t i = 0; i < 4; ++i) {
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
    vector = vector_create(.growth_factor = 3.0);
    check_assertion(vector.growth_factor == 3.0);
    vector_destroy(&vector);
    test_teardown();
}

unit_test(test_resize)
{
    vector(int) vector = vector_create();
    check_assertion(vector.capacity == 0);
    for (int i = 0; i < 5; ++i) {
        vector_push(&vector, i);
    }
    check_assertion(vector.capacity == 8);
    vector_destroy(&vector);
    test_teardown();
}
*/

int main()
{
    run_unit_test(test_vector);
    //run_unit_test(test_vector_create);
    //run_unit_test(test_vector_push_peek_pop);
    //run_unit_test(test_pointer_type);
    //run_unit_test(test_resize);
    return exit_test();
}
