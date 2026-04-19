/**************************************************************************
 * 
 * Intended to make mistakes and learn. May or may not have AI assit.
 * Recommend not to be used for any evaluations of the developer.
 * 
 *************************************************************************/

#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;


// Helper to find next power of 2
size_t nextPowerOfTwo(size_t n) {
    if (n == 0) return 1;
    n--;
    n |= n >> 1; n |= n >> 2; n |= n >> 4;
    n |= n >> 8; n |= n >> 16; n |= n >> 32;
    return n + 1;
}


//
// This CircularQueueSRSW class is converted to efficiently do the single reader and single writer access with no locks.
//
template <typename T>
class CircularQueueSRSW {

private:
    T* buffer;
    size_t size;
    atomic<size_t> headWrite;
    atomic<size_t> tailRead;

    // Prevent accidental copying (The Rule of Three) - if another object is created we don't want a shallow copy 
    // that would make two Objects point to the same buffer location.
    CircularQueueSRSW(const CircularQueueSRSW&) = delete;
    CircularQueueSRSW& operator=(const CircularQueueSRSW&) = delete;

public:
    CircularQueueSRSW(size_t capacity) {
        //Always use power of two capactity.
        if(capacity & (capacity - 1) != 0) {
            // Ceil to the next power of 2.
            capacity = nextPowerOfTwo(capacity);
        }
        buffer = new T[capacity]; // Burning One for the "dead" slot.
        size = capacity;

        //Relaxed - is used when we care about the variable itself on the current thread and not the previous reads or writes.
        headWrite.store(0, memory_order_relaxed);  
        tailRead.store(0, memory_order_relaxed);
    }

    ~CircularQueueSRSW() {
        delete[] buffer;
    }

    // These are implemeted  to understand the single writer/reader cases 
    // without a lock. 

    bool isEmptySingleRWNoLock() const {
        // Use acquire to see the latest write from the other thread
        return headWrite.load(memory_order_acquire) == tailRead.load(memory_order_relaxed);
        //Because ins SRSW - the empty is called by the reading thread, adn reading thread controls the tailRead 
        // and the headWrite is the one that we need to see from the other thread.
    }

    bool isFullSingleRWNoLock() const {
        size_t nextHead = (headWrite.load(memory_order_relaxed) + 1 ) & (size -1);
        return (nextHead == tailRead.load(memory_order_acquire));
    }

    int WriteToQueueSingleRWNoLock(const T& data) {

        size_t currHead = headWrite.load(memory_order_relaxed);
        size_t nextHead = (currHead + 1) & (size -1);
        
        //check full.
        if(nextHead == tailRead.load(memory_order_acquire)) //acquire - because we need to see what the other guy updated.
            return -1;

        buffer[currHead] = data;
        
        headWrite.store(nextHead, memory_order_release); // release - ensure all previous writes are finished and visible to others.
        return 0;
    }

    int ReadfromQueueSingleRWNoLock (T* data) {
        if(data == NULL) 
            return -1;
        
        size_t currTail = tailRead.load(memory_order_relaxed);
        
        //check empty
        if(currTail == headWrite.load(memory_order_acquire)) 
            return -1;

        *data = buffer[currTail];
        currTail = (currTail+1) & (size - 1);

        // Release the tail update so the producer knows there is new space.
        tailRead.store(currTail, std::memory_order_release);
        return 0;
    }
};

//
// Ring buffer implementation for multiple readers and writers. 
//
template <typename T>
class CircularQueueMRMW {

private:
    T* buffer;
    size_t size;
    size_t head;
    size_t tail;
    mutex mt;
    condition_variable cd_slot_available;
    condition_variable cd_data_ready;

    CircularQueueMRMW(const CircularQueueMRMW&) = delete;
    CircularQueueMRMW& operator=(const CircularQueueMRMW&) = delete;

    //Only the lock holder should call this.
    bool isFull() {
        return (((head+1) & (size-1)) == tail);
    }

    //Only the lock holder should call this.
    bool isEmpty() {
        return (head == tail);
    }

public:
   CircularQueueMRMW(size_t capacity) {
        //Always use power of two capactity.
        if(capacity & (capacity - 1) != 0) {
            // Ceil to the next power of 2.
            capacity = nextPowerOfTwo(capacity);
        }
        buffer = new T[capacity]; // Burning One for the "dead" slot.
        size = capacity;
        
        head = 0;
        tail = 0;
    }

    ~CircularQueueMRMW() {
        delete[] buffer;
    }

    int WriteToQueueMRMW(const T& data) {

        //acquire lock and check condition variable.
        unique_lock<mutex> thisLock(mt);
        
        // Here we are the lock owner. 
        // check CV slot available - release lock and wait  if not.
        // the lambda (predicate) should return true when you want to proceed, not when you want to wait.
        // Your isFull() and isEmpty() functions are private members. 
        // When you use them inside a lambda, the lambda needs access to the class instance.
        cd_slot_available.wait(thisLock, [this] {return !isFull();}); 

        buffer[head] = data; 
        head = (head + 1) & (size - 1);

        cd_data_ready.notify_one();
        //Organically the lock will be released here because of unique_lock
        return 0;
    }

    int ReadFromQueueMRMW(const T* data) {

        //acquire lock and check condition variable.
        unique_lock<mutex> thisLock(mt);
        
        // Here we are the lock owner. 
        // check CV slot available - release lock and wait  if not.
        cd_data_ready.wait(thisLock, [this] {return !isEmpty();});
        
        data = buffer[tail];
        tail = (tail + 1) & (size - 1);
        
        cd_slot_available.notify_one();
        //Organically the lock will be released here because of unique_lock

        return 0;
    }

    // this is another scenario to handle.
    // Shutdown handling can be done with a shutdownflag and called from the destructor or from the 
    // main thread-followed by thread-join calls. 
    void shutdown() {
        // Not implemented
    }
};

void Test1() {
    // A queue for integers
    CircularQueueSRSW<int> intQ(5);
    intQ.WriteToQueueSingleRWNoLock (10);

    // A queue for doubles
    CircularQueueSRSW<double> doubleQ(10);
    doubleQ.WriteToQueueSingleRWNoLock(3.14159);

    // Even a queue for custom structs!
    struct Player { int id; float health; };
    CircularQueueMRMW<Player> playerQ(20);

    playerQ.WriteToQueueMRMW({1, 99.9});
    
    cout << "Test1 Completed.\n";
}

int main() {
    Test1();
    return 0;
}