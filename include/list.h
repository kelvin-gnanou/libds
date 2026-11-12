#ifndef DATA_STRUCTURES_LIST_H
#define DATA_STRUCTURES_LIST_H

#include <stdbool.h>
#include <stddef.h>

/* types */

typedef struct List *list_t;

/* Lifecycle */

/**
 * @brief Creates a new empty list
 *
 * @return A pointer to the newly created list, or NULL if allocation fails
 */
list_t list_create(void);

/**
 * @brief Destroys a list and releases all allocated memory
 *
 * @param[in,out] list Pointer to the list to destroy
 *
 * @note Sets the list pointer to NULL after destruction
 */
void list_destroy(list_t *list);

/* Capacity */

/**
 * @brief Checks whether a list is empty
 *
 * @param[in] list List to check
 *
 * @return true if the list is empty or NULL, false otherwise
 */
bool list_is_empty(const list_t list);

/**
 * @brief Gets the number of elements in a list
 *
 * @param[in] list List to inspect
 *
 * @return Number of elements, or 0 if the list is NULL
 */
size_t list_length(const list_t list);

/* Utilities */

/**
 * @brief Prints all elements of a list
 *
 * @param[in] list List to print
 */
void list_print(const list_t list);

/* Modifiers */

/**
 * @brief Inserts a new element at the beginning of a list
 *
 * @param[in,out] list List to modify
 * @param[in] value Value to insert
 *
 * @return true if insertion succeeds, false otherwise
 */
bool list_push_front(list_t list, int value);

/**
 * @brief Inserts a new element at the end of a list
 *
 * @param[in,out] list List to modify
 * @param[in] value Value to insert
 *
 * @return true if insertion succeeds, false otherwise
 */
bool list_push_back(list_t list, int value);

/**
 * @brief Removes the first element of a list
 *
 * @param[in,out] list List to modify
 * @param[out] out_value Pointer to store the removed value (optional)
 *
 * @return true if removal succeeds, false if the list is empty or NULL
 */
bool list_pop_front(list_t list, int *out_value);

/**
 * @brief Removes the last element of a list
 *
 * @param[in,out] list List to modify
 * @param[out] out_value Pointer to store the removed value (optional)
 *
 * @return true if removal succeeds, false if the list is empty or NULL
 */
bool list_pop_back(list_t list, int *out_value);

/**
 * @brief Removes the first occurrence of a given value
 *
 * @param[in,out] list List to modify
 * @param[in] value Value to remove
 *
 * @return true if the value is found and removed, false otherwise
 */
bool list_remove_first(list_t list, int value);

/**
 * @brief Removes the last occurrence of a given value
 *
 * @param[in,out] list List to modify
 * @param[in] value Value to remove
 *
 * @return true if the value is found and removed, false otherwise
 */
bool list_remove_last(list_t list, int value);

#endif /* DATA_STRUCTURES_LIST_H */
