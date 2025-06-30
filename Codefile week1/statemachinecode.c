#include <stdio.h>

typedef enum {
    IDLE,
    SENDING,
    RECEIVING
} State;

typedef struct {
    State current;
} ChatState;

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

int main() {
    ChatState state = { IDLE };
    char events[] = {'s', 'r', 'x'};
    for (int i = 0; i < 3; i++) {
        printf("Event: %c => ", events[i]);
        handle_event(&state, events[i]);
    }
    return 0;
}

