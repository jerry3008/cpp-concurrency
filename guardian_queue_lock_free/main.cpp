#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// TODO: Create a template class GuardianQueue to manage Guardian names concurrently
template<typename T>
class GuardianQueue {
private:
    // TODO: Define a Node struct with atomic pointers for lock-free operations
    struct Node 
    {
        T data;
        std::atomic<Node*>next;
        Node(const T& value): data(value), next(nullptr){}
        // TODO: Include the necessary members for Node such as data and next 
    };
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    // TODO: Declare head and tail as atomic pointers for start and end of the queue
public:
    // TODO: Implement the constructor to initialize a sentinel node
    GuardianQueue()
    {
        Node* dummy = new Node(T{});
        head.store(dummy);
        tail.store(dummy);
    }
    
    // TODO: Implement the destructor to clean up all nodes
    ~GuardianQueue()
    {
        while (Node* old_head = head.load()) 
        {
            head.store(old_head -> next);
            delete old_head;
        }
    }

    // TODO: Implement enqueue method to add items to the queue tail
    void enqueue(const T& value)
    {
        Node* new_node = new Node(value);
        Node* old_tail;
        while (true) 
        {
            old_tail = tail.load();
            Node* tail_next = old_tail->next;
            if (old_tail == tail.load())
            {
                if(tail_next == nullptr)
                {
                    if(old_tail->next.compare_exchange_weak(tail_next, new_node))
                    {
                        break;
                    }
                }else {
                    tail.compare_exchange_weak(old_tail, tail_next);
                }
            
            }
        
        }
        tail.compare_exchange_weak(old_tail, new_node);
        std::cout << "Pushed: " << value << "\n";
    }

    // TODO: Implement dequeue method to remove items from the queue head
    bool dequeue(T& result)
    {
        Node* old_head;
        
        while(true)
        {
            old_head = head.load();
            Node* old_tail = tail.load();
            Node* head_next = old_head ->next;
            if(old_head == head.load())
            {
                if(old_head == old_tail)
                {
                    if(head_next == nullptr)
                    {
                        std::cout << "Pop failed - queue is empty.\n";
                        return false;
                    }
                    tail.compare_exchange_weak(old_tail, head_next);
                }else 
                {
                    if(head.compare_exchange_weak(old_head, head_next))
                    {
                        result = head_next ->data;
                        delete old_head;
                        std::cout << "Popped: " << result << "\n";
                        return true;
                    }
                
                }
            }
            
        }
    }
};

void addGuardians(GuardianQueue<std::string>& queue, const std::vector<std::string>& guardians) {
    for (const auto& guardian : guardians) {
        queue.enqueue(guardian);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

void removeGuardians(GuardianQueue<std::string>& queue, int count) {
    std::string value;
    for (int i = 0; i < count; ++i) {
        queue.dequeue(value);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    GuardianQueue<std::string> queue;

    std::vector<std::string> guardians1 = {"Star Lord", "Gamora", "Rocket"};
    std::vector<std::string> guardians2 = {"Drax", "Groot", "Nebula"};

    std::thread t1(addGuardians, std::ref(queue), guardians1);
    std::thread t2(removeGuardians, std::ref(queue), 2);
    std::thread t3(addGuardians, std::ref(queue), guardians2);
    std::thread t4(removeGuardians, std::ref(queue), 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}