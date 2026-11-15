#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct Queue *ds_queue_t;

/* Lifecycle */

/**
 * @brief Creates a new empty queue.
 *
 * @return A newly allocated queue, or NULL if memory allocation fails.
 */
ds_queue_t ds_queue_create(void);

/**
 * @brief Destroys a queue and releases all allocated resources.
 *
 * @param[in,out] queue Address of the queue handle to destroy.
 *
 * @note Sets the queue handle to NULL after destruction.
 */
void ds_queue_destroy(ds_queue_t *queue);

/* Queue state */

/**
 * @brief Checks whether a queue is empty.
 *
 * @param[in] queue Queue to inspect.
 *
 * @return true if the queue is NULL or contains no elements; false otherwise.
 */
bool ds_queue_empty(const ds_queue_t queue);

/**
 * @brief Returns the number of elements in a queue.
 *
 * @param[in] queue Queue to inspect.
 *
 * @return The number of elements, or 0 if the queue is NULL.
 */
size_t ds_queue_size(const ds_queue_t queue);

/* Insertion */

/**
 * @brief Inserts a new element at the back of a queue.
 *
 * @param[in,out] queue Queue to modify.
 * @param[in] value Value to insert.
 *
 * @return true if insertion succeeds; false if the queue is NULL or memory
 * allocation fails.
 */
bool ds_queue_enqueue(ds_queue_t queue, int value);

/* Removal */

/**
 * @brief Removes the front element from a queue.
 *
 * @param[in,out] queue Queue to modify.
 * @param[out] out_value Optional pointer to store the removed value.
 *
 * @return true if removal succeeds; false if the queue is NULL or empty.
 */
bool ds_queue_dequeue(ds_queue_t queue, int *out_value);

// /* Utilities */

/*
Imposing terminal output on a generic library is discouraged. However, it is necessary for testing purposes. Therefore, I will create a dedicated `test_utils.h` for testing and later introduce an `example_utils.h` for demonstration purposes.
*/

// /**
//  * @brief Prints all elements of a queue.
//  *
//  * @param[in] queue Queue to print.
//  */
// void ds_queue_print(const ds_queue_t queue);

#endif /* DS_QUEUE_H */
