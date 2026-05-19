from __future__ import annotations


def nth_root_newton(
    x: float,
    n: int,
    tolerance: float = 1e-10,
    max_iterations: int = 100,
) -> float:
    if x <= 1:
        raise ValueError("x must be supraunitary, so x > 1.")
    if n <= 0:
        raise ValueError("n must be positive.")

    guess = x if x < 2 else x / n

    for _ in range(max_iterations):
        next_guess = ((n - 1) * guess + x / (guess ** (n - 1))) / n

        if abs(next_guess - guess) < tolerance:
            return next_guess

        guess = next_guess

    return guess


def main() -> None:
    x = 81.0
    n = 4
    root = nth_root_newton(x, n)

    print(f"x = {x}")
    print(f"n = {n}")
    print(f"Approximate {n}-th root: {root:.10f}")
    print(f"Check: root^{n} = {root ** n:.10f}")


if __name__ == "__main__":
    main()
