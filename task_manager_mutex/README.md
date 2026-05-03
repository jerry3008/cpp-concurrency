# Thread-Safe Task Manager Using Mutex (C++)

This module demonstrates how to safely manage shared resources using **mutexes** in C++.

## Objective

Create a task manager where multiple threads add integer tasks to a shared task queue.

The goal is to prevent race conditions by ensuring that only one thread can modify the queue at a time.

## Key Concepts

- Multithreading
- Shared resources
- Mutex locking
- Thread-safe task insertion
- Race condition prevention

## How It Works

Multiple threads attempt to add tasks to the same queue.

A `mutex` is used to lock access before modifying the queue.  
This ensures that one thread finishes its operation before another thread can access the shared queue.

## Files

- `main.cpp`
  - Contains the task manager implementation
  - Creates multiple threads
  - Adds tasks safely to a shared queue
  - Displays the final task queue

## How to Compile and Run

From the project root:

```bash
g++ CPP-CONCURRENCY/task_manager_mutex/main.cpp -o task_manager -pthread
./task_manager