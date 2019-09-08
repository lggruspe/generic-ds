#include "bst.h"
#include "test_lib.h"
#include <stdlib.h>
#include <string.h>

typedef bst_node_register_type(map_node, const char *, int) map_node;

typedef bst(map_node) Map;

map_node *map_node_create(const char *key, int value)
{
    map_node *node = malloc(sizeof(map_node));
    if (node) {
        bst_node_init(node, key, value, NULL, NULL, NULL);
    }
    return node;
}

Map *map_create()
{
    Map *map= malloc(sizeof(Map));
    bst_init(map);
    return map;
}

int map_get(Map *map, const char *key, int def)
{
    bst_search_custom(map, key, strcmp); 
    map_node *node = map->result;
    return node ? node->value : def;
}

void map_set(Map *map, const char *key, int val)
{
    map_node *node = map_node_create(key, val);
    bst_insert_custom(map, node, strcmp);
    if (map->result) {
        free(map->result);
    }
}

void map_delete(Map *map, const char *key)
{
    bst_search_custom(map, key, strcmp);
    if (map->result) {
        bst_delete(map, map->result);;
        free(map->result);
    }
}

void map_destroy(Map *map)
{
    while (map->size > 1) {
        map_node *node = map->root;
        bst_delete(map, node);
        free(node);
    }
    if (map->size == 1) {
        map_node *node = map->root;
        bst_delete(map, node);
        free(node);
        map->root = NULL;
    }
    free(map);
}

unit_test(test_bst_init)
{
    Map *map = map_create();
    assert_true(!map->root);
    assert_true(!map->result);
    assert_true(map->size == 0);
    map_destroy(map);
}

unit_test(test_bst_get_set_delete)
{
    Map *map = map_create();
    assert_true(map_get(map, "a", -1) == -1);
    map_set(map, "a", 1);
    map_set(map, "b", 2);
    map_set(map, "c", 2);
    map_set(map, "c", 3);
    assert_true(map_get(map, "a", -1) == 1);
    assert_true(map_get(map, "b", -1) == 2);
    assert_true(map_get(map, "c", -1) == 3);

    map_delete(map, "a");
    assert_true(map_get(map, "a", -1) == -1);
    assert_true(map_get(map, "d", -1) == -1);
}

int main()
{
    run_unit_test(test_bst_init);
    run_unit_test(test_bst_get_set_delete);
    return exit_test();
}
