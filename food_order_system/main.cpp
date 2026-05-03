#ifndef FOODORDERSYSTEM_H
#define FOODORDERSYSTEM_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

class FoodOrderSystem
{
  private:
  std::queue<std::string>buffer_;
  size_t capacity;
  std::mutex m1;
  std::condition_variable cd_ready;
  std::condition_variable cd_notready;
  
  public:
  FoodOrderSystem(int capacity): capacity(capacity){}
  
  void place_order(const std::string& order)
  {
    std::unique_lock<std::mutex>lock(m1);
    cd_ready.wait(lock, [this](){return buffer_.size() < capacity;});
    buffer_.push(order);
    std::cout<< "Order placed: " <<order << std::endl;
    cd_notready.notify_one();
  }
    
    
    std::string deliver_order()
    {
        std::unique_lock<std::mutex>lock(m1);
        cd_notready.wait(lock, [this](){return !buffer_.empty();});
        auto item = buffer_.front();
        buffer_.pop();
        
        std::cout<< "Order delivered: " <<item << std::endl;
        cd_ready.notify_one();
        return item;
    }
};

#endif // FOODORDERSYSTEM_H

#include <thread>
#include <iostream>

int main() 
{
    
    FoodOrderSystem FoodOrderSystem_(5);
    std::mutex console_mutex;
    
    
    std::thread chef([&FoodOrderSystem_, &console_mutex]()
    {
       for(int i = 0; i < 10; ++i)
       {
        FoodOrderSystem_.place_order("plaintains");
        std::lock_guard<std::mutex> lock(console_mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
       } 
       
    });
     std::thread chef2([&FoodOrderSystem_, &console_mutex]()
    {
       for(int i = 11; i <20; ++i)
       {
        FoodOrderSystem_.place_order("Rice");
        std::lock_guard<std::mutex> lock(console_mutex);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
       } 
       
    });

    std::thread waiters([&FoodOrderSystem_, &console_mutex]()
    {
       for(int i = 0; i < 19; ++i)
       {
            FoodOrderSystem_.deliver_order();
             std::this_thread::sleep_for(std::chrono::milliseconds(100));
       } 
      
    });

    chef.join();
    chef2.join();
    waiters.join();
    

    return 0;
}