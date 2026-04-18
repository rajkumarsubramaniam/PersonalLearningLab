
#include <stdio.h>
#include <pthread.h> // needs -lpthread flag in compilation - posix library
#include "locks.h"
#include "environ.h"

void* TestMutexLock() {
    mutex_lock* mylock;
    mylock = InitMutexLock();

    if(AcquireMutexLockWithLoop(mylock) != false) {
        printf("Acquired mutex lock: Address: %llx\n",mylock);
        if(ReleaseMutexLock(mylock) != false){
             printf("Lock Released!\n");
        }
    }
    DestroyLock(mylock);
    printf("Mutex Lock Test Completed!\n");
    return NULL;
}

int main(int argc, int **argv) {

    pthread_t firstThread;
    pthread_t secondThread;

    PrintCompilerAndTargetSettings();

    // Test two threads

    // Create a new thread
    // Arguments:
    // 1. Pointer to a pthread_t variable (to store the thread ID)
    // 2. Thread attributes (NULL for default)
    // 3. Pointer to the function the thread will run
    // 4. Argument to pass to the function (can be NULL if none needed)
    if(pthread_create(&firstThread, NULL, TestMutexLock, NULL) != 0) {
        perror("Failed to create thread 1.");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&secondThread, NULL, TestMutexLock, NULL) != 0) {
        perror("Failed to create thread 2.");
        exit(EXIT_FAILURE);
    }

    // Wait for the created thread to finish
    if (pthread_join(firstThread, NULL) != 0) {
        perror("Failed to join thread");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(secondThread, NULL) != 0) {
        perror("Failed to join thread");
        exit(EXIT_FAILURE);
    }
    
    //TestMutexLock();
    
    return EXIT_SUCCESS;

}