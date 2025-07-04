/*
 * SPDX-License-Identifier: MIT
 * Author: Sree Sudarshan RV
 * Project: Circular Buffer Implementation in C
 *
 * Description:
 * This code provides a basic implementation of a circular buffer (ring buffer)
 * in C using a fixed-size array. It supports enqueue and dequeue operations and
 * handles overflow and underflow conditions.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/weektasks/Codefile week1 
*/

#include <stdio.h>
#define SIZE 5  // Define the size of the circular buffer

typedef struct {
    int buffer[SIZE];  // Array to store elements
    int head;          // Index where new element will be inserted
    int tail;          // Index where element will be removed
    int count;         // Number of elements currently in buffer
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int enqueue(CircularBuffer *cb, int val) {
    if (cb->count == SIZE) return -1;  // Buffer full
    cb->buffer[cb->head] = val;        // Add value at head position
    cb->head = (cb->head + 1) % SIZE;  // Move head forward (wrap around)
    cb->count++;                       // Increase count
    return 0;                          // Success
}

int dequeue(CircularBuffer *cb, int *val) {
    if (cb->count == 0) return -1;     // Buffer empty
    *val = cb->buffer[cb->tail];       // Get value at tail position
    cb->tail = (cb->tail + 1) % SIZE;  // Move tail forward (wrap around)
    cb->count--;                       // Decrease count
    return 0;                          // Success
}

int main() {
    CircularBuffer cb;
    init(&cb);  // Initialize the buffer

    enqueue(&cb, 100);
    enqueue(&cb, 200);

    int val;

    if (dequeue(&cb, &val) == 0)
        printf("Dequeued: %d\n", val);

    if (dequeue(&cb, &val) == 0)
        printf("Dequeued: %d\n", val);

    return 0;
}
