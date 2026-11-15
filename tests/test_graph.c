/**
 * @file test_graph.c
 * @brief Tests for the graph implementation.
 * @todo Add more tests.
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/ds/graph.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests graph creation, edge insertion, validation, and destruction.
 */
void test_graph(void) {
    // Create an undirected graph with three vertices
    ds_graph_t graph = ds_graph_create(3, false);

    // Verify that graph creation succeeded
    ASSERT_TRUE(graph != NULL && "ERROR: graph creation failed!");

    // Verify the number of vertices
    ASSERT_TRUE(ds_graph_size(graph) == 3 &&
                "ERROR: graph vertex count is not 3!");

    // Verify that a valid edge can be inserted
    ASSERT_TRUE(ds_graph_insert(graph, 0, 2) &&
                "ERROR: failed to insert edge 0-2!");

    // Verify that an invalid vertex index is rejected
    ASSERT_TRUE(!ds_graph_insert(graph, 0, 3) &&
                "ERROR: invalid vertex index was accepted!");

    // Destroy the graph and release its memory
    ds_graph_destroy(&graph);

    // Verify that the graph handle was reset to NULL
    ASSERT_TRUE(graph == NULL && "ERROR: graph was not destroyed!");

    // Create an empty directed graph
    graph = ds_graph_create(0, true);

    // Verify that empty graph creation succeeded
    ASSERT_TRUE(graph != NULL && "ERROR: empty graph creation failed!");

    // Verify that no edge can be inserted into an empty graph
    ASSERT_TRUE(!ds_graph_insert(graph, 0, 0) &&
                "ERROR: edge was inserted into an empty graph!");

    // Destroy the empty graph
    ds_graph_destroy(&graph);

    // Display the test completion message
    fputs("func: void test_graph(void) ended successfully ...\n", stdout);
}
