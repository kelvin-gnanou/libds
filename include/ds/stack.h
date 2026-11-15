#ifndef DS_STACK_H
#define DS_STACK_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct Stack *ds_stack_t;

/* Lifecycle */

/**
 * @brief Creates a new empty stack.
 *
 * @return A newly allocated stack, or NULL if memory allocation fails.
 */
ds_stack_t ds_stack_create(void);

/**
 * @brief Destroys a stack and releases all allocated resources.
 *
 * @param[in,out] stack Address of the stack handle to destroy.
 *
 * @note Sets the stack handle to NULL after destruction.
 */
void ds_stack_destroy(ds_stack_t *stack);

/* Stack state */

/**
 * @brief Checks whether a stack is empty.
 *
 * @param[in] stack Stack to inspect.
 *
 * @return true if the stack is NULL or contains no elements; false otherwise.
 */
bool ds_stack_empty(const ds_stack_t stack);

/**
 * @brief Returns the number of elements in a stack.
 *
 * @param[in] stack Stack to inspect.
 *
 * @return The number of elements, or 0 if the stack is NULL.
 */
size_t ds_stack_size(const ds_stack_t stack);

/* Insertion */

/**
 * @brief Pushes a new element onto the top of a stack.
 *
 * @param[in,out] stack Stack to modify.
 * @param[in] value Value to insert.
 *
 * @return true if insertion succeeds; false if the stack is NULL or memory
 * allocation fails.
 */
bool ds_stack_push(ds_stack_t stack, int value);

/* Removal */

/**
 * @brief Removes the top element from a stack.
 *
 * @param[in,out] stack Stack to modify.
 * @param[out] out_value Optional pointer to store the removed value.
 *
 * @return true if removal succeeds; false if the stack is NULL or empty.
 */
bool ds_stack_pop(ds_stack_t stack, int *out_value);

// /* Utilities */

/*
Imposing terminal output on a generic library is discouraged. However, it is necessary for testing purposes. Therefore, I will create a dedicated `test_utils.h` for testing and later introduce an `example_utils.h` for demonstration purposes.
*/

// /**
//  * @brief Prints all elements of a stack.
//  *
//  * @param[in] stack Stack to print.
//  */
// void ds_stack_print(const ds_stack_t stack);

#endif /* DS_STACK_H */
