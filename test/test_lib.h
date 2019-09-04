#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define unit_test(fn, ...) bool fn(bool passed, ##__VA_ARGS__)
#define test_teardown() return passed

#define check_assertion(condition) do {\
    if (!(condition)) {\
        printf(#condition "\n");\
        passed = false;\
    }\
} while (0)

int total_tests = 0;
int total_failed = 0;

#define run_test(test) do {\
    ++total_tests;\
    if (!(test)()) {\
        printf(#test " failed\n");\
        ++total_failed;\
    }\
} while (0)

#define run_unit_test(test, ...) do {\
    ++total_tests;\
    if (!(test)(true, ##__VA_ARGS__)) {\
        printf(#test " failed\n");\
        ++total_failed;\
    }\
} while (0)

int exit_test()
{
    printf("Passed: %d out of %d\n", (total_tests - total_failed), total_tests);
    return total_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
