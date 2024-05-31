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
    if (queue & RUNNING) {
        printf("Running Queue:\n");
        queue_dump(&s->running);
    }
    if (queue & WAITING) {
        printf("Waiting Queue:\n");
        queue_dump(&s->waiting);
    }
    if (queue & FINISHED) {
        printf("Finished Queue:\n");
        queue_dump(&s->finished);
    }

    // Display overall metrics
    printf("Running = %4lu, Waiting = %4lu, Finished = %4lu, Turnaround = %05.2lf, Response = %05.2lf\n",
        s->running.size, s->waiting.size, s->finished.size, s->total_turnaround_time, s->total_response_time);
    // printf("Running = %4lu, Waiting = %4lu, Finished = %4lu, Turnaround = %05.2lf, Response = %05.2lf\n",
	// 	    0, s->waiting.size, 0, 0.0, 0.0);
    /* TODO: Complement implementation. */
}

/**
 * Schedule next process using appropriate policy.
 * @param   s	    Pointer to Scheduler structure.
 **/
void scheduler_next(Scheduler *s) {

    /* Dispatch to appropriate scheduler function. */
    // printf("Scheduler policy: %d\n", s->policy);
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
    int status;
    pid_t pid;
    // printf("in the wait sheduler");
    // Wait for any child process to change state without blocking
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            // Remove the process from the running queue and update metrics
            Process *process = queue_remove(&s->running, pid);
            // if (process == NULL)
            // {
            //     printf("Running queue is empty");
            // }
            if (process) {
                // printf('hi');
                process->end_time = timestamp();
                // Calculate metrics
                s->total_turnaround_time += process->end_time - process->arrival_time;
                s->total_response_time += process->start_time - process->arrival_time;
                // printf("moving to finish");
                // Move the process to the finished queue
                queue_push(&s->finished, process);
                // printf("Process %d finished, moved to finished queue\n", pid);
            }
        }
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
