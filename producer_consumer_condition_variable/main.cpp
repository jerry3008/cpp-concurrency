#ifndef SUPERMISSIONHQ_H
#define SUPERMISSIONHQ_H

#include <queue>
#include <mutex>
#include <condition_variable>

class SuperMissionHQ {
public:
    SuperMissionHQ(size_t capacity) : mission_capacity_(capacity) {}

    void issue_mission(int mission) 
    {
        std::unique_lock<std::mutex> lock(mission_mutex_);
        cond_mission_full_.wait(lock, [this](){return  missions_.size() < mission_capacity_ ;});
        missions_.push(mission);
        cond_mission_empty_.notify_one();
    }

    int handle_mission() {
        std::unique_lock<std::mutex> lock(mission_mutex_);
        cond_mission_empty_.wait(lock, [this](){return  !missions_.empty();});
        auto item = missions_.front();
        missions_.pop();
        cond_mission_full_.notify_one();
        return item;
    }

private:
    std::queue<int> missions_;
    size_t mission_capacity_;
    std::mutex mission_mutex_;
    std::condition_variable cond_mission_full_;
    std::condition_variable cond_mission_empty_;
};

#endif // SUPERMISSIONHQ_H

// Main function to test the SuperMissionHQ implementation
#include <iostream>
#include <thread>

int main() {
    SuperMissionHQ hq(5);  // Mission queue capacity set to 5
    std::mutex console_mutex;

    // Superheroes issuing missions
    std::thread ironMan([&hq, &console_mutex]() {
        for (int i = 0; i < 12; ++i) {
            hq.issue_mission(i);
            {
                std::lock_guard<std::mutex> lock(console_mutex);
                std::cout << "Mission issued by Iron Man: " << i << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(90));
        }
    });

    // Sidekicks handling missions
    std::thread warMachine([&hq, &console_mutex]() {
        for (int i = 0; i < 12; ++i) {
            int mission = hq.handle_mission();
            {
                std::lock_guard<std::mutex> lock(console_mutex);
                std::cout << "Mission handled by War Machine: " << mission << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });

    ironMan.join();
    warMachine.join();

    return 0;
}