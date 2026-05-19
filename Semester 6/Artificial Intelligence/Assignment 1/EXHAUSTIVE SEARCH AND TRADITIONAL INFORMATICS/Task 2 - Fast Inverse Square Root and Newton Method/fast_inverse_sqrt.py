from __future__ import annotations

import math
import struct


def Q_rsqrt(number: float) -> float:
    """Quake III fast inverse square root: 1 / sqrt(number)."""
    if number <= 0:
        raise ValueError("The input must be positive.")

    x2 = number * 0.5
    y = number
    threehalfs = 1.5

    # evil floating point bit level hacking
    i = struct.unpack("I", struct.pack("f", y))[0]

    # what the fuck?
    i = 0x5F3759DF - (i >> 1)

    y = struct.unpack("f", struct.pack("I", i & 0xFFFFFFFF))[0]

    # 1st Newton iteration
    y = y * (threehalfs - (x2 * y * y))

    # y = y * ( threehalfs - ( x2 * y * y ) );  — 2nd iteration, can be removed

    return y


def fast_inverse_sqrt(number: float) -> float:
    return Q_rsqrt(number)


def main() -> None:
    number = 25.0
    approximation = Q_rsqrt(number)
    exact_value = 1 / math.sqrt(number)

    print(f"Number: {number}")
    print(f"Fast inverse square root: {approximation:.10f}")
    print(f"Exact inverse square root: {exact_value:.10f}")
    print(f"Absolute error: {abs(approximation - exact_value):.10f}")


if __name__ == "__main__":
    main()
