# Advanced Data Structures

Repository for the Advanced Data Structures course.

This repository contains implementations, experiments, and exercises related to advanced data structures and algorithms.

## Branches

Each topic is developed in its own branch.

- `G4-HYPERLOGLOG` — HyperLogLog algorithm.
- `PatternMatching` — Knuth-Morris-Pratt (KMP) pattern matching algorithm.
- `BruteForce` — Brute Force pattern matching algorithm.
- `Hashing` — Hash Table with collision handling using Separate Chaining.

## Implementations

### Pattern Matching

The `PatternMatching` branch contains an implementation of the Knuth-Morris-Pratt (KMP) algorithm in Rust.

KMP uses the LPS (Longest Proper Prefix which is also a Suffix) array to avoid unnecessary comparisons.

Complexity:

- LPS construction: `O(len_pattern)`
- Search: `O(len_text)`
- Total: `O(len_text + len_pattern)`

### Brute Force

The `BruteForce` branch contains a simple pattern matching implementation in Rust.

The algorithm compares the pattern from every possible position in the text.

Complexity:

- Worst case: `O(len_text * len_pattern)`
- Auxiliary space: `O(1)`

### Hashing

The `Hashing` branch contains a Hash Table implementation in Rust.

It includes:

- Hash function
- Insertion
- Search
- Deletion
- Collision handling using Separate Chaining
- Linked List for collision resolution

Average complexity:

- Insert: `O(1)`
- Search: `O(1)`
- Delete: `O(1)`

Worst case with many collisions:

- `O(n)`

### HyperLogLog

The `G4-HYPERLOGLOG` branch contains an implementation of the HyperLogLog probabilistic algorithm for cardinality estimation.

## Technologies

- Rust
- C++

## How to Use

Clone the repository:

```bash
git clone https://github.com/floowxy/advanced-data-structures.git
cd advanced-data-structures
