from __future__ import annotations


def multiply_polynomials_bruteforce(poly1: list[float], poly2: list[float]) -> list[float]:
    result = [0.0] * (len(poly1) + len(poly2) - 1)

    for i, coefficient1 in enumerate(poly1):
        for j, coefficient2 in enumerate(poly2):
            result[i + j] += coefficient1 * coefficient2

    return result


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

    result = multiply_polynomials_bruteforce(poly1, poly2)

    print("Polynomial A:", format_polynomial(poly1))
    print("Polynomial B:", format_polynomial(poly2))
    print("Product:", format_polynomial(result))
    print("Coefficients:", result)
    print()
    print("Complexity:")
    print("- Time: O(n^2), because every coefficient is multiplied with every other coefficient.")
    print("- Space: O(n), for the result array.")


if __name__ == "__main__":
    main()
