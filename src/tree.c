/**
 * @file tree.c
 * @brief Implements the public binary search tree interface declared in ds/tree.h
 * @todo Implement an emptiness check
 */

#include "../include/ds/tree.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structures */

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Tree {
    TreeNode *root; 
    size_t size;
} Tree;

/* Internal API */

/**
 * @brief Recursively frees all nodes in a binary tree.
 *
 * @param[in,out] node Root node of the subtree to clear.
 */
static void ds_tree_clear(TreeNode *node);

/**
 * @brief Calculates the height of a binary tree.
 *
 * @param[in] node Root node of the subtree to inspect.
 *
 * @return The height of the subtree.
 */
static size_t ds_tree_calculate_height(const TreeNode *node);

// /**
//  * @brief Prints the values of a binary tree using inorder traversal.
//  *
//  * @param[in] node Root node of the subtree to traverse.
//  */
// static void ds_tree_inorder(const TreeNode *node);

/* Lifecycle */

ds_tree_t ds_tree_create(void) {
    // Allocate and initialize an empty tree
    return calloc(1, sizeof(Tree));
}

void ds_tree_destroy(ds_tree_t *tree) {
    // Do nothing if the tree pointer or the tree itself is NULL
    if (!tree || !*tree) return;

    // Free all nodes in the tree
    ds_tree_clear((*tree)->root);

    // Free the tree structure
    free(*tree);
    *tree = NULL;
}

/* Internal helpers */

static void ds_tree_clear(TreeNode *node) {
    // Stop if the node is NULL
    if (!node) return;

    // Recursively clear the left and right subtrees
    ds_tree_clear(node->left);
    ds_tree_clear(node->right);

    // Free the current node
    free(node);
}

static size_t ds_tree_calculate_height(const TreeNode *node) {
    // Return 0 if the node is NULL
    if (!node) return 0;

    // Calculate the heights of the left and right subtrees
    size_t left = ds_tree_calculate_height(node->left);
    size_t right = ds_tree_calculate_height(node->right);

    // Return 1 plus the maximum height of the two subtrees
    return 1 + (left > right ? left : right);
}

/* Operations */

bool ds_tree_insert(ds_tree_t tree, int value) {
    // Reject a NULL tree
    if (!tree) return false;

    // Find the appropriate insertion position
    TreeNode **current = &tree->root;

    while (*current) {
        // Stop if the value already exists
        if (value == (*current)->value) return true;

        // Move to the left or right subtree based on the value
        current = value < (*current)->value
            ? &(*current)->left
            : &(*current)->right;
    }

    // Allocate memory for the new node
    TreeNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return false;

    // Initialize the new node
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    // Insert the new node
    *current = node;

    // Increment the tree size
    tree->size++;

    return true;
}

bool ds_tree_contain(const ds_tree_t tree, int value) {
    // Reject a NULL tree
    if (!tree) return false;

    // Start searching from the root
    const TreeNode *node = tree->root;

    // Continue searching while the current node is not NULL
    while (node) {
        // Return true if the value is found
        if (value == node->value) return true;

        // Move to the left or right subtree based on the value
        node = value < node->value
            ? node->left
            : node->right;
    }

    // Return false if the value is not found
    return false;
}

/* Traversal */

// static void ds_tree_inorder(const TreeNode *node) {
//     // Stop if the node is NULL
//     if (!node) return;

//     // Traverse the left subtree
//     ds_tree_inorder(node->left);

//     // Visit the current node
//     printf("%d ", node->value);

//     // Traverse the right subtree
//     ds_tree_inorder(node->right);
// }

/* Tree properties */

size_t ds_tree_size(const ds_tree_t tree) {
    // Return the number of nodes, or 0 if the tree is NULL
    return tree ? tree->size : 0;
}

size_t ds_tree_height(const ds_tree_t tree) {
    // Return the height of the tree, or 0 if the tree is NULL
    return tree ? ds_tree_calculate_height(tree->root) : 0;
}

/* Utilities */

// void ds_tree_print_inorder(const ds_tree_t tree) {
//     // Print the tree using inorder traversal
//     if (tree)
//         ds_tree_inorder(tree->root);
//
//     // Print a newline after the traversal
//     putchar('\n');
// }
