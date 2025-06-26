#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insertEnd(Node **head, int val) {
    Node *new = malloc(sizeof(Node));
    new->data = val;
    new->next = NULL;
    if (*head == NULL) { *head = new; return; }

    Node *temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = new;
}

