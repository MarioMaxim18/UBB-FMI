from __future__ import annotations

from dataclasses import dataclass
from math import dist
from typing import Iterable


@dataclass(frozen=True)
class Point:
    x: float
    y: float


def closest_points_bruteforce(points: Iterable[Point]) -> tuple[tuple[Point, Point], float]:
    point_list = list(points)
    if len(point_list) < 2:
        raise ValueError("At least two points are required.")

    best_pair = (point_list[0], point_list[1])
    best_distance = dist((point_list[0].x, point_list[0].y), (point_list[1].x, point_list[1].y))

    for i in range(len(point_list)):
        for j in range(i + 1, len(point_list)):
            current_distance = dist(
                (point_list[i].x, point_list[i].y),
                (point_list[j].x, point_list[j].y),
            )
            if current_distance < best_distance:
                best_distance = current_distance
                best_pair = (point_list[i], point_list[j])

    return best_pair, best_distance


def main() -> None:
    sample_points = [
        Point(2, 3),
        Point(12, 30),
        Point(40, 50),
        Point(5, 1),
        Point(12, 10),
        Point(3, 4),
    ]

    pair, distance_value = closest_points_bruteforce(sample_points)

    print("Closest pair:")
    print(pair[0])
    print(pair[1])
    print(f"Distance: {distance_value:.6f}")

if __name__ == "__main__":
    main()
