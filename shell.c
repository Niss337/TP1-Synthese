#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // Include for clock_gettime
#include "shell.h"
// Function to display the welcome message
void disp_welc_mes() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

// Function to read the command from user input
int read_command(char *command) {
    printf(" %s%% ", PROMPT); // Custom prompt format
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        return 1; // Return non-zero if reading fails
    }
    command[strcspn(command, "\n")] = 0; // Remove newline character
    return strcmp(command, "exit") == 0; // Return true if the user typed "exit"
}

// Function to display the prompt with exit status or signal and execution time
void displayPrompt(int last_exit_status, bool is_signal) {
    int elapsed_time = last_exit_status & 0xFF;     // Extract execution time
    int exit_code = (last_exit_status >> 8) & 0xFF; // Extract the exit code
      if (is_signal) {
        printf(" %s[sign:%d|%dms]%% ", PROMPT, exit_code, elapsed_time);
    } else {
        printf(" %s[exit:%d|%dms]%% ", PROMPT, exit_code, elapsed_time);
    }
}
// Function to execute a command
void execute_command(char *command, int *last_exit_status, bool *is_signal) {
    pid_t process_id = fork(); // Create a new process

    if (process_id < 0) {
        write(STDERR_FILENO, FORK_FAILED, strlen(FORK_FAILED)); // Error handling for fork failure
        return;
    }
     if (process_id == 0) { // Child process
        char *arguments[MAX_ARGS];
        char *token = strtok(command, " ");
        int index = 0;
        
        // Tokenize the command input into arguments
        while (token != NULL && index < MAX_ARGS - 1) {
            arguments[index++] = token; // Store each argument
            token = strtok(NULL, " ");  // Get the next token
        }
        arguments[index] = NULL; // Null-terminate the array
        // Execute the command
        if (execvp(arguments[0], arguments) == -1) {
            write(STDERR_FILENO, COMMAND_NOT_FOUND, strlen(COMMAND_NOT_FOUND)); // Error handling
            exit(1); // Exit child process if exec fails
        }
    } else { // Parent process
     int status;
        waitpid(process_id, &status, 0); // Wait for child to finish
        if (WIFEXITED(status)) {
            *last_exit_status = WEXITSTATUS(status);
            *is_signal = false;
        } else if (WIFSIGNALED(status)) {
            *last_exit_status = WTERMSIG(status);
            *is_signal = true;
        }
    }
}