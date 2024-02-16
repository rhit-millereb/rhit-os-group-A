#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"

void main(void) {

    printf("Testing Threads: \n");

    struct thread_t thread;
    initThread(thread);
}