/* queue.c: PQSH Queue */

#include "pqsh/macros.h"
#include "pqsh/queue.h"

#include <assert.h>

/**
 * Push process to back of queue.
 * @param q     Pointer to Queue structure.
 **/
void        queue_push(Queue *q, Process *p) {
    if (q->size == 0) {
        q->tail = p;
        q->head = p;
    } else {
        q->tail->next = p;
        q->tail = p;
    }
    q->size++;
}

/**
 * Pop process from front of queue.
 * @param q     Pointer to Queue structure.
 * @return  Process from front of queue.
 **/
Process *queue_pop(Queue *q) {
    if (q->size == 0) return NULL;
    Process *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    q->size--;
    return tmp;
}

/**
 * Remove and return process with specified pid.
 * @param q     Pointer to Queue structure.
 * @param pid   Pid of process to return.
 * @return  Process from Queue with specified pid.
 **/
Process *   queue_remove(Queue *q, pid_t pid) {
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
    /* Display information for each item in Queue. */
    Process *current = q->head;
    while (current != NULL) {

        printf("%6s %-30s %-18.6s %-8.6s %13.6s\n", "PID", " COMMAND", "ARRIVAL", "START", "END");
        printf("%6d %-30s %-13.6lf %-13.6lf %-13.6lf\n",
            current->pid, current->command, current->arrival_time, current->start_time, current->end_time);
        
	current = current->next;
    }
}
/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
