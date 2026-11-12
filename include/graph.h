#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct Graph *graph_t;

/* Lifecycle */

/**
 * @brief Creates a new graph with a specified number of vertices
 *
 * @param[in] vertex_count Number of vertices in the graph
 * @param[in] directed If true, creates a directed graph; otherwise, creates an undirected graph
 *
 * @return A pointer to the newly created graph, or NULL if allocation fails
 */
graph_t graph_create(size_t vertex_count, bool directed);

/**
 * @brief Destroys a graph and releases all allocated memory
 *
 * @param[in,out] graph Pointer to the graph to destroy
 *
 * @note Sets the graph pointer to NULL after destruction
 */
void graph_destroy(graph_t *graph);

/* Graph operations */

/**
 * @brief Gets the number of vertices in a graph
 *
 * @param[in] graph Graph to inspect
 *
 * @return Number of vertices in the graph, or 0 if the graph is NULL
 */
size_t graph_vertex_count(const graph_t graph);

/**
 * @brief Adds an edge between two vertices
 *
 * @param[in,out] graph Graph to modify
 * @param[in] source Index of the source vertex
 * @param[in] destination Index of the destination vertex
 *
 * @return true if the edge is added successfully, false otherwise
 */
bool graph_add_edge(graph_t graph, size_t source, size_t destination);

/**
 * @brief Prints the graph and its edges
 *
 * @param[in] graph Graph to print
 */
void graph_print(const graph_t graph);

#endif /* DATA_STRUCTURES_GRAPH_H */
