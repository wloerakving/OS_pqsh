/* process.c: PQSH Process */

#include "pqsh/macros.h"
#include "pqsh/process.h"
#include "pqsh/timestamp.h"

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Create new process structure given command.
 * @param   command     String with command to execute.
 * @return  Pointer to new process structure
 **/

Process *process_create(const char *command) {
    // Allocate memory for a new process structure
    Process *p = (Process *)malloc(sizeof(Process));
    if (!p) {
        perror("Malloc failed!");
        return NULL;
    }
    // Duplicate the command string and store it in the process structure
    strncpy(p->command, command, MAX_COMMAND_LENGTH - 1);
    p->command[MAX_COMMAND_LENGTH - 1] = '\0';  // Ensure null-termination

    // Fork a new process from parent process
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error occurred, fork failed!");
        free(p);
        return NULL;
    } else if (pid == 0) {
        // Child process
        char *argv[MAX_ARGUMENTS] = {0};
        int i = 0;
        char command_copy[MAX_COMMAND_LENGTH];
        strncpy(command_copy, command, MAX_COMMAND_LENGTH);
        for (char *token = strtok(command_copy, " "); token; token = strtok(NULL, " "))
            argv[i++] = token;
        execvp(argv[0], argv);
        perror("Execvp failed!");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        p->pid = pid;
        p->remaining_time_slice = 0;
        p->arrival_time = timestamp();
    }
    return p;
}

/**
 * Start process by forking and executing the command.
 * @param   p           Pointer to Process structure.
 * @return  Whether or not starting the process was successful
 **/
bool process_start(Process *p) {
    p->start_time = timestamp();
    return kill(p->pid, SIGCONT) == 0;
}

/**
 * Pause process by sending it the appropriate signal.
 * @param   p           Pointer to Process structure.
 * @return  Whether or not sending the signal was successful.
 **/
bool process_pause(Process *p) {
    return kill(p->pid, SIGSTOP) == 0;
}

/**
 * Resume process by sending it the appropriate signal.
 * @param   p           Pointer to Process structure.
 * @return  Whether or not sending the signal was successful.
 **/
bool process_resume(Process *p) {
    return kill(p->pid, SIGCONT) == 0;
}

/**
 * Check if a process has finished.
 * @param   p           Pointer to Process structure.
 * @return  Whether or not the process has finished
 **/
bool process_is_finished(Process *p) {
    int status;
    pid_t result = waitpid(p->pid, &status, WNOHANG);
    if (result == 0) {
        return false;  // Process is still running
    } else if (result == -1) {
        perror("waitpid");
        return false;
    } else {
        p->end_time = timestamp();
        return true;  // Process has finished
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
