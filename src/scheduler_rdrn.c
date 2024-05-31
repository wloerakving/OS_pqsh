/* scheduler_rdrn.c: PQSH Round Robin Scheduler */

#include "pqsh/macros.h"
#include "pqsh/scheduler.h"

#include <assert.h>

/**
 * Schedule next process using round robin policy:
 *
 *  1. If there no waiting processes, then do nothing.
 *
 *  2. Move one process from front of running queue and place in back of
 *  waiting queue.
 *
 *  3. Move one process from front of waiting queue and place in back of
 *  running queue.
 *
 * @param   s	    Scheduler structure
 **/
#define TIME_QUANTUM 4
void scheduler_rdrn(Scheduler *s) {
    /* TODO: Implement Round Robin Policy */
    // Process the running queue
    for (int i = 0; i < s->running.size; i++) {
        Process *current = queue_get(&s->running, i);

        // Check if the process has finished its current time slice
        if (current->remaining_time_slice == 0) {
            // Preempt the process
            process_pause(current);

            // Put it back into the waiting queue if it hasn't finished execution
            if (!process_is_finished(current)) {
                queue_push(&s->waiting, current);
            }

            // Remove it from the running queue
            queue_remove(&s->running, current->pid);
            i--;  // Adjust index due to removal
        }
    }

    // Fill the running queue if there are free cores and waiting processes
    while (s->running.size < s->cores && s->waiting.size > 0) {
        Process *poped = queue_pop(&s->waiting);
        if (poped) {
            // Resume the process if it was paused
            if (poped->remaining_time_slice < TIME_QUANTUM) {
                process_resume(poped);
            } else {
                process_start(poped);
            }

            // Set the initial or remaining time slice for the process
            poped->remaining_time_slice = TIME_QUANTUM;

            queue_push(&s->running, poped);
        }
    }

    // Decrease the remaining time slice for all running processes
    for (int i = 0; i < s->running.size; i++) {
        Process *current = queue_get(&s->running, i);
        current->remaining_time_slice--;
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
