
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define ERROR_BUFFER_LEN 256
#define NUMBER_OF_THREADS 4

struct thread_pack_arg {
    int number_of_strings;
    const char** strings_to_print;
};

static char err_buf[ERROR_BUFFER_LEN];
void* thread_function(void* arg);
struct thread_pack_arg* initialization_thread_arg(
    struct thread_pack_arg* thread_args,
    const size_t thread_number,
    const size_t string_number,
    const char* strings_to_print[]);
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        fputs("Too few arguments. Exit\n", stderr);
        return (EXIT_FAILURE);
    }

    int err;
    const size_t number_of_strings = argc - 1;
    const size_t number_of_threads = NUMBER_OF_THREADS > number_of_strings
                                         ? number_of_strings
                                         : NUMBER_OF_THREADS;

    pthread_t threads_for_print[number_of_threads];

    struct thread_pack_arg threads_pack_arr[number_of_threads];
    initialization_thread_arg(threads_pack_arr, number_of_threads,
                              number_of_strings, argv + 1);

    for (register size_t cur_thread = 0; cur_thread < number_of_threads;
         ++cur_thread) {
        err = pthread_create(threads_for_print + cur_thread, NULL,
                             thread_function,
                             (void*)(threads_pack_arr + cur_thread));

        if (err != 0) {
            strerror_r(errno, err_buf, (size_t)ERROR_BUFFER_LEN);
            fprintf(stderr, "Error with pthread_create: %s\n", err_buf);
            return (EXIT_FAILURE);
        }
    }

    pthread_exit((void*)EXIT_SUCCESS);
}

void* thread_function(void* arg) {
    const struct thread_pack_arg* thread_arg = (struct thread_pack_arg*)arg;
    for (size_t cur_pack = 0; cur_pack < thread_arg->number_of_strings;
         ++cur_pack) {
        fprintf(stdout, "Theread: %zd Say: %s\n", pthread_self(),
                *(thread_arg->strings_to_print + cur_pack));
    }
    return (void*)NULL;
}

struct thread_pack_arg* initialization_thread_arg(
    struct thread_pack_arg* thread_args,
    const size_t thread_number,
    const size_t string_number,
    const char* strings_to_print[]) {
    const size_t string_remainder = string_number % thread_number;
    const size_t string_inter_part = string_number / thread_number;
    const size_t thread_inter_part = thread_number - string_remainder;

    size_t cur_pack = 0;

    for (; cur_pack < string_remainder; ++cur_pack) {
        thread_args[cur_pack].number_of_strings = string_inter_part + 1;
        thread_args[cur_pack].strings_to_print =
            (strings_to_print + cur_pack * (string_inter_part + 1));
    }
    strings_to_print += string_remainder;
    for (; cur_pack < thread_number; ++cur_pack) {
        thread_args[cur_pack].number_of_strings = string_inter_part;
        thread_args[cur_pack].strings_to_print =
            (strings_to_print + (cur_pack * string_inter_part));
    }

    return thread_args;
}
