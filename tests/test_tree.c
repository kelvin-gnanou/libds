/**
 * @file : test_tree.c
 * @brief: Tests for the binary tree implementation
 * @todo : Add more tests
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/tree.h"

#define ASSERT_TRUE(x) assert(x)

void test_tree(void) {
    // Create a new empty binary search tree
    BinaryTree tree = tree_create();

    // Verify that the new tree is empty
    ASSERT_TRUE(tree_size(tree) == 0 &&
                "ERROR: new tree is not empty !");

    // Verify that the height of an empty tree is zero
    ASSERT_TRUE(tree_height(tree) == 0 &&
                "ERROR: new tree height is not 0 !");

    // Insert three distinct values into the tree
    ASSERT_TRUE(tree_insert(&tree, 5) && "ERROR: failed to insert 5 !");
    ASSERT_TRUE(tree_insert(&tree, 2) && "ERROR: failed to insert 2 !");
    ASSERT_TRUE(tree_insert(&tree, 8) && "ERROR: failed to insert 8 !");

    // Verify that inserting a duplicate value is handled successfully
    ASSERT_TRUE(tree_insert(&tree, 2) &&
                "ERROR: duplicate insert failed !");

    // Verify the number of distinct values
    ASSERT_TRUE(tree_size(tree) == 3 &&
                "ERROR: tree size is not 3 !");

    // Verify the height of the tree
    ASSERT_TRUE(tree_height(tree) == 2 &&
                "ERROR: tree height is not 2 !");

    // Verify that an existing value can be found
    ASSERT_TRUE(tree_contains(tree, 8) &&
                "ERROR: value 8 is missing !");

    // Verify that a non-existing value is not found
    ASSERT_TRUE(!tree_contains(tree, 7) &&
                "ERROR: value 7 should be missing !");

    // Destroy the tree and release its memory
    tree_destroy(&tree);

    // Verify that the tree pointer was reset to NULL
    ASSERT_TRUE(tree == NULL && "ERROR: tree was not destroyed !");

    // Display the test completion message
    fputs("func: void test_tree(void) ended successfully ...\n", stdout);
}
