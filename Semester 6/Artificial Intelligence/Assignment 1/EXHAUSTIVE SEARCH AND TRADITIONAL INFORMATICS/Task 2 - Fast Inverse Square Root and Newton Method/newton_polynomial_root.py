from __future__ import annotations


def evaluate_polynomial(coefficients: list[float], x: float) -> float:
    result = 0.0
    for coefficient in reversed(coefficients):
        result = result * x + coefficient
    return result


def derivative_coefficients(coefficients: list[float]) -> list[float]:
    return [power * coefficients[power] for power in range(1, len(coefficients))]


def newton_polynomial_root(
    coefficients: list[float],
    a: float,
    b: float,
    tolerance: float = 1e-10,
    max_iterations: int = 100,
) -> float:
    if a >= b:
        raise ValueError("The interval must satisfy a < b.")

    polynomial_at_a = evaluate_polynomial(coefficients, a)
    polynomial_at_b = evaluate_polynomial(coefficients, b)
    if polynomial_at_a > 0 or polynomial_at_b < 0:
        raise ValueError("The interval [a, b] must contain the root.")

    derivative = derivative_coefficients(coefficients)
    x = b

    for _ in range(max_iterations):
        value = evaluate_polynomial(coefficients, x)
        if abs(value) < tolerance:
            return x

        derivative_value = evaluate_polynomial(derivative, x)
        if derivative_value == 0:
            raise ValueError("Derivative became zero during Newton iteration.")

        next_x = x - value / derivative_value

        if not (a <= next_x <= b):
            next_x = (a + b) / 2

        if abs(next_x - x) < tolerance:
            return next_x

        x = next_x

    return x


def main() -> None:
    # P(x) = x^3 + x - 1
    coefficients = [-1, 1, 0, 1]
    root = newton_polynomial_root(coefficients, 0.0, 1.0)

    print("Polynomial: x^3 + x - 1")
    print(f"Approximate root in [0, 1]: {root:.10f}")
    print(f"P(root) = {evaluate_polynomial(coefficients, root):.10f}")


if __name__ == "__main__":
    main()
