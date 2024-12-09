#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "shell.h"

int main() {
    char command[MAX_COMMAND_LENGTH];
    int last_exit_status = 0;
    bool is_signal = false;

    disp_welc_mes();
    while (1) {
        displayPrompt(last_exit_status, is_signal);
        if (read_command(command)) break;
 struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        execute_command(command, &last_exit_status, &is_signal);
        clock_gettime(CLOCK_MONOTONIC, &end);

        last_exit_status = ((last_exit_status & 0xFF00) | 
                            ((end.tv_sec - start.tv_sec) * 1000 + 
                            (end.tv_nsec - start.tv_nsec) / 1000000));
    }
    return 0;
}
