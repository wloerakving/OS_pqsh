/* process.h: PQSH Process */

#ifndef PQSH_PROCESS_H
#define PQSH_PROCESS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define MAX_ARGUMENTS   1024

/* Structure */

#define MAX_COMMAND_LENGTH 256

typedef struct Process {
    pid_t pid;
    char command[MAX_COMMAND_LENGTH];
    double start_time;
    double arrival_time;
    double end_time;
    int remaining_time_slice;
    struct Process *next;  // Pointer to the next process in the queue
} Process;

/* Functions */

Process *   process_create(const char *command);
bool        process_start(Process *p);
bool        process_pause(Process *p);
bool        process_resume(Process *p);
bool        process_is_finished(Process *p);

#endif

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
