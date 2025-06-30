#include <stdio.h>
#define SIZE 5

typedef struct {
    int buffer[SIZE];
    int head, tail, count;
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = cb->tail = cb->count = 0;
}

int enqueue(CircularBuffer *cb, int val) {
    if (cb->count == SIZE) return -1;
    cb->buffer[cb->head] = val;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
    return 0;
}

int dequeue(CircularBuffer *cb, int *val) {
    if (cb->count == 0) return -1;
    *val = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return 0;
}

int main() {
    CircularBuffer cb;
    init(&cb);
    enqueue(&cb, 100);
    enqueue(&cb, 200);
    int val;
    if (dequeue(&cb, &val) == 0) printf("Dequeued: %d\n", val);
    if (dequeue(&cb, &val) == 0) printf("Dequeued: %d\n", val);
    return 0;
}

