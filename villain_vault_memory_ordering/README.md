# VillainVault Memory Ordering (C++)

This project demonstrates different C++ atomic memory orderings using a `VillainVault` class.

## Objective

Implement a complete class that shows how shared data can be handled across threads using:

- Relaxed ordering
- Release/acquire ordering
- Sequential consistency

## Key Concepts

- `std::atomic`
- `std::memory_order_relaxed`
- `std::memory_order_release`
- `std::memory_order_acquire`
- `std::memory_order_seq_cst`
- Thread synchronization
- Shared data visibility

## How It Works

The `VillainVault` class demonstrates three memory-ordering styles:

### 1. Relaxed Ordering

Relaxed ordering guarantees atomicity but does not guarantee ordering between operations.

This is useful when only the value update matters, not the order of other memory operations.

### 2. Release/Acquire Ordering

Release/acquire ordering is used when one thread publishes data and another thread safely reads it.

- `memory_order_release` is used when storing the ready flag.
- `memory_order_acquire` is used when loading the ready flag.

This ensures shared data written before the release store becomes visible after the acquire load.

### 3. Sequential Consistency

Sequential consistency is the strongest ordering.

It makes atomic operations appear as if they happen in one global order that all threads agree on.

## Files

- `main.cpp`
  - Contains the `VillainVault` class
  - Demonstrates relaxed operations
  - Demonstrates release/acquire synchronization
  - Demonstrates sequentially consistent operations

## How to Compile and Run

From the repository root:

```bash
g++ villain_vault_memory_ordering/main.cpp -o villain_vault -pthread
./villain_vault


Learning Outcome

This final exercise helps strengthen understanding of how different memory orderings affect synchronization, visibility, and correctness in multithreaded C++ programs.