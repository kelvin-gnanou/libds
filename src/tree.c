/**
 * @file   : binary_tree.c
 * @brief  : This file defines the functions declared in binary_tree.h
 * @todo   : Add is empty fonction
 */

#include "../include/tree.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal struct */

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* Internal API */

/**
 * @brief Recursively destroys all nodes in a binary tree
 *
 * @param[in,out] node Root node of the subtree to destroy
 */
static void destroy_nodes(BinaryTree node);

/**
 * @brief Counts the number of nodes in a binary tree
 *
 * @param[in] node Root node of the subtree
 *
 * @return Number of nodes in the subtree
 */
static size_t node_count(const BinaryTree node);

/**
 * @brief Calculates the height of a binary tree
 *
 * @param[in] node Root node of the subtree
 *
 * @return Height of the subtree
 */
static size_t node_height(const BinaryTree node);

/**
 * @brief Prints the values of a binary tree using inorder traversal
 *
 * @param[in] node Root node of the subtree
 */
static void inorder(const BinaryTree node);

/* Lifecycle */

BinaryTree tree_create(void) {
    // Create an empty tree
    return NULL;
}

void tree_destroy(BinaryTree *root) {
    // Do nothing if the root pointer is NULL
    if (!root) return;

    // Destroy all nodes in the tree
    destroy_nodes(*root);

    // Reset the root pointer
    *root = NULL;
}

/* Internal helpers */

static void destroy_nodes(BinaryTree node) {
    // Do nothing if the node is NULL
    if (!node) return;

    // Destroy the left and right subtrees
    destroy_nodes(node->left);
    destroy_nodes(node->right);

    // Free the memory allocated for the current node
    free(node);
}

static size_t node_count(const BinaryTree node) {
    // Return 0 if the node is NULL
    if (!node) return 0;

    // Count the current node and its left and right subtrees
    return 1 + node_count(node->left) + node_count(node->right);
}

static size_t node_height(const BinaryTree node) {
    // Return 0 if the node is NULL
    if (!node) return 0;

    // Calculate the height of the left and right subtrees
    size_t left = node_height(node->left);
    size_t right = node_height(node->right);

    // Return 1 plus the maximum height of the subtrees
    return 1 + (left > right ? left : right);
}

/* Operations */

bool tree_insert(BinaryTree *root, int value) {
    // Do nothing if the root pointer is NULL
    if (!root) return false;

    // Find the appropriate position for the new value
    while (*root != NULL) {
        // Stop if the value already exists
        if (value == (*root)->value) return true;

        // Move to the left or right subtree depending on the value
        root = (value < (*root)->value)
            ? &(*root)->left
            : &(*root)->right;
    }

    // Allocate memory for the new node
    *root = malloc(sizeof(**root));

    // Stop if memory allocation fails
    if (!(*root)) return false;

    // Initialize the new node
    (*root)->value = value;
    (*root)->left = NULL;
    (*root)->right = NULL;

    return true;
}

bool tree_contains(const BinaryTree root, int value) {
    // Start searching from the root
    const struct TreeNode *node = root;

    // Search while the current node is not NULL
    while (node) {
        // Return true if the value is found
        if (value == node->value) return true;

        // Move to the left or right subtree depending on the value
        node = value < node->value
            ? node->left
            : node->right;
    }

    // Return false if the value is not found
    return false;
}

/* Traversal */

static void inorder(const BinaryTree node) {
    // Stop if the node is NULL
    if (!node) return;

    // Visit the left subtree
    inorder(node->left);

    // Visit the current node
    printf("%d ", node->value);

    // Visit the right subtree
    inorder(node->right);
}

/* Utilities */

size_t tree_size(const BinaryTree root) {
    // Return the total number of nodes in the tree
    return node_count(root);
}

size_t tree_height(const BinaryTree root) {
    // Return the height of the tree
    return node_height(root);
}

void tree_print_inorder(const BinaryTree root) {
    // Print the tree using inorder traversal
    inorder(root);

    // Print a newline after the traversal
    putchar('\n');
}
