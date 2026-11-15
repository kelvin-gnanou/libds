/**
 * @file stack.c
 * @brief Implements the public stack interface declared in ds/stack.h.
 * @todo Implement an iterator.
 */

#include "../include/ds/stack.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structures */

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    size_t size;
} Stack;

/* Internal API */

/**
 * @brief Removes all elements from a stack.
 *
 * @param[in,out] stack Stack to clear.
 *
 * @note The stack remains allocated and can be reused.
 */
static void ds_stack_clear(ds_stack_t stack);

/* Public API */

ds_stack_t ds_stack_create(void) {
    // Create an empty stack and initialize all fields to zero
    return calloc(1, sizeof(Stack));
}

void ds_stack_destroy(ds_stack_t *stack) {
    // Do nothing if the stack pointer or the stack itself is NULL
    if (stack == NULL || *stack == NULL) return;

    // Remove all elements from the stack
    ds_stack_clear(*stack);

    // Free the stack structure
    free(*stack);
    *stack = NULL;
}

/* Stack state */

bool ds_stack_empty(const ds_stack_t stack) {
    // Check whether the stack is NULL or empty
    return stack == NULL || stack->size == 0;
}

size_t ds_stack_size(const ds_stack_t stack) {
    // Return the number of elements, or 0 if the stack is NULL
    return !stack ? 0 : stack->size;
}

/* Insertion */

bool ds_stack_push(ds_stack_t stack, int value) {
    // Reject a NULL stack
    if (!stack) return false;

    // Allocate memory for a new node
    StackNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return false;

    // Initialize the new node and link it to the current top
    node->value = value;
    node->next = stack->top;

    // Update the top pointer
    stack->top = node;

    // Increment the stack size
    stack->size++;

    return true;
}

/* Removal */

bool ds_stack_pop(ds_stack_t stack, int *out_value) {
    // Reject a NULL or empty stack
    if (ds_stack_empty(stack)) return false;

    // Store the top node
    StackNode *node = stack->top;

    // Copy the value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the top node
    stack->top = node->next;

    // Decrement the stack size and free the removed node
    stack->size--;
    free(node);

    return true;
}

/* Internal helpers */

static void ds_stack_clear(ds_stack_t stack) {
    // Do nothing if the stack is NULL
    if (!stack) return;

    // Remove all elements from the stack
    int ignored = 0;
    while (ds_stack_pop(stack, &ignored)) {}
}

// /* Utilities */

// void ds_stack_print(const ds_stack_t stack) {
//     // Print the opening bracket
//     putchar('[');

//     // Print all elements separated by commas
//     if (stack != NULL) {
//         for (
//             const StackNode *node = stack->top;
//             node != NULL;
//             node = node->next
//         ) {
//             printf("%d%s", node->value, node->next == NULL ? "" : ", ");
//         }
//     }

//     // Print the closing bracket followed by a newline
//     puts("]");
// }
