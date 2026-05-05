# Dining Philosophers Thread Setup (C++)

This project focuses on setting up and starting threads for the Dining Philosophers Problem.

## Objective

Create one thread for each philosopher. Each thread calls the `dine` function and receives:

- The philosopher ID
- The left fork
- The right fork

## Key Concepts

- `std::thread`
- Passing function arguments to threads
- Using references with `std::ref`
- Dining Philosophers Problem
- Deadlock prevention setup

## How It Works

1. A list of forks is created.
2. A list of philosopher threads is created.
3. Each philosopher thread calls `dine`.
4. The correct left and right forks are passed to each philosopher.
5. All threads are joined before the program exits.

## Files

- `main.cpp`
  - Contains the thread creation logic for each philosopher.

## How to Compile and Run

From the repository root:

```bash
g++ dining_philosophers_threads/main.cpp -o philosophers_threads -pthread
./philosophers_threads


Learning Outcome

This task helps practice creating multiple threads and passing the correct shared resources safely into each thread.