#ifndef DS_TREE_H
#define DS_TREE_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct Tree *ds_tree_t;

/* Lifecycle */

/**
 * @brief Creates a new empty binary search tree.
 *
 * @return A newly allocated tree, or NULL if memory allocation fails.
 */
ds_tree_t ds_tree_create(void);

/**
 * @brief Destroys a binary search tree and releases all allocated resources.
 *
 * @param[in,out] tree Address of the tree handle to destroy.
 *
 * @note Sets the tree handle to NULL after destruction.
 */
void ds_tree_destroy(ds_tree_t *tree);

/* Operations */

/**
 * @brief Inserts a new value into a binary search tree.
 *
 * @param[in,out] tree Tree to modify.
 * @param[in] value Value to insert.
 *
 * @return true if insertion succeeds; false if the tree is NULL or memory
 * allocation fails.
 *
 * @note Duplicate values are ignored.
 */
bool ds_tree_insert(ds_tree_t tree, int value);

/**
 * @brief Checks whether a value exists in a binary search tree.
 *
 * @param[in] tree Tree to search.
 * @param[in] value Value to search for.
 *
 * @return true if the value is found; false otherwise.
 */
bool ds_tree_contain(const ds_tree_t tree, int value);

/* Tree properties */

/**
 * @brief Returns the number of nodes in a binary search tree.
 *
 * @param[in] tree Tree to inspect.
 *
 * @return The number of nodes, or 0 if the tree is NULL.
 */
size_t ds_tree_size(const ds_tree_t tree);

/**
 * @brief Calculates the height of a binary search tree.
 *
 * @param[in] tree Tree to inspect.
 *
 * @return The height of the tree, or 0 if the tree is NULL or empty.
 */
size_t ds_tree_height(const ds_tree_t tree);

/* Traversal */

/*
Imposing terminal output on a generic library is discouraged. However, it is necessary for testing purposes. Therefore, I will create a dedicated `test_utils.h` for testing and later introduce an `example_utils.h` for demonstration purposes.
*/

// /**
//  * @brief Prints the values of a binary search tree using inorder traversal.
//  *
//  * @param[in] tree Tree to traverse.
//  */
// void ds_tree_print_inorder(const ds_tree_t tree);

#endif /* DS_TREE_H */
