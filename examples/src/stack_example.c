/**
 * @file stack_example.c
 * @brief Demonstrates stack operations
 */

#include "../include/examples.h"

#include <stdio.h>

/**
 * @brief Demonstrates stack operations
 */
void demo_stack(void) {
    // Create an empty stack
    ds_stack_t stack = ds_stack_create();

    // Stop if memory allocation fails
    if (!stack) {
        fprintf(stderr, "Stack allocation failed.\n");
        return;
    }

    // Push values onto the stack.
    ds_stack_push(stack, 11);
    ds_stack_push(stack, -13);
    ds_stack_push(stack, 15);

    // Print the stack
    // ds_stack_print(stack);

    // Destroy the stack
    ds_stack_destroy(&stack);
}
