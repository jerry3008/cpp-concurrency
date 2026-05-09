#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

std::mutex coutMutex;

// TODO: Define the HeroStack class template with HeroNode struct.
// - Use std::atomic for the top
// - Implement the constructor

template<typename T>
class HeroStack {
private:
    struct HeroNode 
    {
        T heroPower;
        HeroNode* next;
        HeroNode(const T& value): heroPower(value), next(nullptr){}
        // TODO: Define heroPower and next for HeroNode. Implement constructor.
    };

    // TODO: Declare an atomic pointer to HeroNode named top.
    std::atomic<HeroNode*> top;

public:
    // TODO: Implement the HeroStack constructor to initialize top.
    HeroStack() : top(nullptr){}

    void enlist(const T& power) 
    {
        HeroNode* newHeroNode = new HeroNode(power);
        newHeroNode -> next = top.load(std::memory_order_acquire);
        
        while(!top.compare_exchange_weak(newHeroNode -> next, newHeroNode, std::memory_order_release, std::memory_order_relaxed))
        {
            
        }
        {
            std::lock_guard<std::mutex>  lk(coutMutex);
            std::cout << "Pushed: " << power << "\n";
        
        }
            
        
        // TODO: Create a new HeroNode, use atomic operations with correct memory order.
        // - Add the new HeroNode to the stack
        // - Ensure memory safety using compare_exchange_weak
        // - Lock coutMutex and print a message with the enlisted hero's power
    }

    bool deploy(T& power) 
    {
        HeroNode* old_head = top.load(std::memory_order_acquire);
        
        while(old_head)
        {
            if(top.compare_exchange_weak(old_head, old_head -> next,
                                            std::memory_order_acquire,
                                            std::memory_order_relaxed))
                                            {
                                                power = old_head -> heroPower;
                                                delete old_head;
                                                {
                                                    std::lock_guard<std::mutex>  lk(coutMutex);
                                                    std::cout << "Popped: " << power << "\n";
                                                }
                                            
                return true;
            }
        }
        {
            std::lock_guard<std::mutex>  lk(coutMutex);
            std::cout << "Pop failed - stack is empty.\n";
            
        }
        
        // TODO: Implement deploy using atomics with correct memory ordering.
        // - Remove the top HeroNode if available
        // - Utilize compare_exchange_weak for atomicity
        // - Lock coutMutex and print a message with the deployed hero's power or a failure message
        return false; // Default return value, replace with actual logic
    }
};

// TODO: Implement enlistHeroes function for adding heroes
void enlistHeroes(HeroStack<int>& stack, int count) {
    int power;
    for (int i = 0; i < count; ++i) 
    {
        stack.enlist(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // TODO: Deploy heroes from the stack using deploy method.
    }
}

void deployHeroes(HeroStack<int>& stack, int count) {
    int power;
    for (int i = 0; i < count; ++i) 
    {
        stack.deploy(power);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        // TODO: Deploy heroes from the stack using deploy method.
    }
}

int main() 
{
    HeroStack<int> stack;
    std::thread t1(enlistHeroes, std::ref(stack),  6);
    std::thread t2(deployHeroes, std::ref(stack), 3);
    std::thread t3(enlistHeroes, std::ref(stack),  11);
    std::thread t4(deployHeroes, std::ref(stack), 5);
    // TODO: Initialize a HeroStack and create threads for enlisting and deploying heroes
    // - Use join to synchronize thread completion.
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}