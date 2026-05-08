#include <atomic>
#include <thread>
#include <iostream>

class VillainPlan {
public:
    void set_plan() {
        plan_status_.store(true, std::memory_order_seq_cst);
    }

    void check_plan() {
        
        while (!plan_status_.load(std::memory_order_seq_cst));
        std::cout << "Plan is set in motion!" << std::endl;
    }

private:
    std::atomic<bool> plan_status_{false};
};

int main() {
    VillainPlan plan;

    std::thread setterThread(&VillainPlan::set_plan, &plan);
    std::thread checkerThread(&VillainPlan::check_plan, &plan);
    setterThread.join();
    checkerThread.join();

    return 0;
}