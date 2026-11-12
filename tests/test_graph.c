/**
 * @file : test_graph.c
 * @brief: Tests for the graph implementation
 * @todo : More test
 */

#include <assert.h>   // assert
#include <stddef.h>   // NULL
#include <stdio.h>    // fputs, stdout

#include "../include/graph.h"

#define ASSERT_TRUE(x) assert(x)

/**
 * @brief Tests graph creation, edge insertion, validation and destruction
 */
void test_graph(void) {
    // Create an undirected graph with three vertices
    graph_t graph = graph_create(3, false);

    // Verify that graph creation succeeded
    ASSERT_TRUE(graph != NULL && "ERROR: graph creation failed !");

    // Verify the number of vertices
    ASSERT_TRUE(graph_vertex_count(graph) == 3 &&
                "ERROR: graph vertex count is not 3 !");

    // Verify that a valid edge can be added
    ASSERT_TRUE(graph_add_edge(graph, 0, 2) &&
                "ERROR: failed to add edge 0-2 !");

    // Verify that an invalid vertex is rejected
    ASSERT_TRUE(!graph_add_edge(graph, 0, 3) &&
                "ERROR: invalid vertex was accepted !");

    // Destroy the graph and release its memory
    graph_destroy(&graph);

    // Verify that the graph pointer was reset to NULL
    ASSERT_TRUE(graph == NULL && "ERROR: graph was not destroyed !");

    // Create an empty directed graph
    graph = graph_create(0, true);

    // Verify that empty graph creation succeeded
    ASSERT_TRUE(graph != NULL && "ERROR: empty graph creation failed !");

    // Verify that edges cannot be added to an empty graph
    ASSERT_TRUE(!graph_add_edge(graph, 0, 0) &&
                "ERROR: edge added to empty graph !");

    // Destroy the empty graph
    graph_destroy(&graph);

    // Display the test completion message
    fputs("func: void test_graph(void) ended successfully ...\n", stdout);
}
