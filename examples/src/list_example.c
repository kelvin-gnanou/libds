/**
 * @file list_example.c
 * @brief Demonstrates linked list operations
 */

#include "../include/examples.h"

#include <stdio.h>

/**
 * @brief Demonstrates linked list operations.
 */
void demo_list(void) {
    // Create an empty list
    ds_list_t list = ds_list_create();

    // Stop if memory allocation fails
    if (!list) {
        fprintf(stderr, "List allocation failed.\n");
        return;
    }

    // Insert values into the list
    ds_list_push_back(list, 4);
    ds_list_push_back(list, 9);
    ds_list_push_front(list, -2);

    // Print the list
    // ds_list_print(list);

    // Destroy the list
    ds_list_destroy(&list);
}
