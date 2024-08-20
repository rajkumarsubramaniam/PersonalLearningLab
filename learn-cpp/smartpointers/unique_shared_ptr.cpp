/*
    Code generated with GPT & modified for learning purposes 

    This code experiements with unique_ptr and shared_ptr with a simple class.
    
*/

#include <iostream>
#include <memory> // Include the header for smart pointers

using namespace std;

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor called!" << std::endl;
    }
    
    ~MyClass() {
        std::cout << "MyClass destructor called!" << std::endl;
    }

    void display() {
        std::cout << "Hello from MyClass!" << std::endl;
        //std::cout << "Address of this ptr: " <<  << std::endl;
    }
};

void test_unique_ptr() {
    // Creating a unique_ptr to manage a MyClass object
    std::unique_ptr<MyClass> ptr1(new MyClass); //std::make_unique<MyClass>();

    // Accessing the object via unique_ptr
    ptr1->display();

    // Transferring ownership to another unique_ptr
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
    //Notice, move didn't invoke the Construtor for ptr2 or the destructor for ptr1.

    //
    // This is wrong because when we have unique pointers default copy constructor is not generrated.
    //
    //std:unique_ptr<MyClass> ptr2(&ptr1); 

    if (!ptr1) {
        std::cout << "ptr1 is now null after move! Ptr2: "<<ptr2.get() << std::endl;
    }

    // ptr2 now owns the MyClass object
    ptr2->display();

    std::unique_ptr<MyClass> ptr3 = std::make_unique<MyClass>();
    std::cout << "Ptr3: " << ptr3.get() << std::endl;

    // unique_ptr will automatically delete the object when it goes out of scope
}

void useSharedPtr(std::shared_ptr<MyClass> ptr) {
    std::cout << "Inside function, use count: " << ptr.use_count() << std::endl;
    ptr->display();
}

void test_shared_ptr() {
        // Create a shared_ptr that owns a MyClass object
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();

    std::cout << "After creation, use count: " << ptr1.use_count() << std::endl; // Output: 1

    // Create another shared_ptr pointing to the same MyClass object
    std::shared_ptr<MyClass> ptr2 = ptr1;

    std::cout << "After copying, use count: " << ptr1.use_count() << std::endl; // Output: 2

    // Pass shared_ptr to a function
    useSharedPtr(ptr1);

    std::cout << "After function call, use count: " << ptr1.use_count() << std::endl; // Output: 2

    // Reset one of the shared_ptrs, reducing the reference count
    ptr2.reset();

    std::cout << "After reset, use count: " << ptr1.use_count() << std::endl; // Output: 1

    // The object will be automatically deleted when the last shared_ptr goes out of scope

}

int main() {
    
    test_unique_ptr();

    std::cout << "****************************\n";

    test_shared_ptr();

    return 0;
}
