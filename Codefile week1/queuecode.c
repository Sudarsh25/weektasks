/*
 * SPDX-License-Identifier: MIT
 * Author: Sree Sudarshan RV
 * Project: Queue Implementation in C
 *
 * Description:
 * This program implements a linear queue using an array. It supports enqueue and dequeue
 * operations and demonstrates FIFO (First-In First-Out) behavior.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/weektasks/Codefile week1
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define maximum queue size

// Define Queue structure
typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Add an element to the queue
void enqueue(Queue *q, int value) {
    if (q->rear == MAX - 1) return;  // Queue is full
    if (q->front == -1) q->front = 0; // First element
    q->items[++q->rear] = value;
}

// Remove and return front element from queue
int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) return -1; // Queue is empty
    return q->items[q->front++];
}

// Main function to test queue
int main() {
    Queue q;
    initQueue(&q); // Initialize the queue

    enqueue(&q, 10);  // Add 10
    enqueue(&q, 20);  // Add 20

    // Remove and print elements
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    return 0;
}
