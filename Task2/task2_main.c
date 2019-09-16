
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define ERROR_BUFFER_LEN 256
#define STRING_NUM 10

void* thread_function(void* arg);
int main(void) {

    int err;
    void* join_ret_code;
    char err_buf[ERROR_BUFFER_LEN];
    pthread_t child_thread;
    err  = pthread_create(&child_thread, NULL, thread_function, NULL);
    if (err != 0) {
        strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
        fprintf(stderr, "Error with pthread_create: %s\n", err_buf);
        return (EXIT_FAILURE);
    }
    err = pthread_join(child_thread, &join_ret_code);
    if (err != 0) {
        strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
        fprintf(stderr, "Error with pthread_join: %s\n", err_buf);
        return (EXIT_FAILURE);
    }

    for (int number_of_string = 0; number_of_string < STRING_NUM; ++number_of_string) {
        printf("Main thread line[%d]\n", number_of_string + 1);
    }

    pthread_exit((void*)(EXIT_SUCCESS));
}

void* thread_function(void* arg) {
    for (int  number_of_string = 0; number_of_string < STRING_NUM; ++number_of_string) {
        printf("Childs thread line[%d]\n", number_of_string + 1);
    }
    pthread_exit((void*)NULL);
}

