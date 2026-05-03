# Producer-Consumer Tuple Sum (C++)

This project demonstrates the **Producer-Consumer pattern** using C++ threads, mutexes, and condition variables.

## Objective

Create a thread-safe system where producers generate tuples of two integers, and consumers retrieve those tuples to calculate their sums.

## Key Concepts

- Producer-Consumer pattern
- `std::thread`
- `std::mutex`
- `std::condition_variable`
- Thread-safe shared buffer
- Race condition prevention
- Safe result storage

## How It Works

1. Producers generate tuples such as `(3, 5)`.
2. The tuples are added to a shared buffer.
3. Consumers wait until data is available.
4. Consumers retrieve tuples from the buffer.
5. Each consumer calculates the sum.
6. The computed results are stored safely.

## Files

- `main.cpp`
  - Contains the thread-safe buffer class
  - Implements producer logic
  - Implements consumer logic
  - Stores calculated sums

## How to Compile and Run

From the repository root:

```bash
g++ producer_consumer_tuple_sum/main.cpp -o tuple_sum -pthread
./tuple_sum