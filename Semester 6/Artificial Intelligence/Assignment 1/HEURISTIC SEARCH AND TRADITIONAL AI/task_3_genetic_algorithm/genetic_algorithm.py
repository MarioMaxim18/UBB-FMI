from __future__ import annotations

from pathlib import Path
from random import Random
import sys

sys.path.append(str(Path(__file__).resolve().parents[1] / "task_0_dataset_and_modeling"))

from tsp_utils import (
    fitness_from_distance,
    load_berlin52,
    nearest_neighbor_route,
    random_swap_neighbor,
    random_route,
    route_length,
)


def ordered_crossover(parent1: list[int], parent2: list[int], rng: Random) -> list[int]:
    start, end = sorted(rng.sample(range(len(parent1)), 2))
    child = [None] * len(parent1)
    child[start : end + 1] = parent1[start : end + 1]

    parent2_values = [gene for gene in parent2 if gene not in child]
    insert_index = 0
    for i in range(len(child)):
        if child[i] is None:
            child[i] = parent2_values[insert_index]
            insert_index += 1

    return [gene for gene in child if gene is not None]


def tournament_selection(
    population: list[list[int]], distances: list[float], rng: Random, tournament_size: int = 4
) -> list[int]:
    indices = rng.sample(range(len(population)), tournament_size)
    best_index = min(indices, key=lambda index: distances[index])
    return population[best_index][:]


def genetic_algorithm(
    cities_path: str,
    population_size: int = 80,
    generations: int = 250,
    mutation_rate: float = 0.2,
    elitism_count: int = 4,
    seed: int = 42,
) -> tuple[list[int], float]:
    rng = Random(seed)
    cities = load_berlin52(cities_path)

    population = [nearest_neighbor_route(cities)]
    while len(population) < population_size:
        population.append(random_route(cities, rng))

    best_route = population[0][:]
    best_distance = route_length(best_route, cities)

    for _ in range(generations):
        distances = [route_length(route, cities) for route in population]

        generation_best_index = min(range(len(population)), key=lambda index: distances[index])
        if distances[generation_best_index] < best_distance:
            best_distance = distances[generation_best_index]
            best_route = population[generation_best_index][:]

        ranked = sorted(zip(population, distances), key=lambda item: item[1])
        new_population = [route[:] for route, _ in ranked[:elitism_count]]

        while len(new_population) < population_size:
            parent1 = tournament_selection(population, distances, rng)
            parent2 = tournament_selection(population, distances, rng)
            child = ordered_crossover(parent1, parent2, rng)

            if rng.random() < mutation_rate:
                child = random_swap_neighbor(child, rng)

            new_population.append(child)

        population = new_population

    return best_route, best_distance


def main() -> None:
    cities_path = str(Path(__file__).resolve().parents[1] / "data" / "berlin52.tsp")
    best_route, best_distance = genetic_algorithm(cities_path)

    print("Genetic Algorithm on berlin52")
    print(f"Best distance: {best_distance:.2f}")
    print(f"Fitness: {fitness_from_distance(best_distance):.8f}")
    print(f"Route prefix: {best_route[:10]} ...")


if __name__ == "__main__":
    main()
