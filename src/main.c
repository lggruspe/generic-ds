#include "bst/bst.h"
#include "bst/bst_node.h"
#include "list/list.h"
#include "list/node.h"
#include "deque.h"
#include "heap.h"
//#include "queue.h"
#include "red-black-tree/tree.h"
#define stack_item_type int
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *((int*)a);
    int y = *((int*)b);
    if (x < y) {
        return -1;
    } else if (x == y) {
        return 0;
    } else {
        return 1;
    }
}

void print_node(rb_node_t *node)
{
    printf("key: %d\n", *((int*)(node->key)));
    printf("left: %d\n", (node->left ? *((int*)(node->left->key)) : -1));
    printf("right: %d\n", (node->right ? *((int*)(node->right->key)) : -1));
    printf("color: %c\n", node->color);
    printf("\n");
}

int test_rbtree()
{
    rb_tree_t *tree = rb_tree_create(sizeof(int), compare);
    for (int i = 0; i < 10; ++i) {
        rb_node_t *node = rb_node_create((void*)(&i), NULL, NULL, NULL, RB_RED, sizeof(i));
        rb_tree_insert(tree, node);
    }

    int passed = 1;
    char colors[10];    // expected
    for (int i = 0; i < 10; ++i) {
        colors[i] = RB_BLACK;
    }
    colors[7] = RB_RED;
    colors[9] = RB_RED;
    for (int i = 0; i < 10; ++i) {
        rb_node_t *node = rb_tree_search(tree, (void*)(&i));
        if (!node || node->color != colors[i]) {
            if (!node) {
                printf("null node\n");
            }
            passed = 0;
            goto cleanup;
        }
    }

cleanup:
    rb_tree_destroy(tree, 1);
    return passed;
}

int main()
{
    // see if program compiles
    int passed = test_rbtree();
    printf("test_rbtree: %d\n", passed);
}
