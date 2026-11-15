/**
 * @file main.c
 * @brief Main entry point for the data structures demonstrations
 */

#include "../include/examples.h"

#include <stdio.h>

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

/* Menu handler */

static void handle_choice(int choice) {
    // Execute the selected demonstration.
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

    // Display the menu until the user chooses to quit.
    do {
        menu();

        // Stop if the input is invalid.
        if (scanf("%d", &ch) != 1) {
            puts("Invalid input.");
            return 1;
        }

        // Execute the selected option.
        handle_choice(ch);

    } while (ch != 0);

    return 0;
}
