#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "threads.c"


void test_thread_create(void *arg) {
    int *id = ((int*) arg);

    printf("Thread Started Function with ID: %d", *id);

}


void main(void) {

    printf("Testing Threads: \n");

    printf("\nCreating a thread:\n");
    
    struct thread_t thread;

    thread_create(&thread, *test_thread_create, (void*) 1);
}