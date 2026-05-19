from __future__ import annotations

from dataclasses import dataclass
from math import sqrt
from random import Random


@dataclass(frozen=True)
class City:
    id: int
    x: float
    y: float


def load_berlin52(path: str) -> list[City]:
    cities: list[City] = []
    in_section = False

    with open(path, "r", encoding="utf-8") as file:
        for raw_line in file:
            line = raw_line.strip()

            if not line:
                continue
            if line == "NODE_COORD_SECTION":
                in_section = True
                continue
            if line == "EOF":
                break
            if not in_section:
                continue

            city_id, x_coord, y_coord = line.split()
            cities.append(City(int(city_id), float(x_coord), float(y_coord)))

    return cities


def euclidean_distance(city1: City, city2: City) -> float:
    return sqrt((city1.x - city2.x) ** 2 + (city1.y - city2.y) ** 2)


def route_length(route: list[int], cities: list[City]) -> float:
    if len(route) != len(cities):
        raise ValueError("The route must contain each city exactly once.")

    city_by_id = {city.id: city for city in cities}
    total = 0.0

    for index in range(len(route)):
        current_city = city_by_id[route[index]]
        next_city = city_by_id[route[(index + 1) % len(route)]]
        total += euclidean_distance(current_city, next_city)

    return total


def random_route(cities: list[City], rng: Random | None = None) -> list[int]:
    generator = rng if rng is not None else Random()
    route = [city.id for city in cities]
    generator.shuffle(route)
    return route


def nearest_neighbor_route(cities: list[City], start_id: int | None = None) -> list[int]:
    if not cities:
        return []

    city_by_id = {city.id: city for city in cities}
    unvisited = {city.id for city in cities}
    current_id = start_id if start_id is not None else cities[0].id
    route = [current_id]
    unvisited.remove(current_id)

    while unvisited:
        current_city = city_by_id[current_id]
        next_id = min(
            unvisited,
            key=lambda candidate_id: euclidean_distance(current_city, city_by_id[candidate_id]),
        )
        route.append(next_id)
        unvisited.remove(next_id)
        current_id = next_id

    return route


def swap_two_positions(route: list[int], i: int, j: int) -> list[int]:
    new_route = route[:]
    new_route[i], new_route[j] = new_route[j], new_route[i]
    return new_route


def reverse_segment(route: list[int], i: int, j: int) -> list[int]:
    new_route = route[:]
    new_route[i : j + 1] = reversed(new_route[i : j + 1])
    return new_route


def random_swap_neighbor(route: list[int], rng: Random) -> list[int]:
    i, j = sorted(rng.sample(range(len(route)), 2))
    return swap_two_positions(route, i, j)


def random_two_opt_neighbor(route: list[int], rng: Random) -> list[int]:
    i, j = sorted(rng.sample(range(len(route)), 2))
    return reverse_segment(route, i, j)


def fitness_from_distance(distance: float) -> float:
    return 1.0 / distance
