/**
 * @file graph.c
 * @brief Implements the public graph interface declared in ds/graph.h.
 * @todo Check for duplicate edges before insertion.
 * @todo Implement iterators, an is_empty function, and edge removal.
 */

#include "../include/ds/graph.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structures */

typedef struct Neighbor {
    size_t vertex;
    struct Neighbor *next;
} Neighbor;

typedef struct Graph {
    size_t size;
    bool directed;
    Neighbor **adjacency;
} Graph;

/* Internal API */

/**
 * @brief Inserts a directed edge between two vertices.
 *
 * @param[in,out] graph Graph to modify.
 * @param[in] source Index of the source vertex.
 * @param[in] destination Index of the destination vertex.
 *
 * @return true if the edge is inserted successfully; false if memory allocation fails.
 */
static bool ds_add_edge(ds_graph_t graph, size_t source, size_t destination);

/* Lifecycle */

ds_graph_t ds_graph_create(size_t size, bool directed) {
    // Allocate memory for a new graph and initialize its fields to zero
    ds_graph_t graph = calloc(1, sizeof(*graph));

    // Stop if memory allocation fails
    if (!graph) return NULL;

    // Allocate the adjacency list for all vertices
    if (size) {
        graph->adjacency = calloc(size, sizeof(*(graph->adjacency)));

        // Free the graph if adjacency allocation fails
        if (!graph->adjacency) {
            free(graph);
            return NULL;
        }
    }

    // Initialize the graph properties
    graph->size = size;
    graph->directed = directed;

    return graph;
}

void ds_graph_destroy(ds_graph_t *graph) {
    // Do nothing if the graph pointer or the graph itself is NULL
    if (graph == NULL || *graph == NULL) return;

    // Free all adjacency lists
    for (size_t i = 0; i < (*graph)->size; ++i) {
        Neighbor *node = (*graph)->adjacency[i];

        // Free all neighbors of the current vertex
        while (node) {
            Neighbor *next = node->next;
            free(node);
            node = next;
        }
    }

    // Free the adjacency array and the graph itself
    free((*graph)->adjacency);
    free(*graph);

    // Reset the graph handle
    *graph = NULL;
}

/* Graph state */

size_t ds_graph_size(const ds_graph_t graph) {
    // Return the number of vertices, or 0 if the graph is NULL
    return !graph ? 0 : graph->size;
}

/* Internal helpers */

static bool ds_add_edge(ds_graph_t graph, size_t source, size_t destination) {
    // Allocate memory for a new neighbor
    Neighbor *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return false;

    // Initialize the new neighbor
    node->vertex = destination;
    node->next = graph->adjacency[source];

    // Insert the neighbor at the beginning of the adjacency list
    graph->adjacency[source] = node;

    return true;
}

/* Graph operations */

bool ds_graph_insert(ds_graph_t graph, size_t source, size_t destination) {
    // Reject a NULL graph or invalid vertex indices
    if (!graph || source >= graph->size || destination >= graph->size) {
        return false;
    }

    // Insert the directed edge from source to destination
    if (!ds_add_edge(graph, source, destination)) return false;

    // Insert the reverse edge if the graph is undirected
    if (!graph->directed && !ds_add_edge(graph, destination, source)) {
        // Roll back the first insertion if the reverse insertion fails
        Neighbor *added = graph->adjacency[source];
        graph->adjacency[source] = added->next;

        // Free the previously inserted edge
        free(added);
        return false;
    }

    return true;
}

/* Utilities */

// /**
//  * @brief Prints the graph and its adjacency lists.
//  *
//  * @param[in] graph Graph to print.
//  */
// void ds_graph_print(const ds_graph_t graph) {
//     // Print a placeholder if the graph is NULL
//     if (!graph) {
//         puts("(null graph)");
//         return;
//     }

//     // Print the adjacency list of each vertex
//     for (size_t i = 0; i < graph->size; ++i) {
//         printf("%zu :", i);

//         // Print all neighbors of the current vertex
//         for (
//             const Neighbor *node = graph->adjacency[i];
//             node != NULL;
//             node = node->next
//         ) {
//             printf(" %zu", node->vertex);
//         }

//         putchar('\n');
//     }
// }
