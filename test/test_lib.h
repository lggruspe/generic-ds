#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define unit_test(fn, ...) bool fn(bool passed, ##__VA_ARGS__)
#define test_teardown() return passed

#define check_assertion(condition) do {\
    if (!(condition)) {\
        passed = false;\
    }\
} while (0)

bool global_passed = true;

void fail_tests()
{
    global_passed = false;\
}

#define run_test(test) do {\
    if (!(test)()) {\
        printf(#test " failed\n");\
        fail_tests();\
    }\
} while (0)

#define run_unit_test(test, ...) do {\
    if (!(test)(true, ##__VA_ARGS__)) {\
        printf(#test " failed\n");\
        fail_tests();\
    }\
} while (0)

int exit_test()
{
    printf("passed: %s\n\n", global_passed ? "yes" : "no");
    return global_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
