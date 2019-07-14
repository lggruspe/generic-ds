#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define check_assertion(condition) do {\
    if (condition) {\
        passed = true;\
    }\
} while (0)

bool global_passed = true;

void run_test(bool (*test)(void), const char *name)
{
    bool passed = test();
    printf("%s %s\n", name, passed ? "passed" : "failed");
    if (!passed) {
        global_passed = false;
    }
}

int exit_test()
{
    printf("passed: %s\n\n", global_passed ? "yes" : "no");
    return global_passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
