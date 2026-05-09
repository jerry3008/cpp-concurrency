# Lock-Free Stack (C++)

This project implements a basic lock-free stack using C++ atomic operations.

## Objective

Create a `LockFreeStack` class that supports thread-safe add and remove operations without using traditional locks such as `std::mutex`.

## Key Concepts

- Lock-free programming
- `std::atomic`
- Compare-and-swap
- `compare_exchange_weak`
- Thread-safe stack operations
- Concurrent push and pop
- Non-blocking synchronization

## How It Works

The stack stores nodes linked together through pointers.

The top of the stack is managed using an atomic pointer.

### Add Operation

When adding a new value:

1. Create a new node.
2. Point the new node to the current stack top.
3. Use `compare_exchange_weak` to atomically update the top.
4. Retry if another thread changed the stack at the same time.

### Remove Operation

When removing a value:

1. Read the current top node.
2. If the stack is empty, return safely.
3. Move the top pointer to the next node using `compare_exchange_weak`.
4. Retry if another thread changed the stack at the same time.
5. Return the removed value.

## Files

- `main.cpp`
  - Contains the `LockFreeStack` class
  - Demonstrates add and remove operations
  - Prints clear output for each stack operation

## How to Compile and Run

From the repository root:

```bash
g++ lock_free_stack/main.cpp -o lock_free_stack -pthread
./lock_free_stack
Learning Outcome

This project helps demonstrate how atomic compare-and-swap operations can be used to build thread-safe data structures without mutexes.

Note

This is a learning-focused implementation. Production lock-free stacks may require additional handling for memory reclamation and the ABA problem.