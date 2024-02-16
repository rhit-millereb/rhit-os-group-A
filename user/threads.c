#include "kernel/types.h"
#include "user.h"


struct thread_t {
    int id;
    int busy;
    void *stack;
};


int thread_create(struct thread_t *thread, void (*f)(void*), void* arg) {

    return 0;
}

int thread_join(struct thread_t thread) {

    return 0;
}

int thread_kill(struct thread_t thread) {

    return 0;
}