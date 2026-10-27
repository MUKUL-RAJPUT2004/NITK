"""Chinese Remainder Theorem functions for Lab 2."""


def extended_gcd(a, b):
    """Return (g, x, y) where a*x + b*y = g = gcd(a, b)."""
    if b == 0:
        return abs(a), 1 if a >= 0 else -1, 0

    g, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return g, x, y


def modular_inverse(a, modulus):
    """Return a^(-1) modulo modulus, if it exists."""
    g, x, _ = extended_gcd(a, modulus)
    if g != 1:
        raise ValueError(f"Inverse does not exist because gcd({a}, {modulus}) = {g}.")
    return x % modulus


def combine_two(a, m, b, n):
    """
    Combine x = a (mod m) and x = b (mod n).
    Supports generalized CRT, including non-coprime moduli.
    Return (smallest_nonnegative_solution, lcm_of_moduli).
    """
    if m <= 0 or n <= 0:
        raise ValueError("Moduli must be positive.")

    a %= m
    b %= n
    g, _, _ = extended_gcd(m, n)

    # Compatibility condition for generalized CRT.
    if (b - a) % g != 0:
        raise ValueError(
            f"No solution: gcd({m}, {n}) = {g} does not divide {b-a}."
        )

    m1 = m // g
    n1 = n // g
    rhs = (b - a) // g

    if n1 == 1:
        t = 0
    else:
        t = (rhs * modular_inverse(m1, n1)) % n1

    combined_modulus = m * n1  # lcm(m, n)
    solution = (a + m * t) % combined_modulus
    return solution, combined_modulus


def solve_crt(congruences, show_steps=True):
    """Solve any number of (remainder, modulus) congruences."""
    if not congruences:
        raise ValueError("Please enter at least one congruence.")

    solution, modulus = congruences[0]
    if modulus <= 0:
        raise ValueError("Moduli must be positive.")
    solution %= modulus

    if show_steps:
        print(f"Start: x ≡ {solution} (mod {modulus})")

    for remainder, next_modulus in congruences[1:]:
        old_solution, old_modulus = solution, modulus
        solution, modulus = combine_two(
            solution, modulus, remainder, next_modulus
        )
        if show_steps:
            print(
                f"Combine x ≡ {old_solution} (mod {old_modulus}) with "
                f"x ≡ {remainder % next_modulus} (mod {next_modulus})"
            )
            print(f"  => x ≡ {solution} (mod {modulus})")

    return solution, modulus


def verify_solution(solution, congruences):
    """Return True only if the solution satisfies every input congruence."""
    return all(solution % m == a % m for a, m in congruences)
