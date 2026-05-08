#include <iostream>
#include <atomic>
#include <thread>

class VillainSignal {
public:
    void set_trap() 
    {
        trap_signal_.store(7, std::memory_order_release);

       trap_ready_.store(true, std::memory_order_release);
    }

    void check_trap() {
       
        while (!trap_ready_.load(std::memory_order_acquire));

        
        std::cout << "Trap Signal: " << trap_signal_.load(std::memory_order_acquire) << std::endl;
    }

private:
    std::atomic<int> trap_signal_{0};
    std::atomic<bool> trap_ready_{false};
};

int main() {
    VillainSignal trap;

    std::thread writerThread(&VillainSignal::set_trap, &trap);
    std::thread readerThread(&VillainSignal::check_trap, &trap);
    writerThread.join();
    readerThread.join();

    return 0;
}