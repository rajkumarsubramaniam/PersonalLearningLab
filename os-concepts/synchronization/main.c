
#include <stdio.h>
#include "locks.h"
#include "environ.h"

void TestMutexLock() {
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
    return;
}

int main(int argc, int **argv) {

    PrintCompilerAndTargetSettings();

    TestMutexLock();
    
    return 0;

}