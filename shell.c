#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include "shell.h"

// the welcome message 
void disp_welc_mes() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}
int read_command(char *command) {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    if (read(STDIN_FILENO, command, MAX_COMMAND_LENGTH) <= 0) return 1; // return 1 if reading fails
    command[strcspn(command, "\n")] = 0; // Remove the newline character from the end of the command input
                                     // This is necessary because the input from 'read' includes the newline character when the user presses Enter.
    return strcmp(command, "exit") == 0;
}
void displayPrompt(int last_exit_status, bool is_signal) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s%s%d]%% ", 
             PROMPT, 
             is_signal ? SIGNAL_PREFIX : EXIT_PREFIX, 
             last_exit_status);
    write(STDOUT_FILENO, buffer, strlen(buffer));  // Output the formatted prompt to stdout to inform the user of the shell's state
}
void execute_command(char *command, int *last_exit_status, bool *is_signal) {
    pid_t pid = fork(); // Create a new child process; this duplicates the current process
    if (pid < 0) {
        // If fork fails, output an error message to stderr
        write(STDERR_FILENO, FORK_FAILED, strlen(FORK_FAILED));
        return;
    }
    if (pid == 0) {
        char *args[MAX_ARGS];
        int index = 0;
        // Tokenize the command string into individual arguments for execution
        for (char *token = strtok(command, " "); token && index < MAX_ARGS - 1; token++) {
            args[index++] = token;
        }
         args[index] = NULL; // Terminate the list
        if (execvp(args[0], args) == -1) {
            write(STDERR_FILENO, COMMAND_NOT_FOUND, strlen(COMMAND_NOT_FOUND));
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        *last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        *is_signal = WIFSIGNALED(status);
    }
}
