#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

class Philosopher {
public:
    Philosopher(int id, std::timed_mutex* leftFork, std::timed_mutex* rightFork, std::mutex* coutMutex)
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

    void eat() {
        while (true) {
            // TODO: Replace std::mutex with std::timed_mutex and implement a timed lock for both forks
            // TODO: Attempt to lock left fork for 50 milliseconds using try_lock_for method
            if (leftFork_->try_lock_for(std::chrono::milliseconds(50))) 
            {
                // TODO: If successful, attempt to lock right fork for 50 milliseconds
                if (rightFork_->try_lock_for(std::chrono::milliseconds(50))) 
                {
                    {
                        std::lock_guard<std::mutex> lock(*coutMutex_);
                        std::cout << "Philosopher " << id_ << " is eating." << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    {
                        std::lock_guard<std::mutex> lock(*coutMutex_);
                        std::cout << "Philosopher " << id_ << " finished eating. Thinking..." << std::endl;
                    }
                    // Unlock both forks
                    rightFork_->unlock();
                    leftFork_->unlock();
                    break;
                } else {
                    {
                        std::lock_guard<std::mutex> lock(*coutMutex_);
                        std::cout << "Philosopher " << id_ << " could not acquire the right fork. Retrying..." << std::endl;
                    }
                    leftFork_->unlock();
                }
              // Introduce a short delay before retrying
              std::this_thread::sleep_for(std::chrono::milliseconds(10));
          }
      }
    }

    int id_;
    // TODO: Replace std::mutex with std::timed_mutex for both forks
    std::timed_mutex*  leftFork_;
    std::timed_mutex*  rightFork_;
    std::mutex* coutMutex_;
};

int main() {
    const int numPhilosophers = 5;
    std::vector<std::timed_mutex> forks(numPhilosophers);
    std::vector<std::thread> philosophers;
    std::mutex coutMutex;

    for (int i = 0; i < numPhilosophers; ++i) {
        // TODO: Replace std::mutex with std::timed_mutex for both forks
        std::timed_mutex* leftFork = &forks[i];
        std::timed_mutex* rightFork = &forks[(i + 1) % numPhilosophers];
        philosophers.emplace_back(&Philosopher::dine, Philosopher(i, leftFork, rightFork, &coutMutex));
    }

    for (auto& philosopher : philosophers) {
        philosopher.join();
    }

    return 0;
}