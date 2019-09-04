#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct test_status {
    bool passed;
};

#define unit_test(fn, ...) void fn(struct test_status *status, ##__VA_ARGS__)

#define assert_true(condition) do {\
    if (!(condition)) {\
        printf(#condition " is false\n");\
        status->passed = false;\
    }\
} while (0)

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
    struct test_status status = { .passed = true };\
    test(&status, ##__VA_ARGS__);\
    if (!status.passed) {\
        printf(#test " failed\n");\
        ++total_failed;\
    }\
} while (0)

int exit_test()
{
    printf("Passed: %d out of %d\n", (total_tests - total_failed), total_tests);
    return total_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
