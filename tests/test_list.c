/**
 * @file test_list.c
 * @brief Tests for the linked list implementation.
 * @todo Add more tests.
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/ds/list.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests linked list creation, insertion, removal, and destruction.
 */
void test_list(void) {
    // Create a new empty linked list
    ds_list_t list = ds_list_create();

    // Verify that list creation succeeded
    ASSERT_TRUE(list != NULL && "ERROR: list creation failed!");

    // Verify that the new list is empty
    ASSERT_TRUE(ds_list_empty(list) && "ERROR: new list is not empty!");

    // Append two values to the list
    ASSERT_TRUE(ds_list_push_back(list, 1) && "ERROR: failed to append 1!");
    ASSERT_TRUE(ds_list_push_back(list, 2) && "ERROR: failed to append 2!");

    // Verify the number of elements
    ASSERT_TRUE(ds_list_size(list) == 2 && "ERROR: list size is not 2!");

    // Remove the first occurrence of value 1
    ASSERT_TRUE(ds_list_remove_first(list, 1) &&
                "ERROR: failed to remove the first occurrence of 1!");

    // Verify the updated list size
    ASSERT_TRUE(ds_list_size(list) == 1 && "ERROR: list size is not 1!");

    // Insert value 2 at the beginning of the list
    ASSERT_TRUE(ds_list_push_front(list, 2) &&
                "ERROR: failed to prepend 2!");

    // Remove the last occurrence of value 2
    ASSERT_TRUE(ds_list_remove_last(list, 2) &&
                "ERROR: failed to remove the last occurrence of 2!");

    // Initialize a variable to store the removed value
    int value = 0;

    // Remove the last element and verify its value
    ASSERT_TRUE(
        ds_list_pop_back(list, &value) && value == 2
        && "ERROR: pop_back returned an unexpected value!"
    );

    // Verify that the list is now empty
    ASSERT_TRUE(ds_list_empty(list) && "ERROR: list should be empty!");

    // Verify that removing from an empty list fails
    ASSERT_TRUE(!ds_list_pop_front(list, NULL) &&
                "ERROR: pop_front succeeded on an empty list!");

    // Destroy the list and release its memory
    ds_list_destroy(&list);

    // Verify that the list handle was reset to NULL
    ASSERT_TRUE(list == NULL && "ERROR: list was not destroyed!");

    // Display the test completion message
    fputs("func: void test_list(void) ended successfully ...\n", stdout);
}
