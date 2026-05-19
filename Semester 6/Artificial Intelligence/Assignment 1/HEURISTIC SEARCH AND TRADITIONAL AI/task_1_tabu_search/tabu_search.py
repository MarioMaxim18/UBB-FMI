from __future__ import annotations

from collections import deque
from pathlib import Path
from random import Random
import sys

sys.path.append(str(Path(__file__).resolve().parents[1] / "task_0_dataset_and_modeling"))

from tsp_utils import load_berlin52, nearest_neighbor_route, route_length, swap_two_positions


def tabu_search(
    cities_path: str,
    iterations: int = 300,
    neighborhood_size: int = 120,
    tabu_tenure: int = 20,
    seed: int = 42,
) -> tuple[list[int], float]:
    rng = Random(seed)
    cities = load_berlin52(cities_path)

    current_route = nearest_neighbor_route(cities)
    current_distance = route_length(current_route, cities)
    best_route = current_route[:]
    best_distance = current_distance

    tabu_list: deque[tuple[int, int]] = deque(maxlen=tabu_tenure)

    for _ in range(iterations):
        best_candidate_route: list[int] | None = None
        best_candidate_distance = float("inf")
        best_move: tuple[int, int] | None = None

        for _ in range(neighborhood_size):
            i, j = sorted(rng.sample(range(len(current_route)), 2))
            move = (i, j)
            candidate_route = swap_two_positions(current_route, i, j)
            candidate_distance = route_length(candidate_route, cities)

            if move in tabu_list and candidate_distance >= best_distance:
                continue

            if candidate_distance < best_candidate_distance:
                best_candidate_route = candidate_route
                best_candidate_distance = candidate_distance
                best_move = move

        if best_candidate_route is None or best_move is None:
            break

        current_route = best_candidate_route
        current_distance = best_candidate_distance
        tabu_list.append(best_move)

        if current_distance < best_distance:
            best_route = current_route[:]
            best_distance = current_distance

    return best_route, best_distance


def main() -> None:
    cities_path = str(Path(__file__).resolve().parents[1] / "data" / "berlin52.tsp")
    best_route, best_distance = tabu_search(cities_path)

    print("Tabu Search on berlin52")
    print(f"Best distance: {best_distance:.2f}")
    print(f"Route prefix: {best_route[:10]} ...")


if __name__ == "__main__":
    main()
