#include <atomic>
#include <thread>
#include <iostream>

class VillainVault {
public:
    void unlock_vault_relaxed() 
    {
        code_relaxed_.store(42, std::memory_order_relaxed);
        vault_open_relaxed_.store(true, std::memory_order_relaxed);
    }
    
    void access_vault_relaxed()
    {
        while(!vault_open_relaxed_.load(std::memory_order_relaxed));
        std::cout << "Relaxed Value: " << code_relaxed_.load(std::memory_order_relaxed) << std::endl;
    }

    // TODO: Implement the method to unlock the vault with release/acquire memory order
    void unlock_vault_release_acquire() 
    {
        code_release_acquire_.store(42, std::memory_order_release);
        vault_open_release_acquire_.store(true, std::memory_order_release);
    }
    
    void access_vault_release_acquire() 
    {
        while (!vault_open_release_acquire_.load(std::memory_order_acquire));
        std::cout << "Release/Acquire Value: " << code_release_acquire_.load(std::memory_order_acquire) << std::endl;
    }
    
    void unlock_vault_seq_cst() 
    {
        code_seq_cst_.store(42, std::memory_order_seq_cst);
        vault_open_seq_cst_.store(true, std::memory_order_seq_cst);
        
        
    }
    void access_vault_seq_cst() {
        while (!vault_open_seq_cst_.load(std::memory_order_seq_cst));
        std::cout << "Seq Cst Value: " << code_seq_cst_.load(std::memory_order_seq_cst) << std::endl;
    }

private:
    std::atomic<int> code_relaxed_{0};
    std::atomic<bool> vault_open_relaxed_{false};

    std::atomic<int> code_release_acquire_{0};
    std::atomic<bool> vault_open_release_acquire_{false};

    std::atomic<int> code_seq_cst_{0};
    std::atomic<bool> vault_open_seq_cst_{false};
};

int main() {
    VillainVault vault;

    std::thread unlockRelaxed(&VillainVault::unlock_vault_relaxed, &vault);
    std::thread accessRelaxed(&VillainVault::access_vault_relaxed, &vault);
    unlockRelaxed.join();
    accessRelaxed.join();

    std::thread unlockReleaseAcquire(&VillainVault::unlock_vault_release_acquire, &vault);
    std::thread accessReleaseAcquire(&VillainVault::access_vault_release_acquire, &vault);
    unlockReleaseAcquire.join();
    accessReleaseAcquire.join();

    std::thread unlockSeqCst(&VillainVault::unlock_vault_seq_cst, &vault);
    std::thread accessSeqCst(&VillainVault::access_vault_seq_cst, &vault);
    unlockSeqCst.join();
    accessSeqCst.join();

    return 0;
}