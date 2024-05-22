/* scheduler.c: PQSH Scheduler */

#include "pqsh/macros.h"
#include "pqsh/scheduler.h"
#include "pqsh/timestamp.h"

#include <errno.h>
#include <sys/wait.h>

/**
 * Add new command to waiting queue.
 * @param   s	    Pointer to Scheduler structure.
 * @param   fs      File stream to write to. (File *fs)
 * @param   command Command string for new Process.
 **/
void scheduler_add(Scheduler *s, const char *command) {

    Process *process = process_create(command);
    queue_push(&s->waiting, process);    
    printf("Added process \"bin/worksim%s\" to waiting queue.\n", command);
}

/**
 * Display status of queues in Scheduler.
 * @param   s	    Pointer to Scheduler structure.
 * @param   fs      File stream to write to.
 * @param   queue   Bitmask specifying which queues to display.
 **/
void scheduler_status(Scheduler *s, int queue) {

    printf("Running = %4lu, Waiting = %4lu, Finished = %4lu, Turnaround = %05.2lf, Response = %05.2lf\n",
		    0, s->waiting.size, 0, 0.0, 0.0);
    /* TODO: Complement implementation. */
}

/**
 * Schedule next process using appropriate policy.
 * @param   s	    Pointer to Scheduler structure.
 **/
void scheduler_next(Scheduler *s) {

    /* Dispatch to appropriate scheduler function. */
    switch (s->policy) {
    case FIFO_POLICY:
         scheduler_fifo(s);
         break;
    case RDRN_POLICY:
         scheduler_rdrn(s);
         break;
    default:
         perror("Unknown scheduling policy\n");
         break;
    }
}

/**
 * Wait for any children and remove from queues and update metrics.
 * @param   s	    Pointer to Scheduler structure.
 **/
void scheduler_wait(Scheduler *s) {
    /* TODO: Wait for any children without blocking:
     *
     *  - Remove process from queues.
     *  - Update Process metrics.
     *  - Update Scheduler metrics.
     **/
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
