#pragma once
#include <stdlib.h>
#include <assert.h>

// bst (duplicates not allowed)

#define bst_node_register_type(name, key_type, value_type) struct name {\
    key_type key;\
    value_type value;\
    struct name *left;\
    struct name *right;\
    struct name *parent;\
}

#define bst_node_init(node, _key, _value, _left, _right, _parent) do {\
    (node)->key = (_key);\
    (node)->value = (_value);\
    (node)->left = (_left);\
    (node)->right = (_right);\
    (node)->parent = (_parent);\
} while (0)

// set tree.result to matching node
#define bst_search(tree, _key) do {\
    (tree)->result = (tree)->root;\
    while ((tree)->result && (tree)->result->key != (_key)) {\
        (tree)->result = (_key) < (tree)->result->key ? (tree)->result->left : (tree)->result->right;\
    }\
} while (0)

// same as bst_search but with a custom comparator for keys
#define bst_search_custom(tree, _key, compare) do {\
    (tree)->result = (tree)->root;\
    int comparison;\
    while ((tree)->result && (comparison = (compare)((_key), (tree)->result->key)) != 0) {\
        (tree)->result = (comparison < 0 ? (tree)->result->left : (tree)->result->right);\
    }\
} while (0)


#define bst_node_minimum(result, root) do {\
    assert(root);\
    result = (root);\
    while (result->left) {\
        result = result->left;\
    }\
} while (0)

// node shouldn't be null
#define bst_node_successor(result, node) do {\
    assert(node);\
    result = NULL;\
    if ((node)->right) {\
        bst_node_minimum(result, (node)->right);\
    } else {\
        result = (node);\
        while (result->parent && result->parent->left != result) {\
            result = result->parent;\
        }\
    }\
} while (0)

#define bst(node_type) struct {\
    node_type *root;\
    node_type *result;\
    size_t size;\
}

// comparator compares keys
#define bst_init(tree) do {\
    (tree)->root = NULL;\
    (tree)->result = NULL;\
    (tree)->size = 0;\
} while (0)

// sets tree.result to parent of null node that node will replace
// assumes tree.root is not null
#define bst_match_or_parent(tree, node) do {\
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
#define bst_match_or_parent_custom(tree, node, comparator) do {\
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
// neither should be null
#define bst_transplant(tree, u, v) do {\
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
#define bst_insert(tree, node) do {\
    if (node) {\
        (node)->left = NULL;\
        (node)->right = NULL;\
        if (!(tree)->root) {\
            (tree)->root = (node);\
            (tree)->root->parent = NULL;\
            (tree)->size++;\
            (tree)->result = NULL;\
        } else {\
            bst_match_or_parent((tree), (node));\
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
                bst_transplant((tree), (tree)->result, (node));\
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

#define bst_insert_custom(tree, node, comparator) do {\
    if (node) {\
        (node)->left = NULL;\
        (node)->right = NULL;\
        if (!(tree)->root) {\
            (tree)->root = (node);\
            (tree)->root->parent = NULL;\
            (tree)->size++;\
            (tree)->result = NULL;\
        } else {\
            bst_match_or_parent((tree), (node));\
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
                bst_transplant((tree), (tree)->result, (node));\
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
#define bst_delete(tree, node) do {\
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
            bst_transplant((tree), (node), (node)->left ? (node)->left : (node)->right);\
        } else {\
            bst_node_successor((tree)->result, (node));\
            if ((node)->right != (tree)->result) {\
                bst_transplant(tree, (tree)->result, (tree)->result->right);\
                (tree)->result->right = (node)->right;\
                (tree)->result->right->parent = (tree)->result;\
            }\
            (tree)->result->left = (node)->left;\
            (tree)->result->left->parent = (tree)->result;\
            bst_transplant(tree, (node), (tree)->result);\
        }\
    }\
} while (0)
