# GadgetStack Lock-Free Stack (C++)

This project implements a fully functional lock-free stack using atomic operations in C++.

## Objective

Create a `GadgetStack` class that supports thread-safe `add` and `remove` operations without using traditional locks such as `std::mutex`.

## Key Concepts

- Lock-free data structures
- `std::atomic`
- Atomic pointer updates
- Compare-and-swap
- `compare_exchange_weak`
- Thread-safe stack operations
- Non-blocking synchronization

## How It Works

The stack is implemented as a linked list where each node stores a gadget value and a pointer to the next node.

The top of the stack is stored as an atomic pointer.

### Add Operation

1. Create a new node.
2. Point the new node to the current top of the stack.
3. Use `compare_exchange_weak` to update the top pointer atomically.
4. If another thread changes the top first, retry until the add succeeds.

### Remove Operation

1. Read the current top node.
2. If the stack is empty, report that there is nothing to remove.
3. Attempt to move the top pointer to the next node using `compare_exchange_weak`.
4. If another thread changes the stack first, retry.
5. Return or display the removed gadget value.

## Files

- `main.cpp`
  - Contains the `GadgetStack` class
  - Implements lock-free add and remove operations
  - Provides console output for each operation

## How to Compile and Run

From the repository root:

```bash
g++ gadget_stack_lock_free/main.cpp -o gadget_stack -pthread
./gadget_stack


Learning Outcome

This project demonstrates how atomic compare-and-swap operations can be used to build thread-safe stack behavior without mutex locks.

Note

This is a learning-focused implementation. Real-world lock-free stacks often require additional memory reclamation techniques to safely handle deleted nodes and avoid issues such as the ABA problem.