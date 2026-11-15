/**
 * @file queue.c
 * @brief Implements the public queue interface declared in ds/queue.h.
 * @todo Implement an iterator.
 */

#include "../include/ds/queue.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structures */

typedef struct QueueNode {
    int value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    size_t size;
} Queue;

/* Internal API */

/**
 * @brief Removes all elements from a queue.
 *
 * @param[in,out] queue Queue to clear.
 *
 * @note The queue remains allocated and can be reused.
 */
static void ds_queue_clear(ds_queue_t queue);

/* Public API */

ds_queue_t ds_queue_create(void) {
    // Create an empty queue and initialize all fields to zero
    return calloc(1, sizeof(Queue));
}

/* Queue state */

bool ds_queue_empty(const ds_queue_t queue) {
    // Check whether the queue is NULL or empty
    return !queue || queue->size == 0;
}

size_t ds_queue_size(const ds_queue_t queue) {
    // Return the number of elements, or 0 if the queue is NULL
    return !queue ? 0 : queue->size;
}

/* Insertion */

bool ds_queue_enqueue(ds_queue_t queue, int value) {
    // Reject a NULL queue
    if (!queue) return false;

    // Allocate memory for a new node
    QueueNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return false;

    // Initialize the new node
    node->value = value;
    node->next = NULL;

    // Insert the new node at the end of the queue
    if (!queue->tail)
        queue->head = node;
    else
        queue->tail->next = node;

    // Update the tail pointer
    queue->tail = node;

    // Increment the queue size
    queue->size++;

    return true;
}

/* Removal */

bool ds_queue_dequeue(ds_queue_t queue, int *out_value) {
    // Reject a NULL or empty queue
    if (ds_queue_empty(queue)) return false;

    // Store the first node
    QueueNode *node = queue->head;

    // Copy the value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the first node
    queue->head = node->next;

    // Reset the tail if the queue becomes empty
    if (!queue->head)
        queue->tail = NULL;

    // Decrement the queue size and free the removed node
    queue->size--;
    free(node);

    return true;
}

/* Internal helpers */

static void ds_queue_clear(ds_queue_t queue) {
    // Do nothing if the queue is NULL
    if (!queue) return;

    // Remove all elements from the queue
    int ignored = 0;
    while (ds_queue_dequeue(queue, &ignored)) {}
}

void ds_queue_destroy(ds_queue_t *queue) {
    // Do nothing if the queue pointer or the queue itself is NULL
    if (queue == NULL || *queue == NULL) return;

    // Clear all elements from the queue
    ds_queue_clear(*queue);

    // Free the queue structure
    free(*queue);
    *queue = NULL;
}

// /* Utilities */

// void ds_queue_print(const ds_queue_t queue) {
//     // Print the opening bracket
//     putchar('[');

//     // Print all elements separated by commas
//     if (queue != NULL) {
//         for (
//             const QueueNode *node = queue->head;
//             node != NULL;
//             node = node->next
//         ) {
//             printf("%d%s", node->value, node->next == NULL ? "" : ", ");
//         }
//     }

//     // Print the closing bracket followed by a newline
//     puts("]");
// }
