/**
 * @file test_queue.c
 * @brief Tests for the queue implementation.
 * @todo Add more tests.
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/ds/queue.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests queue creation, insertion, removal, and destruction.
 */
void test_queue(void) {
    // Create two independent queues.
    ds_queue_t queue = ds_queue_create();
    ds_queue_t second = ds_queue_create();

    // Verify that both queues were created successfully.
    ASSERT_TRUE(queue != NULL && second != NULL &&
                "ERROR: queue creation failed!");

    // Enqueue values into the first queue.
    ASSERT_TRUE(ds_queue_enqueue(queue, 10) &&
                "ERROR: failed to enqueue 10!");
    ASSERT_TRUE(ds_queue_enqueue(queue, 20) &&
                "ERROR: failed to enqueue 20!");

    // Enqueue a value into the second queue.
    ASSERT_TRUE(ds_queue_enqueue(second, 7) &&
                "ERROR: failed to enqueue 7 in the second queue!");

    // Verify the number of elements in each queue.
    ASSERT_TRUE(ds_queue_size(queue) == 2 &&
                "ERROR: queue size is not 2!");
    ASSERT_TRUE(ds_queue_size(second) == 1 &&
                "ERROR: second queue size is not 1!");

    // Initialize a variable to store dequeued values.
    int value = 0;

    // Verify the FIFO order of the first queue.
    ASSERT_TRUE(ds_queue_dequeue(queue, &value) && value == 10 &&
                "ERROR: queue order is incorrect!");
    ASSERT_TRUE(ds_queue_dequeue(queue, &value) && value == 20 &&
                "ERROR: queue order is incorrect!");

    // Verify that dequeue fails when the queue is empty.
    ASSERT_TRUE(!ds_queue_dequeue(queue, NULL) &&
                "ERROR: dequeue from an empty queue succeeded!");

    // Destroy both queues.
    ds_queue_destroy(&queue);
    ds_queue_destroy(&second);

    // Verify that both pointers were reset to NULL.
    ASSERT_TRUE(queue == NULL && second == NULL &&
                "ERROR: queues were not destroyed!");

    fputs("func: void test_queue(void) ended successfully ...\n", stdout);
}
