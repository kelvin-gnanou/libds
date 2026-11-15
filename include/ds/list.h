#ifndef DS_LIST_H
#define DS_LIST_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct List *ds_list_t;

/* Lifecycle */

/**
 * @brief Creates a new empty linked list.
 *
 * @return A newly allocated list, or NULL if memory allocation fails.
 */
ds_list_t ds_list_create(void);

/**
 * @brief Destroys a list and releases all allocated resources.
 *
 * @param[in,out] list Address of the list handle to destroy.
 *
 * @note Sets the list handle to NULL after destruction.
 */
void ds_list_destroy(ds_list_t *list);

/* List state */

/**
 * @brief Checks whether a list is empty.
 *
 * @param[in] list List to inspect.
 *
 * @return true if the list is NULL or contains no elements; false otherwise.
 */
bool ds_list_empty(const ds_list_t list);

/**
 * @brief Returns the number of elements in a list.
 *
 * @param[in] list List to inspect.
 *
 * @return Number of elements, or 0 if the list is NULL.
 */
size_t ds_list_size(const ds_list_t list);

/* Utilities */

// /**
//  * @brief Prints all elements of a list in order.
//  *
//  * @param[in] list List to print.
//  */
// void ds_list_print(const ds_list_t list);

/* Insertion */

/**
 * @brief Inserts a new element at the beginning of a list.
 *
 * @param[in,out] list List to modify.
 * @param[in] value Value to insert.
 *
 * @return true if insertion succeeds; false if the list is NULL or memory allocation fails.
 */
bool ds_list_push_front(ds_list_t list, int value);

/**
 * @brief Inserts a new element at the end of a list.
 *
 * @param[in,out] list List to modify.
 * @param[in] value Value to insert.
 *
 * @return true if insertion succeeds; false if the list is NULL or memory allocation fails.
 */
bool ds_list_push_back(ds_list_t list, int value);

/* Removal */

/**
 * @brief Removes the first element of a list.
 *
 * @param[in,out] list List to modify.
 * @param[out] out_value Optional pointer to store the removed value.
 *
 * @return true if removal succeeds; false if the list is NULL or empty.
 */
bool ds_list_pop_front(ds_list_t list, int *out_value);

/**
 * @brief Removes the last element of a list.
 *
 * @param[in,out] list List to modify.
 * @param[out] out_value Optional pointer to store the removed value.
 *
 * @return true if removal succeeds; false if the list is NULL or empty.
 */
bool ds_list_pop_back(ds_list_t list, int *out_value);

/**
 * @brief Removes the first occurrence of a given value.
 *
 * @param[in,out] list List to modify.
 * @param[in] value Value to remove.
 *
 * @return true if the value is found and removed; false if the list is NULL or the value is not found.
 */
bool ds_list_remove_first(ds_list_t list, int value);

/**
 * @brief Removes the last occurrence of a given value.
 *
 * @param[in,out] list List to modify.
 * @param[in] value Value to remove.
 *
 * @return true if the value is found and removed; false if the list is NULL or the value is not found.
 */
bool ds_list_remove_last(ds_list_t list, int value);

/*
Imposing terminal output on a generic library is discouraged. However, it is necessary for testing purposes. Therefore, I will create a dedicated `test_utils.h` for testing and later introduce an `example_utils.h` for demonstration purposes.
*/

// /**
//  * @brief Prints the list elements in order.
//  *
//  * @param[in] list List to print.
//  */
// void ds_list_print(const ds_list_t list);

#endif /* DS_LIST_H */
