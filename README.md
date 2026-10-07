# Delivery Truck Pallet Packing Optimization

A high-performance C++ algorithmic suite designed to solve the **0/1 Knapsack Problem** in the context of commercial logistics. This project evaluates and benchmarks multiple algorithmic paradigms—ranging from exact optimal solvers to high-speed heuristics—to determine the optimal selection of pallets that maximizes total shipment value within strict truck weight limits.

Developed for the **Design of Algorithms (DA)** course at the **Faculty of Engineering of the University of Porto (FEUP)**.

---

## Overview

In freight transportation, maximizing shipment profitability while strictly adhering to vehicle gross weight ratings is a fundamental optimization problem. Modeling this challenge as a 0/1 Knapsack Problem involves:

* **Knapsack:** Delivery truck capacity ($W$).
* **Items:** Pallets, each defined by an identifier, weight ($w_i$), and profit ($p_i$).
* **Objective:** Select a subset of pallets maximizing $\sum p_i$ such that $\sum w_i \le W$, where items cannot be fractioned.

This repository provides an end-to-end framework featuring both an interactive CLI and an automated batch processing pipeline for large-scale benchmarking.

---

## Implemented Algorithms

| Algorithm | Paradigm | Time Complexity | Space Complexity | Optimality Guarantee |
| --- | --- | --- | --- | --- |
| **Exhaustive Search** | Brute-force / Bitmasking | $O(2^n)$ | $O(n)$ | Optimal (exact) |
| **Dynamic Programming** | Bottom-up Memoization | $O(n \cdot W)$ | $O(n \cdot W)$ | Optimal (exact) |
| **Greedy Heuristic** | Approximation (Ratio-based) | $O(n \log n)$ | $O(n)$ | Suboptimal (approximate) |
| **Branch & Bound (ILP)** | State Space Search | $O(2^n)$ worst-case | $O(2^n)$ worst-case | Optimal (exact) |

### 1. Exhaustive Search (Brute Force)

* Evaluates all $2^n$ possible pallet combinations using bitmask generation.
* Guaranteed exact solution, constrained to $n \le 32$ to prevent integer overflow and excessive runtimes.
* Breaks ties by favoring subsets with the lowest pallet count.

### 2. Dynamic Programming

* Builds a 2D table of dimensions $(n + 1) \times (W + 1)$ storing optimal subproblem values alongside multi-criteria tie-breaking state.
* Employs deterministic tie-breaking: when profits match, it favors solutions with fewer pallets, followed by lower pallet ID sums.
* Reconstructs the exact item set using full table backtracking.

### 3. Greedy Approximation

* Sorts pallets descending by profit-to-weight efficiency ratio ($p_i / w_i$).
* Iteratively packs items until the weight capacity is reached.
* Provides near-instantaneous approximations for large-scale datasets where exact solvers are computationally infeasible.

### 4. Branch & Bound / Integer Linear Programming

* Formulates the 0/1 decision problem through a priority queue-driven best-first state-space search.
* Uses continuous fractional knapsack linear relaxations to compute sharp upper bounds for node pruning.
* Prunes non-promising search branches dynamically, drastically outperforming brute-force search on intermediate datasets.

---

## Project Structure

```text
.
├── docs/
│   └── datasets/              # Benchmark CSV datasets (01 to 10)
├── src/
│   ├── batchLogic.cpp         # Headless batch execution logic
│   ├── bruteForceAlg.cpp      # Exhaustive bitmask search implementation
│   ├── dynamicProgAlg.cpp     # Dynamic programming table & backtracking
│   ├── greedyAlg.cpp          # Ratio-based greedy heuristic
│   ├── ILPAlg.cpp             # Branch & Bound ILP solver
│   ├── main.cpp               # CLI entrypoint and argument routing
│   ├── menuLogic.cpp          # Interactive terminal UI
│   ├── parseDataset.cpp       # CSV parsing utilities
│   └── ...                    # Corresponding header files (.h)
└── README.md

```

---

## Dataset Format

Input instances are parsed from paired CSV files located in `docs/datasets/`:

1. **`TruckAndPallets_<X>.csv`:** Contains the truck weight capacity and total available pallets.
```csv
Capacity,Pallets
100,9

```


2. **`Pallets_<X>.csv`:** Contains itemized records of pallet ID, weight, and profit.
```csv
Pallet,Weight,Profit
1,70,10
2,60,5
3,50,10

```



---

## Getting Started

### Prerequisites

* C++17 compatible compiler (`g++` or `clang++`)
* CMake (3.16+) or standard Make utility

### Compilation

Compile directly using `g++`:

```bash
g++ -std=c++17 -O3 src/*.cpp -o Project02

```

---

## Usage

The application supports both an interactive terminal interface and a scriptable batch mode.

### 1. Interactive Mode

Run the executable without arguments to launch the terminal menu:

```bash
./Project02

```

From the interactive menu, select the dataset index (1–10) and the algorithm to execute.

### 2. Batch Mode

Run non-interactively by specifying the dataset index and algorithm ID directly via command-line arguments:

```bash
./Project02 <DataSetNumber> <AlgorithmNumber>

```

#### Parameters:

* `<DataSetNumber>`: Integer from `1` to `10` corresponding to the target dataset.
* `<AlgorithmNumber>`: Integer from `1` to `4`:
* `1` - Exhaustive Search (Brute Force)
* `2` - Dynamic Programming
* `3` - Greedy Heuristic
* `4` - Integer Linear Programming (Branch & Bound)



**Example:**

```bash
# Execute Dynamic Programming on Dataset 05
./Project02 5 2

```

Results are written directly to `src/output.txt`, detailing chosen pallets, total weight, and maximized profit.

---

## Performance Insights & Trade-Offs

* **Scalability vs. Optimality:** Exhaustive search guarantees optimality but rapidly becomes intractable beyond $n = 30$ due to $O(2^n)$ complexity.
* **Memory Constraints:** Dynamic Programming runs fast on small to moderate capacities ($W$) but requires memory proportional to $O(n \cdot W)$, which scales heavily on large capacities.
* **Pruning Efficiency:** Branch & Bound effectively navigates large search spaces, achieving exact solutions in a fraction of brute-force iterations when upper-bound pruning is tight.
* **Heuristic Precision:** The Greedy algorithm runs near-instantaneously ($O(n \log n)$), serving as an effective baseline for massive logistics instances where pseudo-polynomial memory is unavailable.

---
