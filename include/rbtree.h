#pragma once
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum rb_color { rb_black=0, rb_red=1 } rb_color;

struct rb_tree {
    void *data;
    struct rb_tree *left, *right, *parent;
    enum rb_color color;
};

struct rb_tree *rb_tree_create(
        const void *data,
        struct rb_tree *left, 
        struct rb_tree *right, 
        struct rb_tree *parent, 
        enum rb_color color,
        size_t nbytes)  // sizeof(data)
{
    struct rb_tree *tree = (struct rb_tree*)malloc(sizeof(struct rb_tree));
    if (tree) {
        tree->data = malloc(nbytes);
        if (tree->data) {
            tree->left = left;
            tree->right = right;
            tree->parent = parent;
            tree->color = color;
            memcpy(tree->data, data, nbytes);
        } else {
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}

// returns (possibly) new root of tree
struct rb_tree *rb_rotate_left(struct rb_tree *root, struct rb_tree *x)
{
    assert(x && x->right);
    struct rb_tree *y = x->right;
    y->parent = x->parent;
    if (y->parent) {
        if (y->parent->left == x) {
            y->parent->left = y;
        } else {
            y->parent->right = y;
        }
    } else {
        root = y;
    }

    x->right = y->left;
    if (x->right) {
        x->right->parent = x;
    }

    y->left = x;
    x->parent = y;
    return root;
}

struct rb_tree *rb_rotate_right(struct rb_tree *root, struct rb_tree *y)
{
    assert(y && y->left);
    struct rb_tree *x = y->left;
    x->parent = y->parent;
    if (x->parent) {
        if (x->parent->left == y) {
            x->parent->left = x;
        } else {
            x->parent->right = x;
        }
    } else {
        root = x;
    }

    y->left = x->right;
    if (y->left) {
        y->left->parent = y;
    }

    x->right = y;
    y->parent = x;
    return root;
}

void rb_destroy(struct rb_tree *node, bool cascade_, bool free_)
{
    if (!node) return;
    if (cascade_) {
        rb_destroy(node->left, cascade_, free_);
        rb_destroy(node->right, cascade_, free_);
    }
    free(node->data);
    if (free_) free(node);
}

struct rb_tree *rb_closest_match(
        struct rb_tree *root,
        const void *data,
        int (*compare)(const void *, const void *))
{
    struct rb_tree *parent = NULL;
    struct rb_tree *child = root;
    int comparison;
    while (child && (comparison = compare(data, child->data)) != 0) {
        parent = child;
        child = comparison < 0 ? child->left : child->right;
    }
    return child ? child : parent;
}

struct rb_tree *rb_search(
        struct rb_tree *root, 
        const void *data,
        int (*compare)(const void *, const void *))
{
    struct rb_tree *node = root;
    int comparison;
    while (node && (comparison = compare(data, node->data)) != 0) {
        node = comparison < 0 ? node->left : node->right;
    }
    return node;
}

struct rb_tree *rb_transplant(
        struct rb_tree *root, 
        struct rb_tree *u, 
        struct rb_tree *v)
{
    if (!u->parent) {
        root = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
    return root;
}

struct rb_tree *rb_repair(struct rb_tree *root, struct rb_tree *node)
{
    if (!root || !node) return root;
    struct rb_tree *parent = node->parent;
    struct rb_tree *grandparent = (parent ? parent->parent : NULL);
    struct rb_tree *uncle = NULL;
    if (grandparent) {
        uncle = (grandparent->left == parent 
            ? grandparent->right 
            : grandparent->left);
    }

    // case 1: red uncle
    if (uncle && uncle->color == rb_red) {
        if (grandparent) {
            grandparent->color = rb_red;
            uncle->color = rb_black;
            parent->color = rb_black;
            return rb_repair(root, grandparent);
        }
    }
    // case 2: black uncle, triangle
    if (grandparent && grandparent->left == parent && parent->right == node) {
        root = rb_rotate_left(root, parent);
    } else if (grandparent && grandparent->right == parent && parent->left == node) {
        root = rb_rotate_right(root, parent);
    }

    // case 3: black uncle, line
    if (grandparent && grandparent->left == parent && parent->left == node) {
        grandparent->color = rb_red;
        parent->color = rb_black;
        root = rb_rotate_right(root, grandparent);
    } else if (grandparent && grandparent->right == parent && parent->right == node) {
        grandparent->color = rb_red;
        parent->color = rb_black;
        root = rb_rotate_left(root, grandparent);
    }
    root->color = rb_black;
    return root;
}

struct rb_insert_result {
    struct rb_tree *root;
    struct rb_tree *replaced;
};

// returns node that the child replaces, if any, 
// so the caller can deallocate memory (using rb_destroy(node, false))
struct rb_insert_result rb_insert(
        struct rb_tree *root, 
        struct rb_tree *node,
        int (*compare)(const void *, const void *))
{
    struct rb_insert_result result = {
        .root = root,
        .replaced = NULL
    };
    if (!node) return result;

    node->color = rb_red;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    if (!root) {
        node->color = rb_black;
        result.root = node;
        return result;
    }

    struct rb_tree *closest = rb_closest_match(root, node->data, compare);
    int comparison = compare(node->data, closest->data);
    if (comparison == 0) {
        result.replaced = closest;
        node->color = closest->color;
        node->left = closest->left;
        node->right = closest->right;
        root = rb_transplant(root, closest, node);
    } else if (comparison < 0) {
        closest->left = node;
        node->parent = closest;
    } else {
        closest->right = node;
        node->parent = closest;
    }
    root = rb_repair(root, node);
    result.root = root;
    return result;
}

// NOTE doesnt check if new tree preserves BST property
void rb_node_change_data(struct rb_tree *node, const void *data, size_t nbytes)
{
    if (node) {
        if (!node->data) {
            node->data = malloc(nbytes);
        }
        if (node->data) {
            memcpy(node->data, data, nbytes);
        }
    }
}

void rb_inorder(const struct rb_tree *node, void (*handler)(const void*))
{
    if (node) {
        rb_inorder(node->left, handler);
        handler(node->data);
        rb_inorder(node->right, handler);
    }
}

void rb_preorder(const struct rb_tree *node, void (*handler)(const void*))
{
    if (node) {
        handler(node->data);
        rb_preorder(node->left, handler);
        rb_preorder(node->right, handler);
    }
}

void rb_postorder(const struct rb_tree *node, void (*handler)(const void*))
{
    if (node) {
        rb_postorder(node->left, handler);
        rb_postorder(node->right, handler);
        handler(node->data);
    }
}
