/* scheduler_sjf.c: PQSH SJF Scheduler */

#include "pqsh/macros.h"
#include "pqsh/scheduler.h"

#include <assert.h>

void sort_queue_by_remaining_time_slice(Queue *queue) {
    if (queue->size < 2) {
        return; // No need to sort if the queue has less than 2 processes
    }

    bool swapped;
    do {
        swapped = false;
        Process **current = &(queue->head);

        while ((*current)->next != NULL) {
            Process *a = *current;
            Process *b = a->next;

            if (a->remaining_time_slice < b->remaining_time_slice) {
                *current = b;
                a->next = b->next;
                b->next = a;
                swapped = true;
            }
            current = &((*current)->next);
        }
    } while (swapped);
}

/**
 * Schedule next process using sjf policy:
 *
 *  As long as we have less running processes than our number of CPUS and
 *  there are waiting processes, then we should move a process from the
 *  waiting queue to the running queue.
 *
 * @param   s       Scheduler structure
 */
void scheduler_sjf(Scheduler *s) {
    /* Implement SJF Policy */
    sort_queue_by_remaining_time_slice(&(s->waiting));
    scheduler_fifo(s);
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
