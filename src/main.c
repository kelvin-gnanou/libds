/**
 * @file   : main.c
 * @brief  : Demonstrates the implemented data structures
 */

#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/list.h"
#include "../include/tree.h"
#include "../include/graph.h"

#include <stdio.h>

/* Demonstrations */

/**
 * @brief Demonstrates graph creation, edge insertion and destruction
 */
static void demo_graph(void) {
    // Create an undirected graph with four vertices
    graph_t graph = graph_create(4, false);

    // Stop if memory allocation fails
    if (!graph) {
        fprintf(stderr, "Graph allocation failed.\n");
        return;
    }

    // Add edges between vertices
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 2, 3);

    // Print the graph
    graph_print(graph);

    // Destroy the graph and release allocated memory
    graph_destroy(&graph);
}

/**
 * @brief Demonstrates binary search tree operations
 */
static void demo_tree(void) {
    // Create an empty binary tree
    BinaryTree tree = tree_create();

    // Define the values to insert into the tree
    const int values[] = {6, 9, 0, -4, 12};
    const size_t size = sizeof(values) / sizeof(values[0]);

    // Insert all values into the tree
    for (size_t i = 0; i < size; ++i) {
        if (!tree_insert(&tree, values[i])) {
            fprintf(stderr, "Tree allocation failed.\n");
        }
    }

    // Print the tree using inorder traversal
    printf("Inorder traversal : ");
    tree_print_inorder(tree);

    // Display the number of nodes and the tree height
    printf("Nodes : %zu | height : %zu\n",
        tree_size(tree),
        tree_height(tree));

    // Destroy the tree and release allocated memory
    tree_destroy(&tree);
}

/**
 * @brief Demonstrates linked list operations
 */
static void demo_list(void) {
    // Create an empty list
    list_t list = list_create();

    // Stop if memory allocation fails
    if (!list) {
        fprintf(stderr, "List allocation failed.\n");
        return;
    }

    // Insert values into the list
    list_push_back(list, 4);
    list_push_back(list, 9);
    list_push_front(list, -2);

    // Print the list
    list_print(list);

    // Destroy the list and release allocated memory
    list_destroy(&list);
}

/**
 * @brief Demonstrates queue operations
 */
static void demo_queue(void) {
    // Create an empty queue
    queue_t queue = queue_create();

    // Stop if memory allocation fails
    if (!queue) {
        fprintf(stderr, "Queue allocation failed.\n");
        return;
    }

    // Enqueue values
    queue_enqueue(queue, 14);
    queue_enqueue(queue, -34);

    // Print the queue
    queue_print(queue);

    // Destroy the queue and release allocated memory
    queue_destroy(&queue);
}

/**
 * @brief Demonstrates stack operations
 */
static void demo_stack(void) {
    // Create an empty stack
    stack_t stack = stack_create();

    // Stop if memory allocation fails
    if (!stack) {
        fprintf(stderr, "Stack allocation failed.\n");
        return;
    }

    // Push values onto the stack
    stack_push(stack, 11);
    stack_push(stack, -13);
    stack_push(stack, 15);

    // Print the stack
    stack_print(stack);

    // Destroy the stack and release allocated memory
    stack_destroy(&stack);
}

/* Menu */

static void menu(void) {
    // Display the available data structures
    puts("\nData Structures in C");
    puts("\t1. Binary Search Tree");
    puts("\t2. Graph (Adjacency Lists)");
    puts("\t3. Linked List");
    puts("\t4. Queue");
    puts("\t5. Stack");
    puts("\t0. Exit");

    // Prompt the user for a choice
    printf("Choice > ");
}

static void choice(int choice) {
    // Execute the selected demonstration
    switch (choice) {
        case 1: demo_tree(); break;
        case 2: demo_graph(); break;
        case 3: demo_list(); break;
        case 4: demo_queue(); break;
        case 5: demo_stack(); break;
        case 0: break;
        default: puts("Unknown choice."); break;
    }
}

/* Main */

int main(void) {
    int ch = 0;

    // Display the menu until the user chooses to quit
    do {
        menu();

        // Stop if the input is invalid
        if (scanf("%d", &ch) != 1) {
            puts("Invalid input.");
            return 1;
        }

        // Execute the selected option
        choice(ch);

    } while (ch != 0);

    return 0;
}
