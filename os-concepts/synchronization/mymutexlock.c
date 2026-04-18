#include<stdio.h>
#include "locks.h"

mutex_lock* InitMutexLock() {
    // allocate a lock variable.
    mutex_lock* lock;
    lock =  (mutex_lock*)malloc(sizeof(mutex_lock));
    if(lock != NULL) {
        lock->locked = false;
    }
    return lock;
}

bool AcquireMutexLockWithLoop (mutex_lock* lock) {
    bool acquirelock = false;
#if defined  __GNUC__ && _WIN64
    //Use GNU APIs.
    while(acquirelock != true) {
        //
        // __sync_bool_compare_and_swap(*lock, oldvalue, newvalue)
        //
        acquirelock = __sync_bool_compare_and_swap(&lock->locked, false, true);
    }
    printf("This code executes - GNUC && _WIN64\n");
#elif defined __GNUC__ && defined _WIN32

    printf("This code executes - GNUC && _WIN32\n");
#elif defined (_MSC_VER)
    //Use InterlockedCompareExchange
#endif
    return acquirelock;
}

bool ReleaseMutexLock(mutex_lock* lock) {
    bool released = false;
    released = __sync_bool_compare_and_swap(&lock->locked, true, false);
    return released;
}

void DestroyLock(mutex_lock* lock) {
    free(lock);
}