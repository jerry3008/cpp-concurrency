# Producer-Consumer with Condition Variable (C++)

This project demonstrates the **Producer-Consumer pattern** using C++ threads, mutexes, condition variables, and a completion flag.

## Objective

The goal is to coordinate superhero mission issuing and mission handling safely between multiple threads.

A producer thread adds missions to a shared queue, while a consumer thread waits for missions and processes them.

## Key Concepts

- Producer-Consumer pattern
- `std::thread`
- `std::mutex`
- `std::condition_variable`
- Shared queue synchronization
- Completion flag
- Race condition prevention

## How It Works

1. The producer creates superhero missions.
2. Each mission is added to a shared queue.
3. The condition variable notifies the consumer that work is available.
4. The consumer waits until:
   - missions are available, or
   - the producer is finished.
5. The consumer processes all missions and exits safely when no more work remains.

## Files

- `main.cpp`
  - Contains the producer-consumer implementation.
  - Uses condition variables to coordinate mission issuing and handling.

## How to Compile and Run

From the repository root:

```bash
g++ producer_consumer_condition_variable/main.cpp -o missions -pthread
./missions