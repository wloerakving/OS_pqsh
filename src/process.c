/* process.c: PQSH Process */

#include "pqsh/macros.h"
#include "pqsh/process.h"
#include "pqsh/timestamp.h"

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

/**
 * Create new process structure given command.
 * @param   command     String with command to execute.
 * @return  Pointer to new process structure
 **/
Process *process_create(const char *command) {
    // Alocate memory for a new process structure
    Process *p = (Process *)malloc(sizeof(Process));
    if (!p) {
        perror("Malloc failed!");
	return NULL;
    }
    // Duplicated the command string and store it in the process structre
    strcpy(p->command, command);
    // Fork a new process from parrent process
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error occured, fork failed!");
	free(p);
	return NULL;
    } 
    else if (!pid) {
        char *argv[MAX_ARGUMENTS] = {0};
	int i = 0;
	for (char *token = strtok(command, " "); token; token = strtok(NULL, " "))
	    argv[i++] = token;
        execvp(argv[0], argv);
	perror("Execvp failed!");
	exit(EXIT_FAILURE);
    } 
    else {
	p->pid = pid;
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

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
