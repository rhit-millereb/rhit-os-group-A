#include "kernel/types.h"
#include "user.h"



struct thread_t {
    int id;
    int busy;
    void *stack;
};


int thread_create(struct thread_t *thread, void(*f)(void*), void* arg) {
    void* pagetable = malloc(PGSIZE*2);
    if(pagetable == 0) panic("The malloc did not malloc any memory!");
    if(*(uint*)pagetable % PGSIZE == 0) thread->stack = pagetable;
    else thread->stack = pagetable - (*(uint*)pagetable % PGSIZE);
    return procclone(f, arg, thread->stack);
}


int thread_join(struct thread_t thread) {
    int i = 1;
    
    join((void*) &i);

    return 0;
}

int thread_kill(struct thread_t thread) {

    return 0;
}