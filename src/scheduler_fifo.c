/* scheduler_fifo.c: PQSH FIFO Scheduler */

#include "pqsh/macros.h"
#include "pqsh/scheduler.h"

#include <assert.h>

/**
 * Schedule next process using fifo policy:
 *
 *  As long as we have less running processes than our number of CPUS and
 *  there are waiting processes, then we should move a process from the
 *  waiting queue to the running queue.
 *
 * @param   s	    Scheduler structure
 */
void scheduler_fifo(Scheduler *s) {
    /* TODO: Implement FIFO Policy */
    while (s->running.size <= s->cores && s->waiting.size > 0) {
	Process *poped = queue_pop(&s->waiting);
    if (poped) {
        // Start the process
        process_start(poped);
        queue_push(&s->running, poped);
    }
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
