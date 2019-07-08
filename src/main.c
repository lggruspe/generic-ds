#include "bst/bst.h"
#include "bst/bst_node.h"
#include "list/list.h"
#include "list/node.h"
#include "deque.h"
#include "heap.h"
#include "queue.h"
#include "red-black-tree/tree.h"
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

int compare(const void *a, const void *b)
{
    return *((int*)a) < *((int*)b);
}

void print_node(rb_node_t *node)
{
    printf("key: %d\n", *((int*)(node->key)));
    printf("left: %d\n", (node->left ? *((int*)(node->left->key)) : -1));
    printf("right: %d\n", (node->right ? *((int*)(node->right->key)) : -1));
    printf("\n");
}

int test_rbtree()
{
    rb_tree_t *tree = rb_tree_create(sizeof(int), compare);
    for (int i = 0; i < 10; ++i) {
        rb_node_t *node = rb_node_create((void*)(&i), NULL, NULL, NULL, RB_RED, sizeof(i));
        rb_tree_insert(tree, node);
    }
    rb_node_inorder(tree->root, print_node);
    rb_tree_destroy(tree, 1);
    return 1;
}

int main()
{
    // see if program compiles
    int passed = test_rbtree();
    printf("test_rbtree: %d\n", passed);
}
