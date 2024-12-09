#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shell.h"

int main()
{
    char command[MAX_COMMAND_LENGTH];
    int last_exit_status = 0; // Variable to store the last command's exit status
    bool is_signal = false;// track if the last command was terminated by a signal
    disp_welc_mes();
    while (1) {
        displayPrompt(last_exit_status, is_signal);
        if (read_command(command)) break;

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start); // Start the timer to record when the command execution begins
        execute_command(command, &last_exit_status, &is_signal);
        clock_gettime(CLOCK_MONOTONIC, &end);
        // Update the last exit status to include execution time in milliseconds
         last_exit_status = (last_exit_status & 0xFF00) | 
                           ((end.tv_sec - start.tv_sec) * 1000 + 
                            (end.tv_nsec - start.tv_nsec) / 1000000);
    }
    return 0;
}
