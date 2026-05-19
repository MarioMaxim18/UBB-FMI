from __future__ import annotations

import heapq


def dijkstra(graph: dict[str, dict[str, float]], source: str) -> tuple[dict[str, float], dict[str, str | None]]:
    distances = {node: float("inf") for node in graph}
    previous: dict[str, str | None] = {node: None for node in graph}
    distances[source] = 0.0

    priority_queue: list[tuple[float, str]] = [(0.0, source)]

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            candidate_distance = current_distance + weight
            if candidate_distance < distances[neighbor]:
                distances[neighbor] = candidate_distance
                previous[neighbor] = current_node
                heapq.heappush(priority_queue, (candidate_distance, neighbor))

    return distances, previous


def reconstruct_path(previocus: dict[str, str | None], target: str) -> list[str]:
    path: list[str] = []
    current: str | None = target

    while current is not None:
        path.append(current)
        current = previous[current]

    path.reverse()
    return path


def main() -> None:
    graph = {
        "A": {"B": 4, "C": 1},
        "B": {"D": 1},
        "C": {"B": 2, "D": 5},
        "D": {"E": 3},
        "E": {},
    }

    distances, previous = dijkstra(graph, "A")

    print()
    print("Shortest path from A to E:")
    print(" -> ".join(reconstruct_path(previous, "E")))


if __name__ == "__main__":
    main()
