#ifndef MATH_PRODUCER_CONSUMER_H
#define MATH_PRODUCER_CONSUMER_H
#include <iostream>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

class MathProducerConsumer {
public:
    MathProducerConsumer(size_t capacity) : capacity_(capacity) {}
    void produce(const std::pair<int, int>& items)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_full_.wait(lock,[this](){return buffer_.size() <  capacity_;});
        buffer_.push(items);
         std::cout<<"Produced: ("<<items.first<<", "<<items.second<< ")"<<std::endl;
        cond_empty_.notify_one();
       
        
    }
    void  consume(std::vector<int>& result, std::mutex& res_mutex)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_empty_.wait(lock,[this](){return !buffer_.empty();});
        auto hold = buffer_.front();
        buffer_.pop();
        int sum = 0;
        sum = hold.first + hold.second;
        std::lock_guard<std::mutex> lock1(res_mutex);    
        result.push_back(sum);
        std::cout<<"Consumed sum: " << sum<< std::endl;
        cond_full_.notify_one();
       
        
    }

private:
    std::queue<std::pair<int, int>> buffer_;
    size_t capacity_;
    std::mutex mutex_;
    std::condition_variable cond_full_;
    std::condition_variable cond_empty_;
};

#endif // MATH_PRODUCER_CONSUMER_H

#include <iostream>
#include <thread>

int main() {
    MathProducerConsumer mpc(5);
    std::vector<int> results;
    std::mutex results_mutex;

    std::thread p1([&mpc, &results_mutex](){
        for(int i =0; i < 10; ++i)
        {
            mpc.produce({i, i + 1});
            
        }
    });

    std::thread c1([&mpc, &results_mutex, &results](){
        for(int i =0; i < 10; ++i)
        {
            mpc.consume(results, results_mutex);
        }
    });
    
    p1.join();
    c1.join();
   

    return 0;
}