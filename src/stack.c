/**
 * @file  : stack.c
 * @brief : This file defines the functions declared in stack.h
 */

#include "../include/stack.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structs */

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    size_t length;
} Stack;

/* Internal API */

/**
 * @brief Removes all elements from a stack
 *
 * @param[in,out] stack Stack to clear
 *
 * @note The stack itself remains allocated and can be reused
 */
static void stack_clear(stack_t stack);

/* Public API */

stack_t stack_create(void) {
    // Create an empty stack and initialize all fields to zero
    return calloc(1, sizeof(Stack));
}

void stack_destroy(stack_t *stack) {
    // Do nothing if the stack pointer or the stack itself is NULL
    if (stack == NULL || *stack == NULL) return;

    // Clear all elements from the stack
    stack_clear(*stack);

    // Free the memory allocated for the stack
    free(*stack);
    *stack = NULL;
}

/* Stack state */

bool stack_is_empty(const stack_t stack) {
    // Return true if the stack is NULL or empty
    return stack == NULL || stack->length == 0;
}

size_t stack_length(const stack_t stack) {
    // Return the number of elements in the stack, or 0 if the stack is NULL
    return !stack ? 0 : stack->length;
}

/* Insertion */

bool stack_push(stack_t stack, int value) {
    // Do nothing if the stack is NULL
    if (!stack) return false;

    // Allocate memory for a new node
    StackNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return false;

    // Initialize the new node and link it to the current top
    node->value = value;
    node->next = stack->top;

    // Update the top of the stack
    stack->top = node;

    // Update the stack length
    stack->length++;

    return true;
}

/* Removal */

bool stack_pop(stack_t stack, int *out_value) {
    // Do nothing if the stack is empty
    if (stack_is_empty(stack)) return false;

    // Store the top node
    StackNode *node = stack->top;

    // Copy its value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the top node
    stack->top = node->next;

    // Update the stack length and free the removed node
    stack->length--;
    free(node);

    return true;
}

/* Internal helpers */

static void stack_clear(stack_t stack) {
    // Do nothing if the stack is NULL
    if (!stack) return;

    // Remove all elements from the stack
    int ignored = 0;
    while (stack_pop(stack, &ignored)) {}
}

/* Utilities */

void stack_print(const stack_t stack) {
    // Print the opening bracket
    putchar('[');

    // Print all values separated by commas
    if (stack != NULL) {
        for (
            const StackNode *node = stack->top;
            node != NULL;
            node = node->next
        ) {
            printf("%d%s", node->value, node->next == NULL ? "" : ", ");
        }
    }

    // Print the closing bracket and a newline
    puts("]");
}
