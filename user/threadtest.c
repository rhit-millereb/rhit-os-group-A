#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "threads.c"

// create global variables for the threads to be tested on
int x = 0;
int y = 0;


int array[] = {0, 0, 0, 0, 0, 0};
int num_threads_test = 6;


void mprint(char *i) {
    printf("Main: %s\n", i);
}

void cprint(char *i, int *id) {
    printf("Child (%d): %s\n", id, i);
}

//function to be used in tests 1 and 2
void test_thread_create(void *arg) {
    int *id = ((int*) arg);

    //calls a function in the shared space, if this runs then the thread shares the same code space successfully
    cprint("Test 1: Thread Started Function", id);

    x = 1;

    cprint("Completing Function", id);
    return;
}

//function to be used in tests 3, 4, 5
void test_multiple_threads(void *arg) {
    int *id = ((int*) arg);

    array[*id] = *id;
    cprint("Altered array", id);
}


void main(void) {

    printf("Testing Threads: \n\n");


    //test the create functionality
    mprint("Test 1: Creating a thread...");
    
    // create a thread to start the basic tests on
    struct thread_t thread;
    thread_create(&thread, *test_thread_create, (void*) 1);
    // if reaches this point, the main thread is created and the main function is still running
    mprint("Test 1 Passed: Thread Created, main function still running\n");

    
    
    // test the join functionality
    mprint("Test 2: Starting Join...");
    int join_result = thread_join(thread);
    // determine if the value of x is now 1, if so join works and shared global vars work
    if(x == 1 && join_result == 0) {
        mprint("Test 2: Passed");
    } else if (x == 0) {
        mprint("Test 2 FAILED: Main did not see child thread changes to global var \'x\'");
    } else if (join_result != 0) {
        mprint("Test 2 FAILED: Join threw error code");
        printf("%d", join_result);
    }



    //test creating multiple threads
    mprint("Test 3: Test Multiple Threads...");
    struct thread_t *threads = malloc(sizeof(struct thread_t) * num_threads_test);
    int *threadIDs = malloc(num_threads_test);
    for(int i=0; i<num_threads_test; i++) {
        threadIDs[i] = i;
        thread_create(&threads[i], *test_multiple_threads, (void*) &threadIDs[i]);
    }
    mprint("Test 3: All threads created");
    for(int i=0; i<num_threads_test; i++) {
        thread_join(threads[i]);
    }
    //iterate over the array to determine if the values match
    for(int i=0; i<num_threads_test; i++) {
        if (array[i] != i) {
            mprint("Test 3: FAILED: Array did not match at index:");
            printf("%d  Found: %d", i, array[i]);
        }
    }
    mprint("Test 3: Passed");

}
