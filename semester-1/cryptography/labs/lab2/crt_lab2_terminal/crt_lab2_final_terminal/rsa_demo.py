"""Small educational RSA decryption comparison using the CRT.""" 
import math
import time

from crt import modular_inverse


def is_prime(number):
    """Trial-division check; intended only for small lab demonstration values."""
    if number < 2:
        return False
    if number % 2 == 0:
        return number == 2
    divisor = 3
    while divisor * divisor <= number:
        if number % divisor == 0:
            return False
        divisor += 2
    return True


def compare_decryption(p, q, e, message, repetitions=5000):
    """Encrypt one message, then compare direct and CRT-based decryption."""
    if not is_prime(p) or not is_prime(q) or p == q:
        raise ValueError("p and q must be distinct prime numbers.")

    n = p * q
    phi = (p - 1) * (q - 1)
    if not (1 < e < phi) or math.gcd(e, phi) != 1:
        raise ValueError("e must satisfy 1 < e < phi(n) and gcd(e, phi(n)) = 1.")
    if not (0 <= message < n):
        raise ValueError(f"Message must be between 0 and {n - 1}.")

    d = modular_inverse(e, phi)
    ciphertext = pow(message, e, n)

    # Normal RSA: m = c^d mod n
    start = time.perf_counter()
    for _ in range(repetitions):
        normal_message = pow(ciphertext, d, n)
    normal_time = (time.perf_counter() - start) / repetitions

    # CRT-based RSA: calculate modulo p and q, then recombine.
    dp = d % (p - 1)
    dq = d % (q - 1)
    q_inverse = modular_inverse(q, p)

    start = time.perf_counter()
    for _ in range(repetitions):
        m1 = pow(ciphertext, dp, p)
        m2 = pow(ciphertext, dq, q)
        h = (q_inverse * (m1 - m2)) % p
        crt_message = (m2 + h * q) % n
    crt_time = (time.perf_counter() - start) / repetitions

    return {
        "n": n,
        "phi": phi,
        "d": d,
        "ciphertext": ciphertext,
        "normal_message": normal_message,
        "crt_message": crt_message,
        "normal_seconds": normal_time,
        "crt_seconds": crt_time,
        "repetitions": repetitions,
        "dp": dp,
        "dq": dq,
        "m1": m1,
        "m2": m2,
        "q_inverse": q_inverse,
        "h": h,
    }
