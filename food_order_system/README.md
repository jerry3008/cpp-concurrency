# Food Order System Producer-Consumer (C++)

This project implements a complete **Producer-Consumer system** in C++ using a restaurant example.

Chefs act as producers by placing food orders, while waiters act as consumers by delivering those orders to customers.

## Objective

Create a thread-safe food order system using:

- `std::thread`
- `std::mutex`
- `std::condition_variable`
- A shared order queue

## How It Works

1. Chefs create food orders.
2. Orders are added to a shared queue.
3. Waiters wait until orders are available.
4. Waiters remove orders from the queue and deliver them.
5. Synchronization prevents race conditions.
6. A completion flag allows waiters to stop safely when all orders are done.

## Key Concepts

- Producer-Consumer pattern
- Thread synchronization
- Mutex locking
- Condition variables
- Shared queue management
- Safe thread shutdown

## Files

- `main.cpp`
  - Contains the `FoodOrderSystem` class
  - Implements chef producer logic
  - Implements waiter consumer logic
  - Demonstrates safe communication between threads

## How to Compile and Run

From the repository root:

```bash
g++ food_order_system/main.cpp -o food_orders -pthread
./food_orders


Learning Outcome

This project demonstrates how to build a complete concurrent system where multiple producer and consumer threads safely communicate through a shared queue.