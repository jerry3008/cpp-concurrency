# Atomic Memory Ordering (C++)

This project demonstrates how atomic operations and memory ordering work in C++ concurrency.

## Objective

Complete a class that safely manages shared data across threads using atomic variables and explicit memory orders.

## Key Concepts

- `std::atomic`
- Atomic load and store operations
- Memory ordering
- `std::memory_order_relaxed`
- `std::memory_order_release`
- `std::memory_order_acquire`
- Thread-safe communication

## How It Works

Atomic variables allow multiple threads to read and write shared values safely without using a mutex.

Memory ordering controls how operations are seen across threads.

Common memory orders used in this exercise:

- `memory_order_relaxed`
  - Used when atomicity is needed, but ordering between threads is not important.

- `memory_order_release`
  - Used when one thread publishes data to other threads.

- `memory_order_acquire`
  - Used when another thread reads the published data safely.

## Files

- `main.cpp`
  - Contains the atomic memory ordering implementation.

## How to Compile and Run

From the repository root:

```bash
g++ atomic_memory_ordering/main.cpp -o atomic_ordering -pthread
./atomic_ordering

Learning Outcome

This task helps build understanding of how atomic variables coordinate data safely across threads without traditional locks.