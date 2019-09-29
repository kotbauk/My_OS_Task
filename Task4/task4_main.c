#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR_BUFFER_LEN 256

static char err_buf[ERROR_BUFFER_LEN];
void* thread_routine(void* arg);
int main(void) {
    pthread_t thread;
    int err;
    void* thread_result;
    err = pthread_create(&thread, NULL, thread_routine, NULL);
    if (err != 0) {
        strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
        fprintf(stderr, "Error with pthread_create: %s\n", err_buf);
        return (EXIT_FAILURE);
    }

    sleep(2);

    err = pthread_cancel(thread);

    if (err != 0) {
        strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
        fprintf(stderr, "Error with pthread_cancel: %s\n", err_buf);
        return (EXIT_FAILURE);
    }

    err = pthread_join(thread, &thread_result);

    if (err != 0) {
        strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
        fprintf(stderr, "Error with pthread_join: %s\n", err_buf);
        return (EXIT_FAILURE);
    }

    if (thread_result == PTHREAD_CANCELED) {
        fputs("Thread canceled\n", stdout);
    } else {
        fputs("Thread did not cancel\n", stdout);
    }

    return (EXIT_SUCCESS);
}
void* thread_routine(void* arg) {
    while (1) {
        puts("Running...");
        pthread_testcancel();
    }
    return NULL;
}

