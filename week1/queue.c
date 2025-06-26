#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// Initialize
void initQueue(Queue *q) {
    q->front = -1; q->rear = -1;
}

// Enqueue
void enqueue(Queue *q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

// Dequeue
int dequeue(Queue *q) {
    if (q->front == -1 || q->front > q->rear) return -1;
    return q->items[q->front++];
}

