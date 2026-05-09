#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;

template<typename T>
class LockFreeBookStack 
{
private:
    struct Book
    {
        T title;
        Book* next;
        Book(const T& value) : title(value), next(nullptr){} 
    };
    std::atomic<Book*> top_book;
    std::mutex coutmutx;

public:
    LockFreeBookStack(): top_book(nullptr){}
    void addBook(const T& tittle)
    {
        Book* new_book = new Book(tittle);
        new_book -> next = top_book.load();
        {
            std::lock_guard<std::mutex>lk(coutmutx);
            std::cout << "Pushing: " << tittle << "\n";
            
        }
        while(!top_book.compare_exchange_weak(new_book -> next, new_book));
        
        
    }
    bool removeBook(T& result)
    {
        Book* old_book = top_book.load();
        while (old_book != nullptr && !top_book.compare_exchange_weak(old_book, old_book->next));
        if(old_book == nullptr)
        {
            std::lock_guard<std::mutex>lk(coutmutx);
             std::cout << "Pop failed - stack is empty.\n";
            return false;
        }
        
         // Print statement for pop attempt
        {
            std::lock_guard<std::mutex>lk(coutmutx);
            std::cout << "Attempting to pop...\n";
            result = old_book->title;
            delete old_book;
        }
        
        
        {
            std::lock_guard<std::mutex>lk(coutmutx);
            std::cout << "Popped: " << result << "\n";
        }
        return true;
    }
};

void addBooks(LockFreeBookStack<std::string>& stack, int start, int end) {
    for (int i = start; i < end; ++i) {
        stack.addBook("Book" + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void removeBooks(LockFreeBookStack<std::string>& stack, int count) {
    std::string title;
    for (int i = 0; i < count; ++i) {
        stack.removeBook(title);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

int main() {
    LockFreeBookStack<std::string> stack;

    std::thread t1(addBooks, std::ref(stack), 1, 10);
    std::thread t2(removeBooks, std::ref(stack), 5);
    std::thread t3(addBooks, std::ref(stack), 10, 20);
    std::thread t4(removeBooks, std::ref(stack), 5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}