/* pqsh.c: Process Queue Shell */

#include "pqsh/macros.h"
#include "pqsh/options.h"
#include "pqsh/scheduler.h"
#include "pqsh/signal.h"

#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <ctype.h>
#include <unistd.h>

/* Global Variables */

Scheduler PQShellScheduler = {
    .policy    = FIFO_POLICY,
    .cores     = 1,
    .timeout   = 250000,
};

/* Help Message */

void help() {
    printf("Commands:\n");
    printf("  add    command    Add command to waiting queue.\n");
    printf("  status [queue]    Display status of specified queue (default is all).\n");
    printf("  help              Display help message.\n");
    printf("  exit|quit         Exit shell.\n");
}

/* Add Worksim Command*/
void add(Scheduler *s, char arg[]) {
    scheduler_add(s, arg);
}

/* Status Command */
void status(Scheduler *s, char arg[]) {
    
    int queue = 0;
    
    if (streq(arg, "running"))
        queue = RUNNING;
    else if (streq(arg, "finished"))
        queue = FINISHED;
    else if (streq(arg, "waiting"))
	queue = WAITING;
    scheduler_status(s, queue);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    Scheduler *s = &PQShellScheduler;

    /* Parse command line options */
    if (!parse_command_line_options(argc, argv, s)) {
        EXIT_FAILURE;
    }

    /* Register signal handlers */
    signal_register(SIGALRM, 0, sigalrm_handler);
    
    /* Start timer interrupt */
    struct itimerval timer;

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
	exit(EXIT_FAILURE);
    }
    /* Process shell comands */
    while (!feof(stdin)) {
        char command[BUFSIZ]  = "";
        char argument[BUFSIZ] = "";

        printf("\nPQSH> ");

        while (!fgets(command, BUFSIZ, stdin) && !feof(stdin));
	
        chomp(command);
        
        /* Handle add and status commands */
        if (streq(command, "help")) {
            help();
        } else if (streq(command, "exit") || streq(command, "quit")) {
            break;
        } else if (!strncmp(command, "status", 5)) {
		strcpy(argument, &command[7]);
		status(s, argument);
	} else if (!strncmp(command, "add bin/worksim", 14)) {
                strcpy(argument, &command[4]);
		add(s, argument);
	} else if (strlen(command)) {
            printf("Unknown command: %s\n", command);
        }
	// Suspend a program until a signal is caught
        // pause();
    }

    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
