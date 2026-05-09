# HeroStack Lock-Free Stack with Memory Ordering (C++)

This project implements a lock-free stack called `HeroStack` using C++ atomic operations and explicit memory ordering.

## Objective

Build a thread-safe stack without using traditional locks such as `std::mutex`.

The stack supports:

- `enlist`
  - Adds an element to the stack

- `deploy`
  - Removes an element from the stack

## Key Concepts

- Lock-free programming
- `std::atomic`
- Atomic pointer updates
- Compare-and-swap
- `compare_exchange_weak`
- `std::memory_order_release`
- `std::memory_order_acquire`
- Thread-safe stack operations

## How It Works

The stack is implemented using linked nodes.

The top of the stack is stored as an atomic pointer.

### Enlist Operation

The `enlist` operation pushes a new element onto the stack.

It uses `std::memory_order_release` so that the new node and its data are fully visible before the top pointer is updated.

### Deploy Operation

The `deploy` operation removes an element from the stack.

It uses `std::memory_order_acquire` so that the deploying thread safely sees the node data published by the enlist operation.

## Why Memory Ordering Matters

Memory ordering controls how operations become visible across threads.

Using release/acquire ordering ensures that:

- A producer thread safely publishes a new stack node.
- A consumer thread safely reads that node after acquiring it.
- The stack remains safe under concurrent access.

## Files

- `main.cpp`
  - Contains the `HeroStack` class
  - Implements lock-free enlist and deploy operations
  - Uses release/acquire memory ordering
  - Provides console output for each operation

## How to Compile and Run

From the repository root:

```bash
g++ hero_stack_memory_ordering/main.cpp -o hero_stack -pthread
./hero_stack

Learning Outcome

This exercise demonstrates how to apply the C++ memory model to a lock-free data structure using release and acquire synchronization.

Note

This is a learning-focused implementation. Production lock-free stacks may require additional memory reclamation strategies to handle deleted nodes safely and avoid ABA-related issues.