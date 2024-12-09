#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shell.h"

int main() {
    char command[MAX_COMMAND_LENGTH];
    int last_exit_status = 0; // Variable to store the last command's exit status
    bool is_signal = false; // Track if the last command was terminated by a signal
    long exec_time = 0; 
    disp_welc_mes();

    while (1) {
        displayPrompt(last_exit_status, is_signal, exec_time);
        if (read_command(command)) break;
         execute_command(command, &last_exit_status, &is_signal, &exec_time);
    }
    write(STDOUT_FILENO, EXIT_PROMPT, strlen(EXIT_PROMPT));
    return 0;
}
