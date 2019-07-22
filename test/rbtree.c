#include "rbtree.h"
#include "test_lib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct map_string_int_data {
    const char *key;
    int value;
};

struct map_string_int {
    struct rb_tree *tree;
};

struct map_string_int_data map_string_int_data_create(
        const char *key, 
        int value)
{
    return (struct map_string_int_data) {
        .key = key,
        .value = value
    };
}

struct map_string_int map_string_int_create()
{
    return (struct map_string_int) {
        .tree = NULL
    };
}

int map_compare(const void *x, const void *y)
{
    return strcmp(
            ((struct map_string_int_data*)x)->key, 
            ((struct map_string_int_data*)y)->key);
}

void map_string_int_set(
        struct map_string_int *map,
        const char *key, 
        int value)
{
    struct map_string_int_data data = map_string_int_data_create(key, value);
    struct rb_tree *node = rb_tree_create(&data, NULL, NULL, NULL, rb_red, sizeof(struct map_string_int_data));
    struct rb_insert_result result = rb_insert(map->tree, node, map_compare);
    if (result.replaced) {
        rb_destroy(result.replaced, false, true); 
    }
    map->tree = result.root;
}

int map_string_int_get(struct map_string_int *map, const char *key, int def)
{
    struct map_string_int_data data = map_string_int_data_create(key, 0);
    struct rb_tree *node = rb_search(map->tree, &data, map_compare);
    return node ? ((struct map_string_int_data*)node->data)->value : def;
}

void map_destroy(struct map_string_int *map)
{
    rb_destroy(map->tree, true, true);
}

size_t tree_weight(struct rb_tree *tree)
{
    if (!tree) return 0;
    return 1 + tree_weight(tree->left) + tree_weight(tree->right);
}

bool test_rbtree_get_set()
{
    bool passed = true;
    struct map_string_int map = map_string_int_create();
    check_assertion(map_string_int_get(&map, "a", -1) == -1);
    map_string_int_set(&map, "a", 1);
    map_string_int_set(&map, "b", 2);
    map_string_int_set(&map, "c", 2);
    map_string_int_set(&map, "c", 3);
    check_assertion(map_string_int_get(&map, "a", -1) == 1);
    check_assertion(map_string_int_get(&map, "b", -1) == 2);
    check_assertion(map_string_int_get(&map, "c", -1) == 3);
    check_assertion(tree_weight(map.tree) == 3);
    map_destroy(&map);
    return passed;
}

size_t tree_height(struct rb_tree *tree)
{
    if (!tree) return 0;
    size_t left = tree_height(tree->left);
    size_t right = tree_height(tree->right);
    return 1 + (left > right ? left : right);
}

bool is_balanced(struct rb_tree *tree)
{
    size_t weight = tree_weight(tree);
    size_t height = tree_height(tree);
    return height <= 2*log2(weight + 1); 
}

// returns -1 if not well-defined
int black_height(struct rb_tree *node)
{
    if (!node) return 0;
    int left = black_height(node->left);
    if (left == -1) return -1;
    int right = black_height(node->right);
    if (right == -1 || left != right) return -1;
    return node->color == rb_black ? 1 + left : left;
}

// check if each path doesn't have consecutive red nodes
bool is_majority_black(struct rb_tree *node)
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

bool is_red_black(struct rb_tree *root)
{
    return !root || (
            root->color == rb_black 
            && black_height(root) != -1
            && is_majority_black(root));
}

int int_compare(const void *x, const void *y)
{
    return *((int*)x) - *((int*)y);
}

struct set_int {
    struct rb_tree *tree;
};

struct set_int set_int_create()
{
    return (struct set_int) {
        .tree = NULL
    };
}

void set_insert(struct set_int *set, int key)
{
    struct rb_tree *node = rb_tree_create(&key, NULL, NULL, NULL, rb_red, sizeof(int));
    struct rb_insert_result result = rb_insert(set->tree, node, int_compare);
    if (result.replaced) {
        rb_destroy(result.replaced, false, true);
    }
    set->tree = result.root;
}

bool set_contains(struct set_int *set, int key)
{
    struct rb_tree *node = rb_search(set->tree, &key, int_compare);
    return node && int_compare(node->data, &key) == 0;
}

bool is_binary_tree(
        struct rb_tree *tree, 
        int (*compare)(const void*, const void*))
{
    assert(compare);
    if (!tree) return true;
    if (tree->left && compare(tree->left->data, tree->data) > 0) {
        return false;
    }
    bool left = is_binary_tree(tree->left, compare);
    if (!left) return false;
    if (tree->right && compare(tree->data, tree->right->data) > 0) {
        return false;
    }
    bool right = is_binary_tree(tree->right, compare);
    if (!right) return false;
    return true;
}

// check if inserting keys in increasing order still produces a
// red-black tree
bool test_rbtree_redblack()
{
    bool passed = true;
    struct set_int set = set_int_create();

    size_t n = 100;
    int array[n];
    for (size_t i = 0; i < n; ++i) {
        array[i] = (int)0;
    }
    for (size_t i = 0; i < n; ++i) {
        set_insert(&set, array[i]);
    }
    for (size_t i = 0; i < n; ++i) {
        check_assertion(set_contains(&set, array[i]));
    }

    check_assertion(is_binary_tree(set.tree, int_compare));
    check_assertion(is_balanced(set.tree));
    check_assertion(is_red_black(set.tree));
    rb_destroy(set.tree, true, true);
    return passed;
}

int main()
{
    run_test(test_rbtree_get_set);
    run_test(test_rbtree_redblack);
    return exit_test();
}
