#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "threads.c"

int x = 0;

void test_thread_create(void *arg) {
    int *id = ((int*) arg);

    printf("Child: Thread Started Function with ID: %d\n", *id);

    x = 1;

    printf("Child: Completing Function\n");
    return;
}


void main(void) {

    printf("Testing Threads: \n");

    printf("\nMain: Creating a thread:\n");
    
    struct thread_t thread;

    thread_create(&thread, *test_thread_create, (void*) 1);

    printf("Main: Thread Created, function still running\n");

    printf("Main: Starting Join\n")

    thread_join(thread);

    printf("Main: Completed Join\n")
}