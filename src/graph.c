/**
 * @file   : graph.c
 * @brief  : This file defines the functions declared in graph.h
 * @todo   : Check for duplicate edges before insertion
 */

#include "../include/graph.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structs */

typedef struct Neighbor {
    size_t vertex;
    struct Neighbor *next;
} Neighbor;

typedef struct Graph {
    size_t vertex_count;
    bool directed;
    Neighbor **adjacency;
} Graph;

/* Internal API */

/**
 * @brief Adds a directed edge between two vertices
 *
 * @param[in,out] graph Graph to modify
 * @param[in] source Index of the source vertex
 * @param[in] destination Index of the destination vertex
 *
 * @return true if the edge is added successfully, false if memory allocation fails
 */
static bool add_directed_edge(graph_t graph, size_t source, size_t destination);

/* Lifecycle */

graph_t graph_create(size_t vertex_count, bool directed) {
    // Allocate memory for a new graph and initialize its fields to zero
    graph_t graph = calloc(1, sizeof(*graph));

    // Stop if memory allocation fails
    if (!graph) return NULL;

    // Allocate the adjacency list for all vertices
    if (vertex_count) {
        graph->adjacency = calloc(vertex_count, sizeof(*(graph->adjacency)));

        // Free the graph if adjacency allocation fails
        if (!graph->adjacency) {
            free(graph);
            return NULL;
        }
    }

    // Initialize the graph properties
    graph->vertex_count = vertex_count;
    graph->directed = directed;

    return graph;
}

void graph_destroy(graph_t *graph) {
    // Do nothing if the graph pointer or the graph itself is NULL
    if (graph == NULL || *graph == NULL) return;

    // Free all adjacency lists
    for (size_t i = 0; i < (*graph)->vertex_count; ++i) {
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

    // Reset the graph pointer
    *graph = NULL;
}

/* Graph state */

size_t graph_vertex_count(const graph_t graph) {
    // Return the number of vertices, or 0 if the graph is NULL
    return !graph ? 0 : graph->vertex_count;
}

/* Internal helpers */

static bool add_directed_edge(graph_t graph, size_t source, size_t destination) {
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

/* Operations */

bool graph_add_edge(graph_t graph, size_t source, size_t destination) {
    // Do nothing if the graph is NULL or a vertex index is invalid
    if (!graph || source >= graph->vertex_count || destination >= graph->vertex_count) {
        return false;
    }

    // Add the directed edge from source to destination
    if (!add_directed_edge(graph, source, destination)) return false;

    // Add the reverse edge if the graph is undirected
    if (!graph->directed && !add_directed_edge(graph, destination, source)) {
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

void graph_print(const graph_t graph) {
    // Print an error message if the graph is NULL
    if (!graph) {
        puts("(graphe nul)");
        return;
    }

    // Print the adjacency list of each vertex
    for (size_t i = 0; i < graph->vertex_count; ++i) {
        printf("%zu :", i);

        // Print all neighbors of the current vertex
        for (
            const Neighbor *node = graph->adjacency[i];
            node != NULL;
            node = node->next
        ) {
            printf(" %zu", node->vertex);
        }

        putchar('\n');
    }
}
