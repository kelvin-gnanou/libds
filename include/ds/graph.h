#ifndef DS_GRAPH_H
#define DS_GRAPH_H

#include <stdbool.h>
#include <stddef.h>

/* Types */

typedef struct Graph *ds_graph_t;

/* Lifecycle */

/**
 * @brief Creates a new graph with a specified number of vertices.
 *
 * @param[in] size Number of vertices in the graph.
 * @param[in] directed Whether the graph is directed.
 *
 * @return A newly allocated graph, or NULL if allocation fails.
 */
ds_graph_t ds_graph_create(size_t size, bool directed);

/**
 * @brief Destroys a graph and releases all allocated resources.
 *
 * @param[in,out] graph Address of the graph handle to destroy.
 *
 * @note Sets the graph handle to NULL after destruction.
 */
void ds_graph_destroy(ds_graph_t *graph);

/* Graph operations */

/**
 * @brief Returns the number of vertices in a graph.
 *
 * @param[in] graph Graph to inspect.
 *
 * @return Number of vertices, or 0 if the graph is NULL.
 */
size_t ds_graph_size(const ds_graph_t graph);

/**
 * @brief Inserts an edge between two vertices.
 *
 * @param[in,out] graph Graph to modify.
 * @param[in] source Index of the source vertex.
 * @param[in] destination Index of the destination vertex.
 *
 * @return true if the edge is inserted successfully; false otherwise.
 */
bool ds_graph_insert(ds_graph_t graph, size_t source, size_t destination);

/*
Imposing terminal output on a generic library is discouraged. However, it is necessary for testing purposes. Therefore, I will create a dedicated `test_utils.h` for testing and later introduce an `example_utils.h` for demonstration purposes.
*/

// /**
//  * @brief Prints the graph and its edges.
//  *
//  * @param[in] graph Graph to print.
//  */
// void ds_graph_print(const ds_graph_t graph);

#endif /* DS_GRAPH_H */
