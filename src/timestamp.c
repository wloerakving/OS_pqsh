/* timestamp.c: PQSH Timestamp */

#include "pqsh/timestamp.h"

#include <time.h>
#include <sys/time.h>

/**
 * Return current timestamp as a double.
 *
 * Utilizes gettimeofday for precision (accounting for seconds and
 * microseconds) and falls back to time (only account for seconds) if that
 * fails.
 *
 * @return  Double representing the current time.
 **/
double timestamp() {
    /* Implement */
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
         return tv.tv_sec + tv.tv_usec / (double)1e6;
    } else {
        time_t t = time(NULL);
	return (double)t;
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
