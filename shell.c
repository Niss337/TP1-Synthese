#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // Include for clock_gettime
#include "shell.h"


void disp_welc_mes() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

int read_command(char *command) {
    printf(" %s%% ", PROMPT);
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) return 1;
    command[strcspn(command, "\n")] = 0;
    return strcmp(command, "exit") == 0;
}   void displayPrompt(int last_exit_status, bool is_signal) {
    printf(" %s%s%d|%dms]%% ", PROMPT, 
           is_signal ? SIGNAL_PREFIX : EXIT_PREFIX, 
           (last_exit_status >> 8) & 0xFF, 
           last_exit_status & 0xFF);
}
void execute_command(char *command, int *last_exit_status, bool *is_signal) {
    pid_t pid = fork();
    if (pid < 0) {
        write(STDERR_FILENO, FORK_FAILED, strlen(FORK_FAILED));
        return;
    }
    if (pid == 0) {
        char *args[MAX_ARGS];
        int index = 0;
        for (char *token = strtok(command, " "); token && index < MAX_ARGS - 1; token++) {
            args[index++] = token;
        } }
        args[index] = NULL;
        if (execvp(args[0], args) == -1) {
            write(STDERR_FILENO, COMMAND_NOT_FOUND, strlen(COMMAND_NOT_FOUND));
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        *last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status);
        *is_signal = WIFSIGNALED(status);
    }
}
