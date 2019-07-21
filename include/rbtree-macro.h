#pragma once
#include <stdlib.h>
#include <assert.h>

// TODO search_if
// rbtree (duplicates not allowed)

enum rbtree_color { rbtree_black=0, rbtree_color=1 };

#define rbtree_node_register_type(name, key_type, value_type) struct name {\
    key_type key;\
    value_type value;\
    struct name *left;\
    struct name *right;\
    struct name *parent;\
    rbtree_color color;\
}

#define rbtree_node_init(node, _key, _value, _left, _right, _parent, _color) do {\
    (node)->key = (_key);\
    (node)->value = (_value);\
    (node)->left = (_left);\
    (node)->right = (_right);\
    (node)->parent = (_parent);\
    (node)->color = (_color);\
} while (0)

// set tree.result to matching node
#define rbtree_search(tree, _key) do {\
    (tree)->result = (tree)->root;\
    while ((tree)->result && (tree)->result->key != (_key)) {\
        (tree)->result = (_key) < (tree)->result->key ? (tree)->result->left : (tree)->result->right;\
    }\
} while (0)

// same as rbtree_search but with a custom comparator for keys
#define rbtree_search_custom(tree, _key, compare) do {\
    (tree)->result = (tree)->root;\
    int comparison;\
    while ((tree)->result && (comparison = (compare)((_key), (tree)->result->key)) != 0) {\
        (tree)->result = (comparison < 0 ? (tree)->result->left : (tree)->result->right);\
    }\
} while (0)

#define rbtree_minimum(tree, node) do {\
    (tree)->result = (node);\
    if (node) {\
        while ((tree)->result->left) {\
            (tree)->result = (tree)->result->left;\
        }\
    }\
} while (0)

#define rbtree_successor(tree, node) do {\
    (tree)->result = (node);\
    if (node) {\
        if ((node)->right) {\
            rbtree_minimum((tree), (node)->right);\
        } else {\
            while ((tree)->result->parent && (tree)->result->parent->left != (tree)->result) {\
                (tree)->result = (tree)->result->parent;\
            }\
        }\
    }\
} while (0)

#define rbtree(node_type) struct {\
    node_type *root;\
    node_type *result;\
    size_t size;\
}

// comparator compares keys
#define rbtree_init(tree) do {\
    (tree)->root = NULL;\
    (tree)->result = NULL;\
    (tree)->size = 0;\
} while (0)

// x is a pointer to a node
#define rbtree_rotate_left(tree, x) do {\
    assert((x) && (x)->right);\
    (tree)->result = (x)->right;\
    (x)->right = (tree)->result->left;\
    if ((x)->right) {\
        (x)->right->parent = (x);\
    }\
    (tree)->result->parent = (x)->parent;\
    if ((tree)->result->parent) {\
        if ((tree)->result->parent->left == (x)) {\
            (tree)->result->parent->left = (tree)->result;\
        } else {\
            (tree)->result->parent->right = (tree)->result;\
        }\
    } else {\
        (tree)->root = (tree)->result;\
    }\
    (tree)->result->left = (x);\
    (x)->parent = (tree)->result;\
} while (0)

#define rbtree_rotate_right(tree, y) do {\
    assert((y) && (y)->left);\
    (tree)->result = (y)->left;\
    (y)->left = (tree)->result->right;\
    if ((y)->left) {\
        (y)->left->parent = (y);\
    }\
    (tree)->result->parent = (y)->parent;\
    if ((tree)->result->parent) {\
        if ((tree)->result->parent->right == (y)) {\
            (tree)->result->parent->right = (tree)->result;\
        } else {\
            (tree)->result->parent->left = (tree)->result;\
        }\
    } else {\
        (tree)->root = (tree)->result;\
    }\
    (tree)->result->right = (y);\
    (y)->parent = (tree)->result;\
} while (0)

// called when inserting a new node 
#define rbtree_repair(tree, node) do {\
    if (node) {\

    }\
} while (0)

// sets tree.result to parent of null node that node will replace
#define rbtree_match_or_parent(tree, node) do {\
    if ((tree)->root) {\
        (tree)->result = (tree)->root;\
        while ((tree)->result) {\
            if ((node)->key == (tree)->result->key) {\
                break;\
            } else if ((node)->key < (tree)->result->key) {\
                if (!((tree)->result->left)) {\
                    break;\
                }\
                (tree)->result = (tree)->result->left;\
            } else {\
                if (!((tree)->result->right)) {\
                    break;\
                }\
                (tree)->result = (tree)->result->right;\
            }\
        }\
    }\
} while (0)

// search with custom comparator
#define rbtree_match_or_parent_custom(tree, node, comparator) do {\
    if ((tree)->root) {\
        (tree)->result = (tree)->root;\
        while ((tree)->result) {\
            int comparison = (comparator)((node)->key, (tree)->result->key);\
            if (comparison == 0) {\
                break;\
            } else if (comparison < 0) {\
                if (!((tree)->result->left)) {\
                    break;\
                }\
                (tree)->result = (tree)->result->left;\
            } else {\
                if (!((tree)->result->right)) {\
                    break;\
                }\
                (tree)->result = (tree)->result->right;\
            }\
        }\
    }\
} while (0)

// u and v are pointers to nodes
#define rbtree_transplant(tree, u, v) do {\
    assert(u && v);\
    if (!((u)->parent)) {\
        (tree)->root = (v);\
    } else if ((u)->parent->left == (u)) {\
        (u)->parent->left = (v);\
    } else {\
        (u)->parent->right = (v);\
    }\
    (v)->parent = (u)->parent;\
} while (0)

// node is a pointer, shouldn't be null
// replaces matching node if it already exists
// sets children pointers of node to NULL
// and parent pointer to its new parent
// NOTE if there's already a match, the node to be replaced is stored
// in tree->result so it can be deallocayed by the user
#define rbtree_insert(tree, node) do {\
    if (node) {\
        (node)->left = NULL;\
        (node)->right = NULL;\
        if (!(tree)->root) {\
            (tree)->root = (node);\
            (tree)->root->parent = NULL;\
            (tree)->size++;\
            (tree)->result = NULL;\
        } else {\
            rbtree_match_or_parent((tree), (node));\
            (node)->parent = (tree)->result;\
            if ((node)->key == (tree)->result->key) {\
                (node)->left = (tree)->result->left;\
                (node)->right = (tree)->result->right;\
                if ((node)->left) {\
                    (node)->left->parent = (node);\
                }\
                if ((node)->right) {\
                    (node)->right->parent = (node);\
                }\
                rbtree_transplant((tree), (tree)->result, (node));\
            } else if ((node)->key < (tree)->result->key) {\
                (tree)->result->left = (node);\
                (tree)->size++;\
                (tree)->result = NULL;\
            } else {\
                (tree)->result->right = (node);\
                (tree)->size++;\
                (tree)->result = NULL;\
            }\
        }\
    } else {\
        (tree)->result = NULL;\
    }\
} while (0)

#define rbtree_insert_custom(tree, node, comparator) do {\
    if (node) {\
        (node)->left = NULL;\
        (node)->right = NULL;\
        if (!(tree)->root) {\
            (tree)->root = (node);\
            (tree)->root->parent = NULL;\
            (tree)->size++;\
            (tree)->result = NULL;\
        } else {\
            rbtree_match_or_parent((tree), (node));\
            (node)->parent = (tree)->result;\
            int comparison = (comparator)((node)->key, (tree)->result->key);\
            if (comparison == 0) {\
                (node)->left = (tree)->result->left;\
                (node)->right = (tree)->result->right;\
                if ((node)->left) {\
                    (node)->left->parent = (node);\
                }\
                if ((node)->right) {\
                    (node)->right->parent = (node);\
                }\
                rbtree_transplant((tree), (tree)->result, (node));\
            } else if (comparison < 0) {\
                (tree)->result->left = (node);\
                (tree)->size++;\
                (tree)->result = NULL;\
            } else {\
                (tree)->result->right = (node);\
                (tree)->size++;\
                (tree)->result = NULL;\
            }\
        }\
    } else {\
        (tree)->result = NULL;\
    }\
} while (0)

// TODO what if node isn't in the tree?
// NOTE doesn't preserve the red-black properties
// so this should only be used to destroy the tree
#define rbtree_delete(tree, node) do {\
    if (node) {\
        (tree)->size--;\
        if (!((node)->left) && !((node)->right)) {\
            if (!((node)->parent)) {\
                (tree)->root = NULL;\
            } else if ((node)->parent->left == (node)) {\
                (node)->parent->left = NULL;\
            } else {\
                (node)->parent->right = NULL;\
            }\
        } else if (!((node)->left) || !((node)->right)) {\
            rbtree_transplant((tree), (node), (node)->left ? (node)->left : (node)->right);\
        } else {\
            rbtree_successor((tree), (node));\
            if ((node)->right != (tree)->result) {\
                rbtree_transplant(tree, (tree)->result, (tree)->result->right);\
                (tree)->result->right = (node)->right;\
                (tree)->result->right->parent = (tree)->result;\
            }\
            (tree)->result->left = (node)->left;\
            (tree)->result->left->parent = (tree)->result;\
            rbtree_transplant(tree, (node), (tree)->result);\
        }\
    }\
} while (0)


// NOTE doesn't do anything if the red-black properties get violated
#define rbtree_update(tree, node, _key, _value) do {\
    if (node) {\
        (node)->key = (_key);\
        (node)->value = (_value);\
    }\
} while (0)
