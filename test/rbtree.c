#include "rbtree.h"
#include "test_lib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct map_data {
    const char *key;
    int value;
}; 

struct map_data map_data_create(const char *key, int value)
{
    return (struct map_data) {
        .key = key,
        .value = value
    };
}

int map_compare(const void *x, const void *y)
{
    return strcmp(((struct map_data*)x)->key, ((struct map_data*)y)->key);
}

struct rb_tree map_create()
{
    return rb_tree_create(sizeof(struct map_data*), map_compare);
}

void map_set(struct rb_tree *map, const char *key, int value)
{
    struct map_data data = map_data_create(key, value);
    struct rb_node *node = rb_node_create(&data, NULL, NULL, NULL,  rb_red, sizeof(struct map_data));
    rb_node_destroy(rb_tree_insert(map, node), false);
}

int map_get(struct rb_tree *map, const char *key, int def)
{
    struct map_data data = map_data_create(key, 0);
    struct rb_node *node = rb_tree_search(map, &data);
    return node ? ((struct map_data*)node->data)->value : def;
}

void map_destroy(struct rb_tree *map)
{
    rb_tree_destroy(map, true); 
}

// untested change data, delete, inorder, preoder, successor

bool test_rbtree_init()
{
    bool passed = true;
    struct rb_tree map = map_create();
    check_assertion(!map.root);
    return passed;
}

size_t tree_weight_helper(struct rb_node *node)
{
    if (!node) return 0;
    return tree_weight_helper(node->left) + tree_weight_helper(node->right) + 1;
}

size_t tree_weight(struct rb_tree *tree)
{
    return tree_weight_helper(tree->root);
}

bool test_rbtree_get_set()
{
    bool passed = true;
    struct rb_tree map = map_create();
    check_assertion(map_get(&map, "a", -1) == -1);
    map_set(&map, "a", 1);
    map_set(&map, "b", 2);
    map_set(&map, "c", 2);
    map_set(&map, "c", 3);
    check_assertion(map_get(&map, "a", -1) == 1);
    check_assertion(map_get(&map, "b", -1) == 2);
    check_assertion(map_get(&map, "c", -1) == 3);
    check_assertion(tree_weight(&map) == 3);
    map_destroy(&map);
    return passed;
}

size_t tree_height_helper(struct rb_node *node)
{
    if (!node) return 0;
    size_t left = tree_height_helper(node->left);
    size_t right = tree_height_helper(node->right);
    return 1 + (left > right ? left : right);
}

size_t tree_height(struct rb_tree *tree)
{
    return tree_height_helper(tree->root);
}

bool is_balanced(struct rb_tree *tree)
{
    size_t weight = tree_weight(tree);
    size_t height = tree_height(tree);
    // expected height < 2lg(n+1)
    return height <= 2*log2(weight + 1); 
}

// returns -1 if not well-defined
int black_height(struct rb_node *node)
{
    if (!node) return 0;
    int left = black_height(node->left);
    if (left == -1) return -1;
    int right = black_height(node->right);
    if (right == -1 || left != right) return -1;
    return node->color == rb_black ? 1 + left : left;
}

// check if each path doesn't have consecutive red nodes
bool is_majority_black(struct rb_node *node)
{
    if (!node) return true;
    bool left = is_majority_black(node->left);
    if (!left) return false;
    bool right = is_majority_black(node->right);
    if (!right) return false;
    if (node->color == rb_red) {
        if (node->left && node->left->color == rb_red) return false;
        if (node->right && node->right->color == rb_red) return false;
    }
    return true;
}

bool is_red_black(struct rb_tree *tree)
{
    if (!tree->root) return true;
    if (tree->root->color == rb_red) return false;
    if (black_height(tree->root) == -1) return false;
    return is_majority_black(tree->root);
}

int int_compare(const void *x, const void *y)
{
    return *((int*)x) - *((int*)y);
}

void int_set(struct rb_tree *tree, int key)
{
    struct rb_node *node = rb_node_create(&key, NULL, NULL, NULL, rb_red, sizeof(int));
    rb_node_destroy(rb_tree_insert(tree, node), false);
}

bool int_contains(struct rb_tree *tree, int key)
{
    struct rb_node *node = rb_tree_search(tree, &key);
    return node && tree->comparator(node->data, &key) == 0;
}

bool is_binary_tree_helper(
        struct rb_node *node, 
        int (*compare)(const void *, const void *))
{
    if (!node) return true;
    if (node->left && compare(node->left->data, node->data) > 0) {
        return false;
    }
    bool left = is_binary_tree_helper(node->left, compare);
    if (!left) return false;
    if (node->right && compare(node->data, node->right->data) > 0) {
        return false;
    }
    bool right = is_binary_tree_helper(node->right, compare);
    if (!right) return false;
    return true;
}

bool is_binary_tree(struct rb_tree *tree)
{
    return is_binary_tree_helper(tree->root, tree->comparator);
}

// check if inserting keys in increasing order still produces a
// red-black tree
bool test_rbtree_redblack()
{
    bool passed = true;
    struct rb_tree map = rb_tree_create(sizeof(int), int_compare);

    size_t n = 100;
    int array[n];
    for (size_t i = 0; i < n; ++i) {
        array[i] = (int)0;
    }
    for (size_t i = 0; i < n; ++i) {
        int_set(&map, array[i]);
    }
    for (size_t i = 0; i < n; ++i) {
        check_assertion(int_contains(&map, array[i]));
    }

    check_assertion(is_binary_tree(&map));
    check_assertion(is_balanced(&map));
    check_assertion(is_red_black(&map));
    rb_tree_destroy(&map, true);
    return passed;
}

int main()
{
    run_test(test_rbtree_init);
    run_test(test_rbtree_get_set);
    run_test(test_rbtree_redblack);
    return exit_test();
}
