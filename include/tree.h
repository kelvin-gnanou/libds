#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct TreeNode *BinaryTree;

/* Lifecycle */

/**
 * @brief Creates a new empty binary tree
 *
 * @return A pointer to the root node, or NULL if allocation fails
 */
BinaryTree tree_create(void);

/**
 * @brief Destroys a binary tree and releases all allocated memory
 *
 * @param[in,out] root Pointer to the root node
 *
 * @note Sets the root pointer to NULL after destruction
 */
void tree_destroy(BinaryTree *root);

/* Traversal */

/**
 * @brief Inserts a new value into a binary search tree
 *
 * @param[in,out] root Pointer to the root node
 * @param[in] value Value to insert
 *
 * @return true if insertion succeeds, false otherwise
 *
 * @note Duplicate values are not inserted
 */
bool tree_insert(BinaryTree *root, int value);

/**
 * @brief Checks whether a value exists in a binary search tree
 *
 * @param[in] root Root node of the tree
 * @param[in] value Value to search for
 *
 * @return true if the value is found, false otherwise
 */
bool tree_contains(const BinaryTree root, int value);

/**
 * @brief Gets the number of nodes in a binary tree
 *
 * @param[in] root Root node of the tree
 *
 * @return Number of nodes in the tree
 */
size_t tree_size(const BinaryTree root);

/**
 * @brief Gets the height of a binary tree
 *
 * @param[in] root Root node of the tree
 *
 * @return Height of the tree, or 0 if the tree is empty
 */
size_t tree_height(const BinaryTree root);

/**
 * @brief Prints the values of a binary tree in inorder traversal
 *
 * @param[in] root Root node of the tree
 */
void tree_print_inorder(const BinaryTree root);

#endif /* DATA_STRUCTURES_BINARY_TREE_H */
