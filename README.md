# AlgoCore-CPP ⚡

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++: 20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![Header-Only](https://img.shields.io/badge/library-header--only-orange.svg)](#architecture)
[![CMake: 3.20+](https://img.shields.io/badge/CMake-3.20+-green.svg)](https://cmake.org/)

> **AlgoCore-CPP** is a modern, verified, header-only competitive programming algorithms and data structures library authored in modern C++20.

Inspired by traditional competitive programming reference libraries like `code-library`, **AlgoCore-CPP** reimagines algorithmic building blocks with:
- **C++20 Concepts & Zero Overhead**: Maximum compile-time type safety with zero runtime abstraction penalties.
- **Header-Only Simplicity**: Drop `#include "algocore/..."` into any solution without external linker dependencies.
- **Formal Verification**: Every module includes automated unit tests verifying edge cases, 0-indexing / 1-indexing interfaces, and large inputs.
- **CP-Optimized Interfaces**: Designed specifically for fast keyboard prototyping during Codeforces, AtCoder, ICPC, and LeetCode competitions.

---

## 📚 Module Reference & Complexity

| Domain | Header | Data Structure / Algorithm | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Data Structures** | `algocore/data_structures/segment_tree.hpp` | Generic Segment Tree (Point Update, Range Query) | Build: $O(N)$<br>Query: $O(\log N)$<br>Update: $O(\log N)$ | $O(N)$ |
| **Data Structures** | `algocore/data_structures/fenwick_tree.hpp` | Binary Indexed Tree (Fenwick) | Build: $O(N)$<br>Query: $O(\log N)$<br>Update: $O(\log N)$ | $O(N)$ |
| **Data Structures** | `algocore/data_structures/dsu.hpp` | Disjoint Set Union (Path Compression + Rank) | Find / Unite: $O(\alpha(N))$ | $O(N)$ |
| **Graphs** | `algocore/graphs/dijkstra.hpp` | Priority-Queue Dijkstra SSSP & Path Reconstruction | $O((V + E) \log V)$ | $O(V + E)$ |
| **Graphs** | `algocore/graphs/tarjan_scc.hpp` | Tarjan's Strongly Connected Components | $O(V + E)$ | $O(V)$ |
| **Strings** | `algocore/strings/kmp.hpp` | Knuth-Morris-Pratt Prefix Function & Search | $O(\|T\| + \|P\|)$ | $O(\|P\|)$ |
| **Strings** | `algocore/strings/trie.hpp` | Array-Backed Alphabet Prefix Trie | Insert: $O(L)$<br>Search: $O(L)$ | $O(\Sigma \cdot \sum L)$ |
| **Math** | `algocore/math/modular.hpp` | `Modular<Mod>` (Inverse, Power, Division) | Ops: $O(1)$<br>Inv: $O(\log P)$<br>Pow: $O(\log E)$ | $O(1)$ |

---

## 🚀 Quickstart Example

```cpp
#include <iostream>
#include <vector>
#include "algocore/data_structures/segment_tree.hpp"
#include "algocore/math/modular.hpp"

int main() {
    // 1. Point update & range sum queries
    std::vector<int> nums = {1, 3, 5, 7, 9, 11};
    algocore::ds::SegmentTree<int> st(nums);
    std::cout << "Sum [1, 4]: " << st.query(1, 4) << "\n"; // 24

    st.update(1, 10);
    std::cout << "New Sum [1, 4]: " << st.query(1, 4) << "\n"; // 31

    // 2. High-speed modular arithmetic
    using Mint = algocore::math::Mint1e9;
    Mint a = 1000000000;
    Mint b = 10;
    std::cout << "(a + b) mod 1e9+7 = " << (a + b) << "\n"; // 3
    std::cout << "a / b mod 1e9+7 = " << (a / b) << "\n";

    return 0;
}
```

---

## 🛠️ Building & Running Tests

```bash
# Clone the repository
git clone https://github.com/OmReddyEnduri/AlgoCore-CPP.git
cd AlgoCore-CPP

# Build tests with CMake
cmake -B build -S .
cmake --build build --config Release

# Run the test executable
ctest --test-dir build --output-on-failure
# Or directly:
./build/algocore_tests
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.
Copyright (c) 2026 OmReddyEnduri.
