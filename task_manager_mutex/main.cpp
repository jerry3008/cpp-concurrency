#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

// TODO: Define a shared queue for tasks and its corresponding mutex
std::queue<int> sharedTask;
std::mutex mutex_;
// TODO: Implement a function to safely add a task to the shared queue
// The function should lock the queue using a guard and add a task ID to it
void addtask( int id)
{
    std::lock_guard<std::mutex>guard(mutex_);
    sharedTask.push(id);
    
}
// TODO: Implement a function to process tasks
// It should lock the queue, check if the task queue is not empty, process a task, and then remove the task from the queue
void processtask()
{
    std::lock_guard<std::mutex>guard(mutex_);

    while(!sharedTask.empty())
    {
        
       auto value = sharedTask.front();
       sharedTask.pop();
       std::cout<< "the task ID is processing: "<<value<<std::endl;
    }
    
    
}

int main() {
    // TODO: Create three threads to add tasks to the shared queue
    std::thread t1(addtask, 2);
    std::thread t2(addtask, 4);
    std::thread t3(addtask, 6);
    

    // TODO: Join the task-adding threads
    t1.join();
    t2.join();
    t3.join();
    // TODO: Create a thread to process tasks and join it
    std::thread t4(processtask);
    t4.join();

    return 0;
}