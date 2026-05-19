# Task 2 - Fast Inverse Square Root and Newton Method

This folder contains the required implementations for task `2`:

- `fast_inverse_sqrt.py`
- `newton_polynomial_root.py`
- `newton_nth_root.py`

## 1. Quake III fast inverse square root

The Quake III algorithm computes an approximation of `1 / sqrt(x)` very quickly.
It relies on the way floating-point numbers are stored in memory.

A 32-bit floating-point number is divided into:

- `1` sign bit
- `8` exponent bits
- `23` mantissa bits

The algorithm reinterprets the bits of the float as an integer, applies the  
famous magic constant `0x5F3759DF.`

This works because the bit-level manipulation provides a surprisingly good
initial guess for the inverse square root.

## 2. Newton's method for a polynomial root in [a, b]

To find a root of a strictly increasing convex polynomial `P(x)` in an interval
`[a, b]`, Newton's method uses:

`x_(k+1) = x_k - P(x_k) / P'(x_k)`

Because the polynomial is strictly increasing and convex, the root is unique in
the interval. Starting from the right endpoint is a stable choice in this case.
If a Newton step exits the interval, the implementation falls back to the
midpoint of `[a, b]`.

## 3. Newton's method for the n-th root of x

To compute `x^(1/n)`, define:

`f(y) = y^n - x`

Then Newton's iteration becomes:

`yₙ = yₙ₋₁ − f(yₙ₋₁) / f'(yₙ₋₁)`

This converges quickly for `x > 1` and `n >= 1` when a reasonable initial guess
is used.

## Complexity

- Fast inverse square root: `O(1)` time and `O(1)` space
- Newton root of a polynomial: `O(k * d)` time, where `k` is the number of
iterations and `d` is the degree of the polynomial
- Newton n-th root: `O(k * n)` time if powers are evaluated directly

In practice, Newton's method converges very fast, usually in a small number of
iterations.
