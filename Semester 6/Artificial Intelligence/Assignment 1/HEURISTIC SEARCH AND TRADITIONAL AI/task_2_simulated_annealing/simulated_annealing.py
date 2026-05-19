from __future__ import annotations
# pyright: reportMissingImports=false

from math import exp
from pathlib import Path
from random import Random
import sys

sys.path.append(str(Path(__file__).resolve().parents[1] / "task_0_dataset_and_modeling"))

from tsp_utils import load_berlin52, nearest_neighbor_route, random_two_opt_neighbor, route_length


def simulated_annealing(
    cities_path: str,
    initial_temperature: float = 5000.0,
    cooling_rate: float = 0.995,
    iterations: int = 4000,
    seed: int = 42,
) -> tuple[list[int], float]:
    rng = Random(seed)
    cities = load_berlin52(cities_path)

    current_route = nearest_neighbor_route(cities)
    current_distance = route_length(current_route, cities)
    best_route = current_route[:]
    best_distance = current_distance
    temperature = initial_temperature

    for _ in range(iterations):
        candidate_route = random_two_opt_neighbor(current_route, rng)
        candidate_distance = route_length(candidate_route, cities)
        delta = candidate_distance - current_distance

        if delta < 0 or rng.random() < exp(-delta / max(temperature, 1e-12)):
            current_route = candidate_route
            current_distance = candidate_distance

            if current_distance < best_distance:
                best_route = current_route[:]
                best_distance = current_distance

        temperature *= cooling_rate

    return best_route, best_distance


def main() -> None:
    cities_path = str(Path(__file__).resolve().parents[1] / "data" / "berlin52.tsp")
    best_route, best_distance = simulated_annealing(cities_path)

    print("Simulated Annealing on berlin52")
    print(f"Best distance: {best_distance:.2f}")
    print(f"Route prefix: {best_route[:10]} ...")


if __name__ == "__main__":
    main()
