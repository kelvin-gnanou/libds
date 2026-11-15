/**
 * @file queue_example.c
 * @brief Demonstrates queue operations.
 */

#include "../include/examples.h"

#include <stdio.h>

/**
 * @brief Demonstrates queue operations.
 */
void demo_queue(void) {
    // Create an empty queue.
    ds_queue_t queue = ds_queue_create();

    // Stop if memory allocation fails.
    if (!queue) {
        fprintf(stderr, "Queue allocation failed.\n");
        return;
    }

    // Enqueue values.
    ds_queue_enqueue(queue, 14);
    ds_queue_enqueue(queue, -34);

    // Print the queue.
    // ds_queue_print(queue);

    // Destroy the queue.
    ds_queue_destroy(&queue);
}
