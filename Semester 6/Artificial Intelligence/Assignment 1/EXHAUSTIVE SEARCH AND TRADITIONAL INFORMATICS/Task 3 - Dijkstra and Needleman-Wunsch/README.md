# Task 3 - Dijkstra and Needleman-Wunsch

This folder contains the required implementations:

- `dijkstra.py`
- `needleman_wunsch.py`

## 1. Dijkstra's algorithm

Dijkstra's algorithm finds shortest paths from one source node to all other
nodes in a weighted graph with non-negative edge weights.

### Why it combines greedy and dynamic programming ideas

It is greedy because at each step it chooses the not-yet-finalized node with the
smallest temporary distance. This is the locally best choice.

It also uses a dynamic programming style because it stores the best distances
found so far and improves them using previously computed optimal subpaths. Once
the shortest distance to a node is finalized, that value is reused to relax
neighboring edges.

### Complexity

With a priority queue:

- Time: `O((V + E) log V)`
- Space: `O(V)`

where `V` is the number of vertices and `E` is the number of edges.

## 2. Needleman-Wunsch algorithm

Needleman-Wunsch computes a global alignment between two sequences.

It fills a dynamic programming table where each cell stores the best alignment
score for prefixes of the two sequences.

For each cell, the algorithm considers:

- diagonal move: match or mismatch
- upward move: gap in the second sequence
- left move: gap in the first sequence

Then it reconstructs an optimal alignment by tracing back from the last cell.

### Scoring penalties

The implementation in `needleman_wunsch.py` uses these default values:

| Parameter | Default | Meaning |
|-----------|---------|---------|
| `match_score` | `+1` | Aligned characters are equal |
| `mismatch_score` | `-1` | Aligned characters differ |
| `gap_penalty` | `-1` | A gap (`-`) in either sequence |

The alignment score is the sum of these values over all columns in the final alignment.

### Complexity

- Time: `O(mn)`
- Space: `O(mn)`

where `m` and `n` are the sequence lengths.
