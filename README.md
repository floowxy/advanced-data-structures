# Pattern Matching

Implementation of pattern matching algorithms for the Advanced Data Structures course.

## KMP Algorithm

This branch contains an implementation of the Knuth-Morris-Pratt (KMP) string matching algorithm in Rust.

KMP searches for occurrences of a pattern inside a text using the LPS (Longest Proper Prefix which is also a Suffix) array to avoid unnecessary comparisons.

## Project Structure

```text
src/
├── main.rs
├── kmp_search.rs
└── build_lps.rs
```

- `main.rs` — program entry point.
- `kmp_search.rs` — KMP search algorithm.
- `build_lps.rs` — construction of the LPS array.

## How to Run

Make sure Rust and Cargo are installed.

Clone the repository and switch to the `PatternMatching` branch:

```bash
git clone https://github.com/floowxy/advanced-data-structures.git
cd advanced-data-structures
git switch PatternMatching
```

Enter the Rust project:

```bash
cd PatternMatching
```

Run the program:

```bash
cargo run
```

Example output:

```text
Text: ABABABAC
Pattern: ABABAC
Matches: [2]
```

## Technology

- Rust

## Complexity

- LPS construction: `O(len_pattern)`
- KMP search: `O(len_text)`
- Total complexity: `O(len_text + len_pattern)`

Where:

- `len_text` is the length of the text.
- `len_pattern` is the length of the pattern.

## Author

Diego Sotelo