from __future__ import annotations
# pyright: reportMissingImports=false

from pathlib import Path
from time import perf_counter
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.append(str(ROOT / "task_1_tabu_search"))
sys.path.append(str(ROOT / "task_2_simulated_annealing"))
sys.path.append(str(ROOT / "task_3_genetic_algorithm"))

from genetic_algorithm import genetic_algorithm
from simulated_annealing import simulated_annealing
from tabu_search import tabu_search


def benchmark(name: str, solver, dataset_path: str) -> tuple[str, float, float]:
    start = perf_counter()
    _, best_distance = solver(dataset_path)
    elapsed = perf_counter() - start
    return name, best_distance, elapsed


def main() -> None:
    dataset_path = str(ROOT / "data" / "berlin52.tsp")

    results = [
        benchmark("Tabu Search", tabu_search, dataset_path),
        benchmark("Simulated Annealing", simulated_annealing, dataset_path),
        benchmark("Genetic Algorithm", genetic_algorithm, dataset_path),
    ]

    results.sort(key=lambda item: item[1])

    print("Benchmark on berlin52")
    print()
    for name, distance, elapsed in results:
        print(f"{name}:")
        print(f"  Best distance: {distance:.2f}")
        print(f"  Runtime: {elapsed:.3f} seconds")
        print()


if __name__ == "__main__":
    main()
