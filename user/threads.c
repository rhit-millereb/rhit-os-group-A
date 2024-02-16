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
    if(*(uint*)pagetable % PGSIZE == 0) thread->stack = pagetable;
    else thread->stack = pagetable - (*(uint*)pagetable % PGSIZE);

    //Sets the thread as started
    thread->busy = 1;
    
    //Clones the physical memory data from the old thread to the new one
    int newID = procclone(f, arg, thread->stack);
    thread->id = newID;

    //determine if procclone failed and return the error code
    if (newID < 0) {
        return newID;
    }

    //return showing function was successful
    return 0;
}


int thread_join(struct thread_t thread) {
    //int i = 1;
    
    join(thread.id);

    return 0;
}

int thread_kill(struct thread_t thread) {

    return 0;
}