#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <unistd.h>  

// Constants for shell messages and prompts
#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 10
#define WELCOME_MESSAGE "Welcome to the ENSEA Shell.\nType 'exit' to quit.\n"
#define COMMAND_NOT_FOUND "Command not found.\n"
#define FORK_FAILED "Fork failed.\n"
#define EXIT_PROMPT "Goodbye...\n"
#define PROMPT "enseash % "
#define EXIT_PREFIX "[exit:"
#define SIGNAL_PREFIX "[sign:"
#define TIME_SUFFIX "|%ldms]%% "

// Function prototypes
void disp_welc_mes();
int read_command(char *command);
void displayPrompt(int last_exit_status, bool is_signal, long exec_time);
void execute_command(char *command, int *last_exit_status, bool *is_signal, long *exec_time);
void handle_cd(char *path, int *last_exit_status);

#endif // SHELL_H
