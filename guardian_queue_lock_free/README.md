# GuardianQueue Lock-Free Queue (C++)

This project implements a lock-free queue called `GuardianQueue` using atomic operations in C++.

## Objective

Build a queue that supports thread-safe `enqueue` and `dequeue` operations without using traditional locks such as `std::mutex`.

## Key Concepts

- Lock-free data structures
- `std::atomic`
- Atomic pointer updates
- Compare-and-swap
- `compare_exchange_weak`
- Thread-safe queue operations
- Concurrent enqueue and dequeue
- Non-blocking synchronization

## How It Works

The queue is implemented using linked nodes and atomic pointers.

A dummy node is used to simplify enqueue and dequeue logic.

The queue keeps track of:

- `head`
  - Points to the front of the queue

- `tail`
  - Points to the back of the queue

Both pointers are updated using atomic compare-and-swap operations.

## Enqueue Operation

1. Create a new node.
2. Read the current tail.
3. Check whether the tail is still valid.
4. Attempt to link the new node to the end of the queue.
5. Move the tail pointer forward.
6. Retry if another thread changed the queue at the same time.

## Dequeue Operation

1. Read the current head.
2. Read the next node after head.
3. If the queue is empty, return safely.
4. Attempt to move the head pointer forward.
5. If successful, return the dequeued value.
6. Retry if another thread changed the queue at the same time.

## Files

- `main.cpp`
  - Contains the `GuardianQueue` class
  - Implements lock-free enqueue and dequeue operations
  - Sets up multiple threads to test concurrent queue behavior
  - Prints clear console output for each operation

## How to Compile and Run

From the repository root:

```bash
g++ guardian_queue_lock_free/main.cpp -o guardian_queue -pthread
./guardian_queue

Learning Outcome

This project demonstrates how atomic operations can be used to build a concurrent queue without using mutex locks.

It also strengthens understanding of:

Lock-free programming
Safe pointer updates
Queue integrity under concurrency
Thread testing for shared data structures
Note

This is a learning-focused implementation. Production lock-free queues often require additional memory reclamation techniques to avoid memory safety issues such as ABA problems and unsafe node deletion.