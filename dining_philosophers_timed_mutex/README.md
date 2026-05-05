# Dining Philosophers with Timed Mutex (C++)

This project demonstrates the Dining Philosophers problem using `std::timed_mutex`.

## Objective

Update the philosopher fork-locking logic so each philosopher attempts to acquire forks for a limited time instead of waiting forever.

This improves responsiveness when multiple philosophers are competing for the same forks.

## Key Concepts

- Dining Philosophers problem
- `std::thread`
- `std::timed_mutex`
- `try_lock_for`
- Resource contention
- Deadlock avoidance
- Retry-based synchronization

## How It Works

1. Each fork is represented by a `std::timed_mutex`.
2. A philosopher attempts to lock one fork.
3. The philosopher then attempts to lock the second fork for up to 50 milliseconds.
4. If both forks are acquired, the philosopher eats.
5. If the second fork cannot be acquired in time, the philosopher releases the first fork and retries later.
6. This prevents philosophers from blocking forever while waiting for forks.

## Files

- `main.cpp`
  - Contains the Dining Philosophers implementation
  - Uses `std::timed_mutex`
  - Demonstrates timed locking with `try_lock_for`

## How to Compile and Run

From the repository root:

```bash
g++ dining_philosophers_timed_mutex/main.cpp -o philosophers -pthread
./philosophers

Learning Outcome

This project shows how std::timed_mutex can improve thread responsiveness by allowing threads to time out and retry instead of waiting indefinitely.