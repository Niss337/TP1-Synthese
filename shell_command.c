#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "shell.h"

// Function to parse the command into arguments and handle redirections
void parse_command(char *command, char **arguments, char **input_file, char **output_file) {
    *input_file = NULL;
    *output_file = NULL;
    char *token;
    int index = 0;
    token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            *output_file = strtok(NULL, " "); // Get the output file
        } else if (strcmp(token, "<") == 0) {
            *input_file = strtok(NULL, " "); // Get the input file
        } else {
            arguments[index++] = token; // Store command arguments
        }
        token = strtok(NULL, " ");
         }
    arguments[index] = NULL; // Null terminate the arguments array
}

// Function to execute the command in a child process
void run_command(char **arguments, char *input_file, char *output_file) {
    if (output_file) {
         freopen(output_file, "w", stdout); // Redirect output
    }
    if (input_file) {
        freopen(input_file, "r", stdin); // Redirect input
    }
    execvp(arguments[0], arguments); // Execute the command
    perror("Command not found"); // Error if command execution fails
    exit(1);
} // Main function to execute a command
void execute_command(char *command, int *last_exit_status, bool *is_signal, long *exec_time) {
    char *arguments[MAX_ARGS];
    char *input_file, *output_file;

    parse_command(command, arguments, &input_file, &output_file); // Parse the command

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Start timing
      pid_t process_id = fork(); // Create a new process
    if (process_id < 0) {
        perror("Fork failed"); // Error handling for fork failure
        return;
    }

    if (process_id == 0) { // Child process
        run_command(arguments, input_file, output_file); // Run the command
    } else { // Parent process
        int status;
         waitpid(process_id, &status, 0); // Wait for child to finish
        clock_gettime(CLOCK_MONOTONIC, &end); // End timing

        // Calculate execution time
        *exec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
  // Check how the child process terminated
        if (WIFEXITED(status)) {
            *last_exit_status = WEXITSTATUS(status); // Get exit status
            *is_signal = false; // Not terminated by signal
        } else if (WIFSIGNALED(status)) {
            *last_exit_status = WTERMSIG(status); // Get signal number
            *is_signal = true; // Terminated by signal
        }
    }
}
