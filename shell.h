#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 10
#define WELCOME_MESSAGE "Welcome to the ENSEA Shell.\nType 'exit' to quit.\n"
#define COMMAND_NOT_FOUND "Command not found.\n"
#define FORK_FAILED "Fork failed.\n"
#define EXIT_PROMPT "Bye bye...\n"
#define PROMPT "enseash"
// Exit and signal messages
#define EXIT_PREFIX "[exit:"
#define SIGNAL_PREFIX "[sign:"
#define TIME_SUFFIX "|%dms]%% "

// Function prototypes
void disp_welc_mes();
int read_command(char *command);
void execute_command(char *command, int *last_exit_status, bool *is_signal);
void displayPrompt(int last_exit_status, bool is_signal);

#endif // SHELL_H
