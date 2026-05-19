# Task 1 - Polynomial Multiplication

This folder contains the two required approaches:

- `polynomial_multiplication_bruteforce.py`
- `polynomial_multiplication_fft.py`

## 1. Brute-force polynomial multiplication

If

- `A(x) = a0 + a1x + ... + anx^n`
- `B(x) = b0 + b1x + ... + bnx^n`

then each coefficient `ai` must be multiplied with each coefficient `bj`, and
their product contributes to the term of degree `i + j`.

This leads to the double loop:

- for each coefficient in the first polynomial
- for each coefficient in the second polynomial
- add the product to the proper position in the result

### Complexity

- Time: `O(n^2)`
- Space: `O(n)` for the result coefficients

## 2. Fast Fourier Transform (FFT) approach

The FFT method speeds up multiplication by changing the representation of the
polynomials:

1. pad the coefficient lists to a power of two
2. evaluate both polynomials at many roots of unity using FFT
3. multiply the evaluated values point by point
4. apply the inverse FFT to recover the coefficients

Because evaluation and interpolation are both done in `O(n log n)`, polynomial
multiplication becomes much faster than the brute-force method for large inputs.

### Complexity

- Time: `O(n log n)`
- Space: `O(n)`

## 3. Comparison with the closest-points problem

The two tasks are similar in spirit:

- in closest points, brute force checks all relevant pairs and costs `O(n^2)`
- in polynomial multiplication, brute force checks all coefficient pairs and
  also costs `O(n^2)`

The optimized methods are different, but the idea is similar: avoid unnecessary
quadratic work.

- closest points uses `divide and conquer` plus a geometric observation about
  the strip near the middle line, giving `O(n log n)`
- polynomial multiplication uses `FFT`, which transforms the problem into fast
  evaluation, pointwise multiplication, and interpolation, also giving
  `O(n log n)`

So both problems start with a simple quadratic solution and then use a more
clever strategy to reduce the time complexity to `O(n log n)`.
