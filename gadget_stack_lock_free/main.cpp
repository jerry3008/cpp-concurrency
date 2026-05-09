#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex cout_mutex;

// TODO: Define a template class GadgetStack to handle gadgets in a thread-safe manner using atomic operations.
template<typename T>
class GadgetStack {
private:
    // TODO: Define a Gadget struct to hold the gadget type and the pointer to the next gadget.

    // TODO: Declare an atomic variable to keep track of the top gadget of the stack.
    struct gadget
    {
        T data;
        gadget* next;
        gadget(const T& value): data(value), next(nullptr){}
        
    };
    std::atomic<gadget*> head;

public:
// TODO: Implement a removeGadget function that removes gadgets from the stack.
    // - Use a loop with compare_exchange_weak to safely update topGadget while the stack is not empty.
    // - If the stack was empty, print a message and return false using a lock_guard and cout_mutex.
    // - On success, print an "Attempting to remove" message using a lock_guard and cout_mutex.
    // - Retrieve the gadget type, delete the node, and print the removed gadget using a lock_guard and cout_mutex.
    
    
    GadgetStack() : head(nullptr){}
    
    
    void addGadget(const T& value)
    {
        gadget* new_gadget = new gadget(value);
        new_gadget -> next = head.load();
        while(!head.compare_exchange_weak(new_gadget->next, new_gadget));
        {
            std::lock_guard<std::mutex>lk(cout_mutex);
            std::cout << "Pushing: " << value << "\n";
        }
    }
    
    
    
    
    bool removeGadget(T& result)
    {
        gadget* old_gadget =  head.load();
        while(old_gadget != nullptr && !head.compare_exchange_weak(old_gadget, old_gadget -> next));
        if(old_gadget == nullptr)
        {
            std::lock_guard<std::mutex>lk(cout_mutex);
            std::cout << "Pop failed - stack is empty.\n";
            return false;
        }
        
        {
            std::lock_guard<std::mutex>lk(cout_mutex);
            std::cout << "Attempting to pop...\n";
            result = old_gadget->data;
            delete old_gadget;
        }
        
        {
            std::lock_guard<std::mutex>lk(cout_mutex);
            std::cout << "Popped: " << result << "\n";
            return true;
        }
    }
    
};

void addGadgets(GadgetStack<std::string>& stack, int start, int end) {
    for (int i = start; i < end; ++i) {
        stack.addGadget("Gadget" + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Add delay
    }
}

void removeGadgets(GadgetStack<std::string>& stack, int count) {
    std::string gadgetType;
    for (int i = 0; i < count; ++i) {
        stack.removeGadget(gadgetType);
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Add delay
    }
}

int main() {
    GadgetStack<std::string> stack;

    std::thread t1(addGadgets, std::ref(stack), 1, 10);
    std::thread t2(removeGadgets, std::ref(stack), 5);
    std::thread t3(addGadgets, std::ref(stack), 10, 20);
    std::thread t4(removeGadgets, std::ref(stack), 5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}