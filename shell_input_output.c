#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void disp_welc_mes() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

// Read command from user input
int read_command(char *command) {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    if (read(STDIN_FILENO, command, MAX_COMMAND_LENGTH) <= 0) return 1; // Return 1 if reading fails
    command[strcspn(command, "\n")] = 0; // Remove the newline character
     // This is necessary because the input from 'read' includes the newline character when the user presses Enter.
    return strcmp(command, "exit") == 0;
}
// Display the prompt
void displayPrompt(int last_exit_status, bool is_signal, long exec_time) {
    char buffer[256];
    if (is_signal) {
        snprintf(buffer, sizeof(buffer), "%s%s%d|%ldms]%% ", PROMPT, SIGNAL_PREFIX, last_exit_status, exec_time);
    } else {
        snprintf(buffer, sizeof(buffer), "%s%s%d|%ldms]%% ", PROMPT, EXIT_PREFIX, last_exit_status, exec_time);
    }
    write(STDOUT_FILENO, buffer, strlen(buffer));
}
