/*
 * SPDX-License-Identifier: MIT
 * Author: Sree Sudarshan RV
 * Project: Event-driven State Machine in C
 *
 * Description:
 * This program simulates a simple state machine with three states: IDLE, SENDING, and RECEIVING.
 * Based on character input events, it transitions between states and prints actions.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/weektasks/Codefile week1
 */

#include <stdio.h>

// Define state values
typedef enum {
    IDLE,
    SENDING,
    RECEIVING
} State;

// Structure to hold current state
typedef struct {
    State current;
} ChatState;

// Event handler to change states based on input
void handle_event(ChatState *state, char event) {
    switch (state->current) {
        case IDLE:
            if (event == 's') {
                printf("Sending...\n");
                state->current = SENDING;
            } else if (event == 'r') {
                printf("Receiving...\n");
                state->current = RECEIVING;
            }
            break;
        case SENDING:
        case RECEIVING:
            printf("Back to IDLE\n");
            state->current = IDLE;
            break;
    }
}

// Main function to simulate events
int main() {
    ChatState state = { IDLE }; // Start from IDLE state
    char events[] = {'s', 'r', 'x'}; // Simulated inputs

    for (int i = 0; i < 3; i++) {
        printf("Event: %c => ", events[i]);
        handle_event(&state, events[i]);  // Trigger state change
    }

    return 0;
}
