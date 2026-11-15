/**
 * @file list.c
 * @brief Implements the public linked list interface declared in list.h.
 * @todo Implement an iterator.
 */

#include "../include/ds/list.h"

#include <stdio.h>
#include <stdlib.h>

/* Internal structures */

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head; // Pointer to the first node
    ListNode *tail; // Pointer to the last node
    size_t size;    // Number of nodes in the list
} List;

/* Internal API */

/**
 * @brief Removes all nodes from a list.
 *
 * @param[in,out] list List to clear.
 *
 * @note The list itself remains allocated and can be reused.
 */
static void ds_list_clear(ds_list_t list);

/**
 * @brief Creates a new list node.
 *
 * @param[in] value Value to store in the new node.
 *
 * @return A newly allocated node, or NULL if memory allocation fails.
 */
static ListNode *ds_node_create(int value);

/**
 * @brief Removes the first or last occurrence of a given value.
 *
 * @param[in,out] list List to modify.
 * @param[in] value Value to remove.
 * @param[in] last_match Whether to remove the last occurrence instead of the first.
 *
 * @return true if an occurrence is found and removed; false otherwise.
 *
 * @note This helper is private to this source file.
 */
static bool ds_list_remove(ds_list_t list, int value, bool last_match);

/* Lifecycle */

ds_list_t ds_list_create(void) {
    // Allocate a new list and initialize all fields to zero
    return calloc(1, sizeof(List));
}

void ds_list_destroy(ds_list_t *list) {
    // Do nothing if the list pointer or the list itself is NULL
    if (list == NULL || *list == NULL) return;

    // Remove all nodes from the list
    ds_list_clear(*list);

    // Free the list structure
    free(*list);
    *list = NULL;
}

/* List state */

bool ds_list_empty(const ds_list_t list) {
    // Return true if the list is NULL or contains no nodes
    return !list || list->size == 0;
}

size_t ds_list_size(const ds_list_t list) {
    // Return the number of nodes, or 0 if the list is NULL
    return !list ? 0 : list->size;
}

/* Internal helpers */

static void ds_list_clear(ds_list_t list) {
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
    list->size = 0;
}

static ListNode *ds_node_create(int value) {
    // Allocate memory for a new node
    ListNode *node = malloc(sizeof(*node));

    // Stop if memory allocation fails
    if (!node) return NULL;

    // Initialize the node fields
    node->value = value;
    node->next = NULL;

    return node;
}

/* Insertion */

bool ds_list_push_front(ds_list_t list, int value) {
    // Reject a NULL list
    if (!list) return false;

    // Create a new node
    ListNode *node = ds_node_create(value);

    // Stop if memory allocation fails
    if (!node) return false;

    // Insert the new node at the beginning of the list
    node->next = list->head;
    list->head = node;

    // Update the tail if the list was empty
    if (!list->tail) list->tail = node;

    // Increment the list size
    list->size++;

    return true;
}

bool ds_list_push_back(ds_list_t list, int value) {
    // Reject a NULL list
    if (!list) return false;

    // Create a new node
    ListNode *node = ds_node_create(value);

    // Stop if memory allocation fails
    if (!node) return false;

    // Insert the new node at the end of the list
    if (!list->tail)
        list->head = node;
    else
        list->tail->next = node;

    // Update the tail pointer
    list->tail = node;

    // Increment the list size
    list->size++;

    return true;
}

/* Removal */

bool ds_list_pop_front(ds_list_t list, int *out_value) {
    // Stop if the list is NULL or empty
    if (ds_list_empty(list)) return false;

    // Store a pointer to the first node
    ListNode *node = list->head;

    // Copy the node value if an output pointer is provided
    if (out_value)
        *out_value = node->value;

    // Remove the first node
    list->head = node->next;

    // Update the tail if the list becomes empty
    if (!list->head)
        list->tail = NULL;

    // Decrement the list size and free the removed node
    list->size--;
    free(node);

    return true;
}

bool ds_list_pop_back(ds_list_t list, int *out_value) {
    // Stop if the list is NULL or empty
    if (ds_list_empty(list)) return false;

    // Store a pointer to the last node
    ListNode *node = list->tail;

    // Copy the node value if an output pointer is provided
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

        // Detach the last node and update the tail
        previous->next = NULL;
        list->tail = previous;
    }

    // Decrement the list size and free the removed node
    list->size--;
    free(node);

    return true;
}

static bool ds_list_remove(ds_list_t list, int value, bool last_match) {
    // Stop if the list is NULL or empty
    if (ds_list_empty(list)) return false;

    // Track the matching node and its predecessor
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

    // Unlink the matching node from the list
    if (!match_previous)
        list->head = match->next;
    else
        match_previous->next = match->next;

    // Update the tail if the last node is removed
    if (list->tail == match)
        list->tail = match_previous;

    // Decrement the list size and free the removed node
    list->size--;
    free(match);

    return true;
}

bool ds_list_remove_first(ds_list_t list, int value) {
    // Remove the first occurrence of the given value
    return ds_list_remove(list, value, false);
}

bool ds_list_remove_last(ds_list_t list, int value) {
    // Remove the last occurrence of the given value
    return ds_list_remove(list, value, true);
}

/* Utilities */

// void ds_list_print(const ds_list_t list) {
//     // Print the opening bracket
//     putchar('[');

//     // Print all values separated by commas
//     if (list) {
//         for (
//             const ListNode *node = list->head;
//             node != NULL;
//             node = node->next
//         ) {
//             printf("%d%s", node->value, node->next == NULL ? "" : ", ");
//         }
//     }

//     // Print the closing bracket and a newline
//     puts("]");
// }
