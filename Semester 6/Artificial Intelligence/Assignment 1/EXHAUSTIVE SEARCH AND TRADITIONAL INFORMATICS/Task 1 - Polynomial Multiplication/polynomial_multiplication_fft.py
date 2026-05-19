from __future__ import annotations

import cmath


def fft(values: list[complex], invert: bool = False) -> list[complex]:
    n = len(values)
    if n == 1:
        return values[:]

    even_part = fft(values[0::2], invert)
    odd_part = fft(values[1::2], invert)

    angle = 2 * cmath.pi / n * (-1 if not invert else 1)
    root = cmath.exp(1j * angle)
    current = 1 + 0j

    result = [0j] * n
    for i in range(n // 2):
        contribution = current * odd_part[i]
        result[i] = even_part[i] + contribution
        result[i + n // 2] = even_part[i] - contribution
        current *= root

    if invert:
        return [value / 2 for value in result]
    return result


def _next_power_of_two(value: int) -> int:
    power = 1
    while power < value:
        power *= 2
    return power


def multiply_polynomials_fft(poly1: list[float], poly2: list[float]) -> list[int]:
    result_size = len(poly1) + len(poly2) - 1
    fft_size = _next_power_of_two(result_size)

    padded1 = [complex(coefficient, 0) for coefficient in poly1] + [0j] * (fft_size - len(poly1))
    padded2 = [complex(coefficient, 0) for coefficient in poly2] + [0j] * (fft_size - len(poly2))

    transformed1 = fft(padded1)
    transformed2 = fft(padded2)

    transformed_product = [
        transformed1[index] * transformed2[index] for index in range(fft_size)
    ]
    inverted = fft(transformed_product, invert=True)

    return [round(inverted[index].real) for index in range(result_size)]


def format_polynomial(coefficients: list[float]) -> str:
    terms: list[str] = []

    for power, coefficient in enumerate(coefficients):
        if coefficient == 0:
            continue
        if power == 0:
            terms.append(f"{coefficient:g}")
        elif power == 1:
            terms.append(f"{coefficient:g}x")
        else:
            terms.append(f"{coefficient:g}x^{power}")

    return " + ".join(terms) if terms else "0"


def main() -> None:
    poly1 = [3, 2, 5]
    poly2 = [5, 1, 2]

    result = multiply_polynomials_fft(poly1, poly2)

    print("Polynomial A:", format_polynomial(poly1))
    print("Polynomial B:", format_polynomial(poly2))
    print("Product:", format_polynomial(result))
    print("Coefficients:", result)
    print()
    print("Complexity:")
    print("- Time: O(n log n), because FFT replaces coefficient-by-coefficient multiplication.")
    print("- Space: O(n), for padded arrays and recursive FFT calls.")


if __name__ == "__main__":
    main()
