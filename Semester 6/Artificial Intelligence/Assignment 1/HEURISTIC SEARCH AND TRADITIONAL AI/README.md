# Heuristic Search and Traditional AI

This directory contains the Travelling Salesman Problem on the `berlin52` dataset solved with heuristic search methods. The implemented work covers dataset analysis, modeling the problem as a search task, defining the cost and fitness functions, running three heuristic algorithms, and benchmarking their results.

## Problem overview

The `berlin52` instance is a classic TSP benchmark containing 52 cities with 2D Euclidean coordinates. The goal is to build a closed tour that visits every city exactly once and returns to the starting city while minimizing the total distance traveled.

In this project, the TSP is modeled as a search problem:
*   **State:** A complete ordering of the 52 cities (a permutation of city IDs).
*   **Initial solution:** A random route or a route built with the nearest-neighbor heuristic.
*   **Cost function:** Total closed-tour distance.

## What was implemented

### 1. Dataset analysis and shared utilities

The folder `task_0_dataset_and_modeling/` contains the common infrastructure used by all algorithms:
*   Loading and parsing `data/berlin52.tsp`.
*   Representing each city with its ID and coordinates.
*   Computing Euclidean distances and evaluating full route length.
*   Generating initial solutions and creating neighbors through structural operations.

### 2. Tabu Search

The file `task_1_tabu_search/tabu_search.py` implements a Tabu Search solver. It starts from a nearest-neighbor solution, samples swap-based neighbors, and uses a tabu list to avoid cycling back to recently explored moves.

**Steps per iteration:**
1. Generate a set of neighboring solutions using swap operations.
2. Evaluate the route length for all candidates.
3. Filter out moves that are currently in the tabu list, unless they meet the aspiration criterion.
4. Select the best valid candidate, even if it is worse than the current state.
5. Update the current state and add the chosen move to the tabu list.

**Key mechanisms and parameters:**
*   **Tabu list:** A short-term memory structure (fixed-size queue) that records recent moves to prevent the algorithm from returning to a previously visited state.
*   **Aspiration criterion:** A rule that overrides the tabu status. If a tabu move results in a route shorter than the global best solution found so far, it is accepted anyway.

### 3. Simulated Annealing

The file `task_2_simulated_annealing/simulated_annealing.py` implements Simulated Annealing using random 2-opt style neighbors.

**Key mechanisms and behavior:**
*   **2-opt operator:** Reverses the order of a segment of cities within the tour. This efficiently untangles crossing paths in a TSP route.
*   **Acceptance probability:** Improving moves are always accepted. Worse moves are accepted with a probability of `exp(-delta / T)`, where `delta` is the difference in distance and `T` is the current temperature.
*   **Cooling schedule:** The temperature decreases gradually after each step using a geometric decay multiplier (e.g., `T = T * 0.99`).
*   **Early vs. late behavior:** Early in the search at high temperatures, the algorithm accepts almost any move, acting like a random walk to explore the space. Late in the search at low temperatures, the acceptance probability drops near zero for worse moves, turning the search into a greedy hill climber to fine-tune the solution.

### 4. Genetic Algorithm

The file `task_3_genetic_algorithm/genetic_algorithm.py` implements a Genetic Algorithm for TSP tours.

**A complete generation step:**
1. Evaluate the fitness of the entire population.
2. Select parents using tournament selection.
3. Produce offspring via crossover.
4. Apply mutation to the new offspring.
5. Form the next generation using the offspring and elite individuals.

**Key mechanisms and parameters:**
*   **Initialization:** The starting population includes one nearest-neighbor route to provide a solid baseline, while the rest are completely random permutations.
*   **Fitness:** Calculated as `1 / distance`. This converts the minimization problem into a maximization problem, giving higher selection weight to shorter tours.
*   **Tournament selection:** Picks a small random subset of individuals and chooses the one with the highest fitness to become a parent.
*   **Ordered Crossover (OX):** Copies a random segment from the first parent into the offspring, then fills the remaining positions with cities in the exact order they appear in the second parent. This ensures the resulting route is a valid permutation with no duplicates or missing cities.
*   **Mutation:** Randomly swaps two cities in the route with a low probability to introduce new genetic material and prevent premature convergence.
*   **Elitism:** Automatically carries over a small number of the absolute best individuals from the current generation to the next, ensuring the best solution is never lost.

## Algorithm Comparison

| Feature | Tabu Search | Simulated Annealing | Genetic Algorithm |
| :--- | :--- | :--- | :--- |
| **Core Mechanism** | Neighborhood search with memory | Probabilistic neighborhood search | Population-based evolution |
| **Exploration** | Forced by making recent moves tabu | High at high temperatures | Handled by crossover and mutation |
| **Exploitation** | Selects the best available non-tabu move | High at low temperatures | Promoted by tournament and elitism |
| **Memory** | Explicit (Tabu list) | None (Markov process) | Implicit (Population) |
| **Key Operators** | Swap, Tabu List, Aspiration | 2-opt, Temperature Cooling | OX Crossover, Swap Mutation |
| **Accepts worse moves?** | Yes, to avoid local optima | Yes, based on `exp(-delta / T)` | N/A (generates new solutions) |
| **Main Parameters** | Tabu tenure, iterations | Initial T, cooling rate | Pop. size, mutation rate, elitism |

## Benchmarking and Hyperparameters

The file `benchmarking/benchmark_algorithms.py` runs the three algorithms on the same `berlin52` dataset. Because heuristics are highly sensitive to parameter choices, the benchmark results are meaningful only relative to the current configuration.

*   **Tabu Search:** More iterations and a larger neighborhood can improve results but increase runtime. The tabu tenure dictates how aggressively the algorithm avoids revisiting recent moves.
*   **Simulated Annealing:** The initial temperature controls exploratory behavior, and the cooling rate determines how quickly the search becomes greedy. It often produces highly competitive distances on this dataset.
*   **Genetic Algorithm:** Population size affects diversity, mutation rate dictates raw exploration, and elitism determines how strongly the current best solutions are preserved. It typically requires the most parameter tuning.

## Directory structure

*   `data/berlin52.tsp`: The dataset
*   `task_0_dataset_and_modeling/tsp_utils.py`: Shared TSP functions
*   `task_1_tabu_search/tabu_search.py`: Tabu Search implementation
*   `task_2_simulated_annealing/simulated_annealing.py`: Simulated Annealing implementation
*   `task_3_genetic_algorithm/genetic_algorithm.py`: Genetic Algorithm implementation
*   `benchmarking/benchmark_algorithms.py`: Performance comparison script