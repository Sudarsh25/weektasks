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
            state->current = IDLE;
            break;
    }
}

