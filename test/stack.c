#include "stack.h"
#include <stdbool.h>
#define check_assertion(condition) {\
    if (!(condition)) {\
        passed = false;\
    }\
}

#include <stdio.h>

bool global_passed = true;

bool test_stack_init()
{
    bool passed = true;
    stack(char) stack;
    stack_init(stack);
    check_assertion(!stack.array);
    check_assertion(stack.size == 0);
    check_assertion(stack.capacity == 0);
    stack_destroy(stack);
    return passed;
}

bool test_stack_increase_capacity()
{
    bool passed = true;
    stack(char) stack;
    stack_init(stack);
    stack_increase_capacity(stack);
    check_assertion(stack.size == 1);
    for (size_t i = 0; i < 3; ++i) {
        stack_increase_capacity(stack);
    }
    check_assertion(stack.size == 8);
    stack_destroy(stack);
    return passed;
}

bool test_stack_is_empty()
{
    bool passed = true;
    stack(char) stack;
    stack_init(stack);
    check_assertion(stack_is_empty(stack));
    stack_push(stack, 0);
    check_assertion(!stack_is_empty(stack));
    stack_pop(stack);
    check_assertion(stack_is_empty(stack));
    stack_destroy(stack);
    return passed;
}

bool test_stack_is_full()
{
    bool passed = true;
    stack(char) stack;
    stack_init(stack);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 1);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 2);
    check_assertion(stack_is_full(stack));
    stack_push(stack, 3);
    check_assertion(!stack_is_full(stack));
    stack_push(stack, 4);
    check_assertion(stack_is_full(stack));
    stack_destroy(stack);
    return passed;
}

bool test_stack_push_peek_pop()
{
    bool passed = true;
    stack(char) stack;
    stack_init(stack);
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
    stack_destroy(stack);
    return passed;
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
    printf("passed: %d\n", global_passed);
    if (!global_passed) {
        return EXIT_FAILURE;
    }
}
