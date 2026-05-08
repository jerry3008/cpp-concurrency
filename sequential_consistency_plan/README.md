# Sequential Consistency Plan (C++)

This project demonstrates how to use atomic operations with sequential consistency in C++.

## Objective

Complete a class that sets and checks a shared plan across multiple threads using the correct memory ordering.

## Key Concepts

- `std::atomic`
- `std::memory_order_seq_cst`
- Sequential consistency
- Shared data safety
- Multithreaded visibility

## What Sequential Consistency Means

Sequential consistency is the strongest memory ordering in C++ atomics.

It makes atomic operations appear as if they happen in one single global order that all threads agree on.

## How It Works

1. One thread sets a plan using an atomic operation.
2. Another thread checks whether the plan has been set.
3. `std::memory_order_seq_cst` ensures the operation order is consistent across threads.

## Files

- `main.cpp`
  - Contains the sequential consistency exercise implementation.

## How to Compile and Run

From the repository root:

```bash
g++ sequential_consistency_plan/main.cpp -o seq_plan -pthread
./seq_plan

Learning Outcome

This task helps demonstrate how sequential consistency keeps shared atomic state predictable across threads.