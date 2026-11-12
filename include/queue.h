#ifndef DATA_STRUCTURES_QUEUE_H
#define DATA_STRUCTURES_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

/* types */

typedef struct Queue *queue_t;

/* Lifecycle */

/**
 * @brief Creates a new empty queue
 *
 * @return A pointer to the newly created queue, or NULL if allocation fails
 */
queue_t queue_create(void);

/**
 * @brief Destroys a queue and releases all allocated memory
 *
 * @param[in,out] queue Pointer to the queue to destroy
 *
 * @note Sets the queue pointer to NULL after destruction
 */
void queue_destroy(queue_t *queue);

/* Capacity */

/**
 * @brief Checks whether a queue is empty
 *
 * @param[in] queue Queue to check
 *
 * @return true if the queue is empty or NULL, false otherwise
 */
bool queue_is_empty(const queue_t queue);

/**
 * @brief Gets the number of elements in a queue
 *
 * @param[in] queue Queue to inspect
 *
 * @return Number of elements, or 0 if the queue is NULL
 */
size_t queue_length(const queue_t queue);

/* Modifiers */

/**
 * @brief Adds a new element to the back of a queue
 *
 * @param[in,out] queue Queue to modify
 * @param[in] value Value to insert
 *
 * @return true if insertion succeeds, false otherwise
 */
bool queue_enqueue(queue_t queue, int value);

/**
 * @brief Removes the front element from a queue
 *
 * @param[in,out] queue Queue to modify
 * @param[out] out_value Pointer to store the removed value (optional)
 *
 * @return true if removal succeeds, false if the queue is empty or NULL
 */
bool queue_dequeue(queue_t queue, int *out_value);

/* Utilities */

/**
 * @brief Prints all elements of a queue
 *
 * @param[in] queue Queue to print
 */
void queue_print(const queue_t queue);

#endif /* DATA_STRUCTURES_QUEUE_H */
