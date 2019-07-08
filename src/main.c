#define stack_item_type char
#include "bst/bst.h"
#include "bst/bst_node.h"
#include "list/list.h"
#include "list/node.h"
#include "deque.h"
#include "heap.h"
#include "queue.h"
#include "red-black-tree/rbtree.h"
#define stack_item_type int
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int test_stack()
{
    int passed = 1;
    stack_item_type A[10];
    stack_t *stack = stack_init(10);
    for (int i = 0; i < 10; ++i) {
        stack_item_type item = rand() % 10;
        stack_push(stack, item);
        A[i] = item;
    }

    for (int i = 9; i >= 0; --i) {
        stack_item_type item = stack_pop(stack);
        if (item != A[i]) {
            passed = 0;
            goto cleanup;
        }
    }

cleanup:
    stack_destroy(stack);
    return passed;
}

int main()
{
    // see if program compiles
    int passed = test_stack();
    printf("test_stack: %d\n", passed);
}
