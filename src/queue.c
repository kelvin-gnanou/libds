/**
 * @file  : queue.c
 * @brief : This file defines the functions declared in queue.h
 */

#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structs */

typedef struct QueueNode {
    int value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    size_t length;
} Queue;

/* Internal API */

/**
 * @brief Removes all elements from a queue
 *
 * @param[in,out] queue Queue to clear
 *
 * @note The queue itself remains allocated and can be reused
 */
static void queue_clear(queue_t queue);

/* Public API */

queue_t queue_create(void) {
    // Create an empty queue and initialize all fields to zero
    return calloc(1, sizeof(Queue));
}

/* Queue state */

bool queue_is_empty(const queue_t queue) {
    // Return true if the queue is NULL or empty
    return !queue || queue->length == 0;
}

size_t queue_length(const queue_t queue) {
    // Return the number of elements in the queue, or 0 if the queue is NULL
    return !queue ? 0 : queue->length;
}

/* Insertion */

bool queue_enqueue(queue_t queue, int value) {
    // Do nothing if the queue is NULL
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

    // Update the tail
    queue->tail = node;

    // Update the queue length
    queue->length++;

    return true;
}

/* Removal */

bool queue_dequeue(queue_t queue, int *out_value) {
    // Do nothing if the queue is empty
    if (queue_is_empty(queue)) return false;

    // Store the first node
    QueueNode *node = queue->head;

    // Copy its value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the first node
    queue->head = node->next;

    // Update the tail if the queue becomes empty
    if (!queue->head)
        queue->tail = NULL;

    // Update the queue length and free the removed node
    queue->length--;
    free(node);

    return true;
}

/* Internal helpers */

static void queue_clear(queue_t queue) {
    // Do nothing if the queue is NULL
    if (!queue) return;

    // Remove all elements from the queue
    int ignored = 0;
    while (queue_dequeue(queue, &ignored)) {}
}

void queue_destroy(queue_t *queue) {
    // Do nothing if the queue pointer or the queue itself is NULL
    if (queue == NULL || *queue == NULL) return;

    // Clear all elements from the queue
    queue_clear(*queue);

    // Free the memory allocated for the queue
    free(*queue);
    *queue = NULL;
}

/* Utilities */

void queue_print(const queue_t queue) {
    // Print the opening bracket
    putchar('[');

    // Print all values separated by commas
    if (queue != NULL) {
        for (
            const QueueNode *node = queue->head;
            node != NULL;
            node = node->next
        ) {
            printf("%d%s", node->value, node->next == NULL ? "" : ", ");
        }
    }

    // Print the closing bracket and a newline
    puts("]");
}

