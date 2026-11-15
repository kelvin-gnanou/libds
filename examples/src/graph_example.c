/**
 * @file graph_example.c
 * @brief Demonstrates graph operations.
 */

#include "../include/examples.h"

#include <stdio.h>

/**
 * @brief Demonstrates graph creation, edge insertion, and destruction
 */
void demo_graph(void) {
    // Create an undirected graph with four vertices.
    ds_graph_t graph = ds_graph_create(4, false);

    // Stop if memory allocation fails.
    if (!graph) {
        fprintf(stderr, "Graph allocation failed.\n");
        return;
    }

    // Add edges between vertices
    ds_graph_insert(graph, 0, 2);
    ds_graph_insert(graph, 0, 1);
    ds_graph_insert(graph, 2, 3);

    // Print the graph
    // ds_graph_print(graph);

    // Destroy the graph
    ds_graph_destroy(&graph);
}
