# Task 0 - Closest Points in the Cartesian Plane

This folder contains both required approaches for task `0`:

- `closest_points_bruteforce.py`
- `closest_points_divide_and_conquer.py`

## 1. Brute-force approach

The brute-force method compares each point with every point that comes after it.
If there are `n` points, the number of checked pairs is:

`n(n - 1) / 2`

So the complexity is:

- Time: `O(n^2)`
- Auxiliary space: `O(1)` (excluding the input data)

This method is easy to implement, but it becomes slow for large inputs because
the number of pair comparisons grows quadratically.

## 2. Divide-and-conquer approach

The optimized method works as follows:

1. sort the points by `x` and by `y`
2. split the set into a left half and a right half
3. solve the problem recursively in each half
4. keep the better of the two distances
5. examine only the points near the dividing line

## 3. Comparison

- Brute force is simpler, but slower: `O(n^2)`
- Divide and conquer is more sophisticated, but faster: `O(n log n)`

For small inputs, brute force is acceptable. For larger inputs, the
divide-and-conquer method is much more efficient.
