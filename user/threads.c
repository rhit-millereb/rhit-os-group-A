#include "kernel/types.h"
#include "user.h"

#define PGSIZE 4096 // bytes per page


struct thread_t {
    int id;
    int busy;
    void *stack;
};


int thread_create(struct thread_t *thread, void(*f)(void*), void* arg) {
    //allocates the pagetable data on the virtual memory
    void* pagetable = malloc(PGSIZE*2);
    if(pagetable == 0) {
        printf("The malloc did not malloc any memory!");
        return -1;
    }

    //Sets the stack location to go a pagetable amount for the newly created pagetable
    if((uint64)pagetable % PGSIZE == 0) thread->stack = pagetable;
    else thread->stack = pagetable - ((uint64)pagetable % PGSIZE);

    //Sets the thread as started
    thread->busy = 1;
    
    //Clones the physical memory data from the old thread to the new one
    thread->id = procclone(f, arg, thread->stack);
    if(thread->id < 0) return -1;
    return thread->id;
}


int thread_join(struct thread_t thread) {
    //int i = 1;
    
    join(1);

    return 0;
}

int thread_kill(struct thread_t thread) {

    return 0;
}