from __future__ import annotations

from dataclasses import dataclass
from math import dist


@dataclass(frozen=True)
class Point:
    x: float
    y: float


def _distance(point1: Point, point2: Point) -> float:
    return dist((point1.x, point1.y), (point2.x, point2.y))


def _bruteforce(points: list[Point]) -> tuple[tuple[Point, Point], float]:
    best_pair = (points[0], points[1])
    best_distance = _distance(points[0], points[1])

    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            current_distance = _distance(points[i], points[j])
            if current_distance < best_distance:
                best_distance = current_distance
                best_pair = (points[i], points[j])

    return best_pair, best_distance


def _closest_pair_recursive(
    points_sorted_x: list[Point], points_sorted_y: list[Point]
) -> tuple[tuple[Point, Point], float]:
    n = len(points_sorted_x)
    if n <= 3:
        return _bruteforce(points_sorted_x)

    mid = n // 2
    midpoint = points_sorted_x[mid]

    left_x = points_sorted_x[:mid]
    right_x = points_sorted_x[mid:]

    left_set = set(left_x)
    left_y = [point for point in points_sorted_y if point in left_set]
    right_y = [point for point in points_sorted_y if point not in left_set]

    left_pair, left_distance = _closest_pair_recursive(left_x, left_y)
    right_pair, right_distance = _closest_pair_recursive(right_x, right_y)

    if left_distance <= right_distance:
        best_pair = left_pair
        delta = left_distance
    else:
        best_pair = right_pair
        delta = right_distance

    strip = [point for point in points_sorted_y if abs(point.x - midpoint.x) < delta]

    # In the strip, each point must be compared with only the next few points.
    for i in range(len(strip)):
        for j in range(i + 1, min(i + 8, len(strip))):
            current_distance = _distance(strip[i], strip[j])
            if current_distance < delta:
                delta = current_distance
                best_pair = (strip[i], strip[j])

    return best_pair, delta


def closest_points_divide_and_conquer(points: list[Point]) -> tuple[tuple[Point, Point], float]:
    if len(points) < 2:
        raise ValueError("At least two points are required.")

    points_sorted_x = sorted(points, key=lambda point: (point.x, point.y))
    points_sorted_y = sorted(points, key=lambda point: (point.y, point.x))
    return _closest_pair_recursive(points_sorted_x, points_sorted_y)


def main() -> None:
    sample_points = [
        Point(2, 3),
        Point(12, 30),
        Point(40, 50),
        Point(5, 1),
        Point(12, 10),
        Point(3, 4),
    ]

    pair, distance_value = closest_points_divide_and_conquer(sample_points)

    print("Closest pair:")
    print(pair[0])
    print(pair[1])
    print(f"Distance: {distance_value:.6f}")

if __name__ == "__main__":
    main()
