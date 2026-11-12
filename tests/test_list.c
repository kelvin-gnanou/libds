/**
 * @file : test_list.c
 * @brief: Tests for the linked list implementation
 * @todo : Add more test
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/list.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests linked list creation, insertion, removal and destruction
 */
void test_list(void) {
    // Create a new empty linked list
    list_t list = list_create();

    // Verify that list creation succeeded
    ASSERT_TRUE(list != NULL && "ERROR: list creation failed !");

    // Verify that the new list is empty
    ASSERT_TRUE(list_is_empty(list) && "ERROR: new list is not empty !");

    // Append two values to the list
    ASSERT_TRUE(list_push_back(list, 1) && "ERROR: failed to append 1 !");
    ASSERT_TRUE(list_push_back(list, 2) && "ERROR: failed to append 2 !");

    // Verify the number of elements
    ASSERT_TRUE(list_length(list) == 2 && "ERROR: list size is not 2 !");

    // Remove the first occurrence of value 1
    ASSERT_TRUE(list_remove_first(list, 1) &&
                "ERROR: failed to remove first 1 !");

    // Verify the updated list size
    ASSERT_TRUE(list_length(list) == 1 && "ERROR: list size is not 1 !");

    // Insert value 2 at the beginning of the list
    ASSERT_TRUE(list_push_front(list, 2) &&
                "ERROR: failed to prepend 2 !");

    // Remove the last occurrence of value 2
    ASSERT_TRUE(list_remove_last(list, 2) &&
                "ERROR: failed to remove last 2 !");

    // Initialize a variable to store the removed value
    int value = 0;

    // Remove the last element and verify its value
    ASSERT_TRUE(
        list_pop_back(list, &value) && value == 2
        && "ERROR: pop back returned a wrong value !"
    );

    // Verify that the list is now empty
    ASSERT_TRUE(list_is_empty(list) && "ERROR: list should be empty !");

    // Verify that removing from an empty list fails
    ASSERT_TRUE(!list_pop_front(list, NULL) &&
                "ERROR: pop from empty list succeeded !");

    // Destroy the list and release its memory
    list_destroy(&list);

    // Verify that the list pointer was reset to NULL
    ASSERT_TRUE(list == NULL && "ERROR: list was not destroyed !");

    // Display the test completion message
    fputs("func: void test_list(void) ended successfully ...\n", stdout);
}
