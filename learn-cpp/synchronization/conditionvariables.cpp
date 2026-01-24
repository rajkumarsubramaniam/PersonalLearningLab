//
// Objective: Refresh about using condition variables. Learn CPP synchronization.
// Task: 
// Step1: Create two threads, and let send the data the other one receive it.
// Step2: Play around and learn, identify cons in the code etc.,
// 
#include <condition_variable>
#include <thread>
#include <iostream>

using namespace std;

mutex sharedLock;
condition_variable cv;

bool dataReady = false;
const int iterations = 10;

void consumer() {

    for(int i = iterations; i > 0; i--) {
        //Another RAII, unique_lock works with Condition Variables.
        //unique_locks have some flexibility over lock_guard

        unique_lock<mutex> myLock(sharedLock); 

        //cannot use defer_lock here, as the cv.wait requires the lock owner. Else, undefined.
        //unique_lock<mutex> myLock(sharedLock, defer_lock); 

        // wait for producer
        // the wait function is used with the predicate here, this is similar to 
        // while(!datReady) { signal.wait(sharedLock); } // to handle spurious wakeups.
        cv.wait(myLock, [] {return dataReady;}); //This is just a lambda overload of the while loop.
        
        dataReady = false;
        cout << "Consumer: Data is received\n";

        cv.notify_one();
    }
    return;

}

void producer() {

    for(int i = iterations; i > 0; i--) {

        //RAII - Resource Aquisition Is Initialization technique
        //Tries to acquire lock during construction and release automatically during destruction.

        //Problems with Lock_guard - No flexibility. Locks when init, and unlocks at out of scope.
        //So, I can't use in while loop. if we want the producer to consume immediately.
        //lock_guard<mutex> myLockGuard(sharedLock); 
       
        unique_lock<mutex> myUniLock(sharedLock);

        cv.wait(myUniLock, [] {return !dataReady;});

        //produce something
        dataReady = true;
        cout << "Producer Thread: Completed\n";

        //Unlock here?- It is okay, but not needed to unlock explicity,
        //myLockGuard.unlock();    // cannot do this, not supported by lock_guard 
        //myUniLock.unlock(); //  Unique_lock allows this. 
        //myUniLock.release(); -- >Careful:  This release and disowns the mutex and not unlock

        cv.notify_one();
    }
    return;
}

int main() {

    //create two threads
    thread prThread(producer);
    thread crThread(consumer);

    prThread.join();
    crThread.join();

    return 0;
}