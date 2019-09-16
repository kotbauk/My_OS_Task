
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define STRING_NUM 10
void* thread_function(void* arg);
pthread_t child_thread;
int main(void) {

    int err;
    err  = pthread_create(&child_thread, NULL, thread_function, NULL);
    if (err != 0) {
       fprintf(stderr, "Can't create thread. Exit.\n");  
       return (EXIT_FAILURE);
    }

    for (size_t number_of_string = 0; number_of_string < STRING_NUM; ++number_of_string) {
        printf("Main thread line[%zd]\n", number_of_string + 1);
    }
    pthread_exit((void*) EXIT_SUCCESS);
}

void* thread_function(void* arg) {
    for (size_t number_of_string = 0; number_of_string < STRING_NUM; ++number_of_string) {
        printf("Childs thread line[%zd]\n", number_of_string + 1);
    }
    return (void*) NULL;
}

