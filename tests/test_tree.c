/**
 * @file test_tree.c
 * @brief Tests for the binary search tree implementation.
 * @todo Add more tests.
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/ds/tree.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests binary search tree creation, insertion, search, and destruction.
 */
void test_tree(void) {
    // Create a new empty binary search tree.
    ds_tree_t tree = ds_tree_create();

    // Verify that tree creation succeeded.
    ASSERT_TRUE(tree != NULL && "ERROR: tree creation failed!");

    // Verify that the new tree is empty.
    ASSERT_TRUE(ds_tree_size(tree) == 0 &&
                "ERROR: new tree is not empty!");

    // Verify that the height of an empty tree is zero.
    ASSERT_TRUE(ds_tree_height(tree) == 0 &&
                "ERROR: new tree height is not 0!");

    // Insert three distinct values into the tree.
    ASSERT_TRUE(ds_tree_insert(tree, 5) &&
                "ERROR: failed to insert 5!");
    ASSERT_TRUE(ds_tree_insert(tree, 2) &&
                "ERROR: failed to insert 2!");
    ASSERT_TRUE(ds_tree_insert(tree, 8) &&
                "ERROR: failed to insert 8!");

    // Verify that inserting a duplicate value is handled successfully.
    ASSERT_TRUE(ds_tree_insert(tree, 2) &&
                "ERROR: duplicate insertion failed!");

    // Verify the number of distinct values.
    ASSERT_TRUE(ds_tree_size(tree) == 3 &&
                "ERROR: tree size is not 3!");

    // Verify the height of the tree.
    ASSERT_TRUE(ds_tree_height(tree) == 2 &&
                "ERROR: tree height is not 2!");

    // Verify that an existing value can be found.
    ASSERT_TRUE(ds_tree_contain(tree, 8) &&
                "ERROR: value 8 was not found!");

    // Verify that a non-existing value is not found.
    ASSERT_TRUE(!ds_tree_contain(tree, 7) &&
                "ERROR: value 7 should not be found!");

    // Destroy the tree.
    ds_tree_destroy(&tree);

    // Verify that the tree pointer was reset to NULL.
    ASSERT_TRUE(tree == NULL && "ERROR: tree was not destroyed!");

    fputs("func: void test_tree(void) ended successfully ...\n", stdout);
}
