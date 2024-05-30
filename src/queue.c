/* queue.c: PQSH Queue */

#include "pqsh/macros.h"
#include "pqsh/queue.h"

#include <assert.h>

/**
 * Push process to back of queue.
 * @param q     Pointer to Queue structure.
 **/
void        queue_push(Queue *q, Process *p) {
    /* Implement */
    if (q->size == 0) {
        q->tail = p;
	q->head = p;
    } else {
	q->tail->next = p;
	q->tail = p;
    }
    q->size++;
    // arrival_time

}

/**
 * Pop process from front of queue.
 * @param q     Pointer to Queue structure.
 * @return  Process from front of queue.
 **/
Process *   queue_pop(Queue *q) {
    /* Implement */
	Process * tmp = q->head;
	if (q->size > 0) {
            q->head = q->head->next; 
            q->size--;
	    return tmp;
        }	    

        return NULL; // Return NULL if the queue is empty
}

/**
 * Remove and return process with specified pid.
 * @param q     Pointer to Queue structure.
 * @param pid   Pid of process to return.
 * @return  Process from Queue with specified pid.
 **/
Process *   queue_remove(Queue *q, pid_t pid) {
    // /* Implement */
    // Process * tmp = q->head;
    // Process * toremove;
    // while (tmp->next->pid != pid) {
    //     continue;
    // }
    // toremove = tmp->next;
    // tmp->next = tmp->next->next;
    // return toremove;
    if (q->size == 0) return NULL;

    Process *prev = NULL;
    Process *current = q->head;
    while (current != NULL) {
        if (current->pid == pid) {
            if (prev == NULL) {
                q->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == q->tail) {
                q->tail = prev;
            }
            q->size--;
            return current;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

/**
 * Dump the contents of the Queue to the specified stream.
 * @param q     Queue structure.
 * @param fs    Output file stream.
 **/
void        queue_dump(Queue *q) {
    // printf("%6s %-30s %-13s %-13s %-13s\n", 
    //             "PID", "COMMAND", "ARRIVAL", "START", "END"); 
    /* TODO Display information for each item in Queue. */
    Process *current = q->head;
    while (current != NULL) {
        printf("%6d %-30s %-13.6lf %-13.6lf %-13.6lf\n",
            current->pid, current->command, current->arrival_time, current->start_time, current->end_time);
        current = current->next;
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
