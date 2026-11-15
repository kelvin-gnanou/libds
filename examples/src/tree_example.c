/**
 * @file tree_example.c
 * @brief Demonstrates binary search tree operations
 */

#include "../include/examples.h"

#include <stdio.h>

/**
 * @brief Demonstrates binary search tree operations
 */
void demo_tree(void) {
    // Create an empty binary search tree
    ds_tree_t tree = ds_tree_create();

    // Stop if memory allocation fails
    if (!tree) {
        fprintf(stderr, "Tree allocation failed.\n");
        return;
    }

    // Define the values to insert into the tree
    const int values[] = {6, 9, 0, -4, 12};
    const size_t size = sizeof(values) / sizeof(values[0]);

    // Insert all values into the tree
    for (size_t i = 0; i < size; ++i) {
        if (!ds_tree_insert(tree, values[i])) {
            fprintf(stderr, "Failed to insert %d.\n", values[i]);
        }
    }

    // Print the tree using inorder traversal
    // printf("Inorder traversal: ");
    // ds_tree_print(tree);

    // Display the number of nodes and the tree height
    printf("Nodes: %zu | Height: %zu\n",
           ds_tree_size(tree),
           ds_tree_height(tree));

    // Destroy the tree
    ds_tree_destroy(&tree);
}
