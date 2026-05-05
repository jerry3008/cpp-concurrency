#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class Philosopher {
public:
    Philosopher(int id, std::mutex* leftFork, std::mutex* rightFork, std::mutex* coutMutex)
        : id_(id), leftFork_(leftFork), rightFork_(rightFork), coutMutex_(coutMutex) {}

    void dine() {
        for (int i = 0; i < 10; ++i) {
            think();
            eat();
        }
    }

private:
    void think() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void eat() 
    {
        // TODO: Create a unique lock for the left fork and right fork using std::defer_lock to defer locking in case of deadlock.
        std::unique_lock<std::mutex>leftlock(*leftFork_, std::defer_lock);
        std::unique_lock<std::mutex>rightlock(*rightFork_, std::defer_lock);
        std::lock(leftlock, rightlock);

        // TODO: Use std::lock to lock both forks at the same time.

        {
            std::lock_guard<std::mutex> lock(*coutMutex_);
            std::cout << "Philosopher " << id_ << " is eating." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        {
            std::lock_guard<std::mutex> lock(*coutMutex_);
            std::cout << "Philosopher " << id_ << " finished eating. Thinking..." << std::endl;
        }
    }

    int id_;
    std::mutex* leftFork_;
    std::mutex* rightFork_;
    std::mutex* coutMutex_;
};


int main() {
    const int numPhilosophers = 5;
    std::vector<std::mutex> forks(numPhilosophers);
    std::vector<std::thread> philosophers;
    std::mutex coutMutex;

    for (int i = 0; i < numPhilosophers; ++i) {
        std::mutex* leftFork = &forks[i];
        std::mutex* rightFork = &forks[(i + 1) % numPhilosophers];

        // TODO: Create a thread for each philosopher and call the dine function passing the dine function and the Philosopher object with the correct parameters.
        philosophers.emplace_back(&Philosopher::dine, Philosopher(i, leftFork, rightFork, &coutMutex));
    }

    for (auto& philosopher : philosophers) {
        philosopher.join();
    }

    return 0;
}