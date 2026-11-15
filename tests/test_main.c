/**
 * @file test_main.c
 * @brief Main entry point for the test suite
 */

#include <stdio.h>  // puts

/* Test function prototypes */

void test_graph(void);
void test_tree(void);
void test_list(void);
void test_queue(void);
void test_stack(void);

/**
 * @brief Runs all data structure tests
 *
 * @return 0 if all tests complete successfully
 */
int main(void) {
    // Display the beginning of the test suite
    puts("\nBEGINNING OF TESTS ...\n");

    // Run binary tree tests
    test_tree();

    // Run graph tests
    test_graph();

    // Run linked list tests
    test_list();

    // Run queue tests
    test_queue();

    // Run stack tests
    test_stack();

    // Display the test suite completion message
    puts("\nALL TESTS PASSED ...\n");

    // Return success status
    return 0;
}
