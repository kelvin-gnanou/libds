/**
 * @file : test_stack.c
 * @brief: Tests for the stack implementation
 * @todo : Add more tests
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/stack.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests stack creation, insertion, removal and destruction
 */
void test_stack(void) {
    // Create a new empty stack
    stack_t stack = stack_create();

    // Verify that stack creation succeeded
    ASSERT_TRUE(stack != NULL && "ERROR: stack creation failed !");

    // Verify that the new stack is empty
    ASSERT_TRUE(stack_is_empty(stack) && "ERROR: new stack is not empty !");

    // Push two values onto the stack
    ASSERT_TRUE(stack_push(stack, 3) && "ERROR: failed to push 3 !");
    ASSERT_TRUE(stack_push(stack, 8) && "ERROR: failed to push 8 !");

    // Verify the number of elements
    ASSERT_TRUE(stack_length(stack) == 2 && "ERROR: stack size is not 2 !");

    // Initialize a variable to store popped values
    int value = 0;

    // Verify the LIFO order of the stack
    ASSERT_TRUE(stack_pop(stack, &value) && value == 8 &&
                "ERROR: stack order is incorrect !");
    ASSERT_TRUE(stack_pop(stack, &value) && value == 3 &&
                "ERROR: stack order is incorrect !");

    // Verify that pop fails when the stack is empty
    ASSERT_TRUE(!stack_pop(stack, NULL) &&
                "ERROR: pop from empty stack succeeded !");

    // Destroy the stack and release its memory
    stack_destroy(&stack);

    // Verify that the stack pointer was reset to NULL
    ASSERT_TRUE(stack == NULL && "ERROR: stack was not destroyed !");

    // Display the test completion message
    fputs("func: void test_stack(void) ended successfully ...\n", stdout);
}
