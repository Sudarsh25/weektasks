/*
 * SPDX-License-Identifier: MIT
 * Author: Sree Sudarshan RV
 * Project: Linked List Implementation in C
 *
 * Description:
 * This program implements a singly linked list. It supports insertion of nodes
 * at the end and displays the entire list.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/weektasks/Codefile week1
 */

#include <stdio.h>
#include <stdlib.h>

// Define structure for linked list node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Insert a node at the end of the list
void insertEnd(Node **head, int val) {
    Node *new = malloc(sizeof(Node));  // Create a new node
    new->data = val;
    new->next = NULL;

    if (*head == NULL) {  // Empty list
        *head = new;
        return;
    }

    // Traverse to the end
    Node *temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = new;  // Link new node
}

// Display the list
void display(Node *head) {
    while (head) {
        printf("%d -> ", head->data); // Print node value
        head = head->next;
    }
    printf("NULL\n");
}

// Main function to test linked list
int main() {
    Node *head = NULL; // Start with empty list

    insertEnd(&head, 5);   // Insert 5
    insertEnd(&head, 10);  // Insert 10
    insertEnd(&head, 15);  // Insert 15

    display(head); // Output the list

    return 0;
}
