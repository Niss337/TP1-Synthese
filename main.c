#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>  // Include this for bool type
#include "shell.h"
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1 // Define a value if not defined
#endif
int main() {
    char command[MAX_COMMAND_LENGTH]; // Buffer for user command
    int last_exit_status = 0; // Variable to store the last exit code
    bool is_signal = false; // Flag to indicate if the last exit was due to a signal
    struct timespec start, end; // Variables for measuring time

    disp_welc_mes(); // Display welcome message
    while (1) { // Infinite loop for REPL (read-eval-print loop)
        displayPrompt(last_exit_status, is_signal); // Display the prompt
        if (read_command(command)) { // Read user command
            write(STDOUT_FILENO, EXIT_PROMPT, strlen(EXIT_PROMPT));
            break; // Exit the shell
        }
         clock_gettime(CLOCK_MONOTONIC, &start); // Start the timer
        execute_command(command, &last_exit_status, &is_signal); // Execute the command
        clock_gettime(CLOCK_MONOTONIC, &end); // Stop the timer

        // Calculate execution time in milliseconds
        long elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
        last_exit_status = (last_exit_status << 8) | elapsed_ms; // Store the time in the exit code
    }
    return 0; // Exit the program
}
