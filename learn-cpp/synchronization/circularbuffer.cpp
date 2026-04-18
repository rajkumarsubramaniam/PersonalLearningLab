/**************************************************************************
 * 
 * Intended to make mistakes and learn. May or may not have AI assit.
 * Recommend not to be used for any evaluations of the developer.
 * 
 *************************************************************************/

#include <cstddef>

class CircularQueue {

private:
    int* buffer;
    size_t size;
    size_t headWrite;
    size_t tailRead;

public:

    CircularQueue(size_t capacity) {
    
        buffer = new int[capacity+1]; // Burning One slot for full check.
        size = capacity + 1;
        headWrite = 0;
        tailRead = 0;
    }

    ~CircularQueue() {
        delete[] buffer;
    }

    bool isEmpty() const {
        return (headWrite == tailRead);
    }

    bool isFull() const {
        return (((headWrite+1) % size) == tailRead);
    }

    int WriteToQueue(int data) {
        if(isFull()) {
        return -1;
        }

        buffer[headWrite] = data;
        headWrite = (headWrite + 1) % size;

        return 0;
    }

    int ReadfromQueue (int* data) {
        if(data == NULL) 
            return -1;

        if(isEmpty()) {
            return -1;
        }
        *data = buffer[tailRead];
        tailRead = (tailRead+1) % size;
        return 0;
    }
};

int main() {

    return 0;
}