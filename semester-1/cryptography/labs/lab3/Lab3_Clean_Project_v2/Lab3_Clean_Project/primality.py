"""Primality algorithms used in Lab 3. No random values are generated."""
from math import gcd, isqrt


def trial_division(n: int):
    """Return (is_prime, iteration_count)."""
    if n < 2:
        return False, 0
    if n == 2:
        return True, 0
    if n % 2 == 0:
        return False, 1

    iterations = 0
    limit = isqrt(n)
    divisor = 3
    while divisor <= limit:
        iterations += 1
        if n % divisor == 0:
            return False, iterations
        divisor += 2
    return True, iterations


def _valid_bases(n: int, rounds: int):
    """Deterministic, repeatable bases: 2, 3, 5, 7, ... below n - 1."""
    if rounds < 1:
        raise ValueError("Number of rounds must be at least 1.")
    candidates = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47)
    bases = [a for a in candidates if 2 <= a <= n - 2][:rounds]
    if not bases:
        # Small n is handled before this helper is called.
        raise ValueError("No valid test base for this number.")
    return bases


def fermat_test(n: int, rounds: int = 1):
    """Return (probably_prime, bases_tested). Uses fixed bases, not randomness."""
    if rounds < 1:
        raise ValueError("Number of rounds must be at least 1.")
    if n < 2:
        return False, 0
    if n in (2, 3):
        return True, 0
    if n % 2 == 0:
        return False, 0

    bases = _valid_bases(n, rounds)
    tested = 0
    for a in bases:
        tested += 1
        if gcd(a, n) != 1:
            return False, tested
        if pow(a, n - 1, n) != 1:
            return False, tested
    return True, tested


def miller_rabin_test(n: int, rounds: int = 1):
    """Return (probably_prime, bases_tested). Uses fixed bases, not randomness."""
    if rounds < 1:
        raise ValueError("Number of rounds must be at least 1.")
    if n < 2:
        return False, 0
    if n in (2, 3):
        return True, 0
    if n % 2 == 0:
        return False, 0

    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1

    bases = _valid_bases(n, rounds)
    tested = 0
    for a in bases:
        tested += 1
        if gcd(a, n) != 1:
            return False, tested

        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue

        witness_found = True
        for _ in range(s - 1):
            x = (x * x) % n
            if x == n - 1:
                witness_found = False
                break
        if witness_found:
            return False, tested

    return True, tested


def exact_reference(n: int):
    """Exact classification for this lab's bounded input range."""
    return trial_division(n)[0]
