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
    while (((&s->waiting)->size) > 0 || ((&s->running)->size) > 0) {
        Process *process = queue_pop(&s->waiting);
        if (process) {
            process_start(process);
            process->start_time = timestamp();
            queue_push(&s->running, process);
        }

        for (int i = 0; i < ((&s->running)->size); i++) {
            process = queue_pop(&s->running);
            if (process->remaining_time_slice > 0) {
                process_resume(process);
                sleep(TIME_QUANTUM);
                process_pause(process);
                process->remaining_time_slice -= TIME_QUANTUM;
            }

            if (process_is_finished(process)) {
                process->end_time = timestamp();
                s->total_turnaround_time += process->end_time - process->arrival_time;
                s->total_response_time += process->start_time - process->arrival_time;
                free(process);
            } else {
                queue_push(&s->running, process);
            }
        }
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
