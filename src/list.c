/**
 * @file  : list.c
 * @brief : This file defines the functions declared in list.h
 */

#include "../include/list.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structs */

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head; // head of list
    ListNode *tail; // tail of list
    size_t length;  // list length
} List;

/* internal API */

/**
 * @brief Removes all nodes from a list
 *
 * @param[in,out] list List to clear
 *
 * @note The list itself remains allocated and can be reused
 */
static void list_clear(list_t list);

/**
 * @brief Creates a new list node
 *
 * @param[in] value Value to store in the new node
 *
 * @return A pointer to the newly created node, or NULL if allocation fails
 */
static ListNode *node_create(int value);

/**
 * @brief Removes the first or last occurrence of a given value
 *
 * @param[in,out] list List to modify
 * @param[in] value Value to remove
 * @param[in] last_match If true, removes the last occurrence; otherwise, removes the first
 *
 * @return true if an occurrence is found and removed, false otherwise
 *
 * @note Internal helper function, accessible only within this source file
 */
static bool remove_value(list_t list, int value, bool last_match);

/* Public API */

list_t list_create(void) {
    // Create an empty list and initialize all fields to zero
    return calloc(1, sizeof(List));
}

void list_destroy(list_t *list) {
    // Do nothing if the list pointer or the list itself is NULL
    if (list == NULL || *list == NULL) return;

    // Clear all nodes from the list
    list_clear(*list);

    // Free the memory allocated for the list
    free(*list);
    *list = NULL;
}

/* list state */

bool list_is_empty(const list_t list) {
    // Return true if the list is NULL or empty
    return !list || list->length == 0;
}

size_t list_length(const list_t list) {
    // Return the number of nodes in the list, or 0 if the list is NULL
    return !list ? 0 : list->length;
}

/* Internal helpers */

static void list_clear(list_t list) {
    // Do nothing if the list is NULL
    if (!list) return;

    // Free all nodes in the list
    ListNode *node = list->head;
    while (node != NULL) {
        ListNode *next = node->next;
        free(node);
        node = next;
    }

    // Reset the list to its empty state
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

static ListNode *node_create(int value) {
    // Allocate memory for a new node
    ListNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return NULL;

    // Initialize the new node
    node->value = value;
    node->next = NULL;

    return node;
}

/* Insertion */

bool list_push_front(list_t list, int value) {
    // Do nothing if the list is NULL
    if (!list) return false;

    // Create a new node
    ListNode *node = node_create(value);

    // Stop if memory allocation fails
    if (!node) return false;

    // Insert the new node at the beginning of the list
    node->next = list->head;
    list->head = node;

    // Update the tail if the list was empty
    if (!list->tail) list->tail = node;

    // Update the list length
    list->length++;

    return true;
}

bool list_push_back(list_t list, int value) {
    // Do nothing if the list is NULL
    if (!list) return false;

    // Create a new node
    ListNode *node = node_create(value);

    // Stop if memory allocation fails
    if (!node) return false;

    // Insert the new node at the end of the list
    if (!list->tail)
        list->head = node;
    else
        list->tail->next = node;

    // Update the tail
    list->tail = node;

    // update length
    list->length++;

    return true;
}

/* Removal */

bool list_pop_front(list_t list, int *out_value) {
    // Do nothing if the list is empty
    if (list_is_empty(list)) return false;

    // Store the first node
    ListNode *node = list->head;

    // Copy its value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the first node
    list->head = node->next;

    // Update the tail if the list becomes empty
    if (!list->head)
        list->tail = NULL;

    // Update the list length and free the removed node
    list->length--;
    free(node);

    return true;
}

bool list_pop_back(list_t list, int *out_value) {
    // Do nothing if the list is empty
    if (list_is_empty(list)) return false;

    // Store the last node
    ListNode *node = list->tail;

    // Copy its value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Handle the case where the list contains only one node
    if (list->head == node) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        // Find the node preceding the last node
        ListNode *previous = list->head;
        while (previous->next != node) {
            previous = previous->next;
        }

        // Remove the last node and update the tail
        previous->next = NULL;
        list->tail = previous;
    }

    // Update the list length and free the removed node
    list->length--;
    free(node);

    return true;
}

static bool remove_value(list_t list, int value, bool last_match) {
    // Do nothing if the list is empty
    if (list_is_empty(list)) return false;

    // Initialize pointers to track the matching node and its predecessor
    ListNode *match = NULL;
    ListNode *match_previous = NULL;
    ListNode *previous = NULL;

    // Search for the first or last occurrence of the value
    for (ListNode *node = list->head; node != NULL; node = node->next) {
        if (node->value == value) {
            match = node;
            match_previous = previous;

            // Stop at the first match if requested
            if (!last_match) break;
        }
        previous = node;
    }

    // Stop if the value is not found
    if (!match) return false;

    // Remove the matching node from the list
    if (!match_previous)
        list->head = match->next;
    else
        match_previous->next = match->next;

    // Update the tail if the last node is removed
    if (list->tail == match)
        list->tail = match_previous;

    // Update the list length and free the removed node
    list->length--;
    free(match);

    return true;
}

bool list_remove_first(list_t list, int value) {
    // Remove the first occurrence of the given value
    return remove_value(list, value, false);
}

bool list_remove_last(list_t list, int value) {
    // Remove the last occurrence of the given value
    return remove_value(list, value, true);
}

/* utilities */
void list_print(const list_t list) {
    // Print the opening bracket
    putchar('[');

    // Print all values separated by commas
    if (list) {
        for (
            const ListNode *node = list->head;
            node != NULL;
            node = node->next
        ) {
            printf("%d%s", node->value, node->next == NULL ? "" : ", ");
        }
    }

    // Print the closing bracket and a newline
    puts("]");
}
