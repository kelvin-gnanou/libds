#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stdbool.h>
#include <stddef.h>

/* types */

typedef struct Stack *stack_t;

/* Lifecycle */

/**
 * @brief Creates a new empty stack
 *
 * @return A pointer to the newly created stack, or NULL if allocation fails
 */
stack_t stack_create(void);

/**
 * @brief Destroys a stack and releases all allocated memory
 *
 * @param[in,out] stack Pointer to the stack to destroy
 *
 * @note Sets the stack pointer to NULL after destruction
 */
void stack_destroy(stack_t *stack);

/* Capacity */

/**
 * @brief Checks whether a stack is empty
 *
 * @param[in] stack Stack to check
 *
 * @return true if the stack is empty or NULL, false otherwise
 */
bool stack_is_empty(const stack_t stack);

/**
 * @brief Gets the number of elements in a stack
 *
 * @param[in] stack Stack to inspect
 *
 * @return Number of elements, or 0 if the stack is NULL
 */
size_t stack_length(const stack_t stack);

/* Modifiers */

/**
 * @brief Pushes a new element onto the top of a stack
 *
 * @param[in,out] stack Stack to modify
 * @param[in] value Value to insert
 *
 * @return true if insertion succeeds, false otherwise
 */
bool stack_push(stack_t stack, int value);

/**
 * @brief Removes the top element from a stack
 *
 * @param[in,out] stack Stack to modify
 * @param[out] out_value Pointer to store the removed value (optional)
 *
 * @return true if removal succeeds, false if the stack is empty or NULL
 */
bool stack_pop(stack_t stack, int *out_value);

/* Utilities */

/**
 * @brief Prints all elements of a stack
 *
 * @param[in] stack Stack to print
 */
void stack_print(const stack_t stack);

#endif /* DATA_STRUCTURES_STACK_H */
