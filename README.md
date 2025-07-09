# Algorithms
This repository contains seven take-home programming assignments covering fundamental algorithms topics: sorting, selection, dynamic programming, graph search, dependency resolution, and more.


## Technology Stack
- **Language:** C++ (ISO C++11)  
- **Compiler:** g++ (GNU GCC)  
- **Build Tools:** GNU Make or command-line `g++` invocations  
- **Standard Library:** STL containers, algorithms, `<vector>`, `<string>`, `<queue>`, `<stack>`, `<limits>`  
- **Testing:** Provided `test.cpp` harnesses on METU’s VPL (ODTUCLASS)

## Assignments Overview

1. **Selection & QuickSort3** (`the1/`)
   - **Problem:** Implement `select_k_with_quick_sort3` (full sort) and `quick_select3` (partial) with three-way partitioning to find the k<sup>th</sup> smallest element, counting swaps and recursion.

2. **Multi-Digit String Radix Sort** (`the2/`)
   - **Problem:** Sort an array of uppercase strings using group-based RadixSort with CountingSort subroutine, return iteration count. 

3. **Island Perimeter Planting (DP)** (`the3/`)
   - **Problem:** Compute minimal planting cost along island perimeter with adjacency constraints via bottom-up DP. 

4. **Cake Cutting (DP)** (`the4/`)
   - **Problem:** Partition a rectangular cake into "tasty" slices of given dimensions, minimizing waste area using dynamic programming. 

5. **Work Package Scheduling** (`the5/`)
   - **Problem:** Identify interdependent work items (strongly connected components) and produce a valid topological order of packages. 

6. **Friendship Scores (Shortest Paths)** (`the6/`)
   - **Problem:** Given a directed weighted graph of email interactions, compute pairwise friendship scores based on all-pairs shortest paths. 

7. **Longest Path to Home** (`the7/`)
   - **Problem:** Find the longest simple path between two nodes in a weighted directed graph; use exhaustive search for non-DAGs and DP for DAGs.  
