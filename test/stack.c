#include "stack.h"
#include <stdbool.h>
#include <stdio.h>

#define check_assertion(condition) {\
    if (condition) {\
        passed = true;\
    }\
}

#define test_stack_setup(type) bool passed = false; stack(type) stack; stack_init(stack)

#define test_stack_teardown() stack_destroy(stack); return passed


bool global_passed = true;

bool test_stack_init()
{
    test_stack_setup(char);
    check_assertion(!stack.array);
    check_assertion(stack.size == 0);
    check_assertion(stack.capacity == 0);
    test_stack_teardown();
}

bool test_stack_increase_capacity()
{
    test_stack_setup(char);
    stack_increase_capacity(stack);
    check_assertion(stack.capacity == 1);
    for (size_t i = 0; i < 3; ++i) {
        stack_increase_capacity(stack);
    }
    check_assertion(stack.capacity == 8);
    test_stack_teardown();
}

bool test_stack_is_empty()
{
    test_stack_setup(char);
    check_assertion(stack_is_empty(stack));
    stack_push(stack, 0);
    check_assertion(!stack_is_empty(stack));
    stack_pop(stack);
    check_assertion(stack_is_empty(stack));
    test_stack_teardown();
}

bool test_stack_is_full()
{
    test_stack_setup(char);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 1);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 2);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 3);
    check_assertion(!stack_is_full(stack));
    stack_push(stack, 4);
    check_assertion(stack_is_full(stack));
    test_stack_teardown();
}

bool test_stack_push_peek_pop()
{
    test_stack_setup(char);
    char array[] = "0123456789";
    for (size_t i = 0; i < 10; ++i) {
        stack_push(stack, array[i]);
    }
    check_assertion(stack.size == 10);
    for (size_t i = 0; i < 10; ++i) {
        check_assertion(*(stack_peek(stack)) == array[9-i]);
        stack_pop(stack);
    }
    check_assertion(stack_is_empty(stack));
    void *ptr = stack_peek(stack);
    check_assertion(!ptr);
    test_stack_teardown();
}


void run_test(bool (*test)(void), const char *name)
{
    bool passed = test();
    printf("%s %s\n", name, passed ? "passed" : "failed");
    if (!passed) {
        global_passed = false;
    }
}

int main()
{
    run_test(test_stack_init, "test_stack_init");
    run_test(test_stack_increase_capacity, "test_stack_increase_capacity");
    run_test(test_stack_is_empty, "test_stack_is_empty");
    run_test(test_stack_is_full, "test_stack_is_full");
    run_test(test_stack_push_peek_pop, "test_stack_push_peek_pop");
    printf("passed: %d\n\n", global_passed);
    if (!global_passed) {
        return EXIT_FAILURE;
    }
}
