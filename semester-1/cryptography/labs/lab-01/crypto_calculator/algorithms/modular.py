import time
from .gcd import extended_gcd

def modular_add(a, b, m):
    return (a+b) % m

def modular_multiply(a, b, m):
    return (a*b) % m

def modular_inverse(a, m):
    g, x, y, steps, elapsed = extended_gcd(a, m)
    return (x % m if g == 1 else None), g, x, y, steps, elapsed

def naive_mod_pow(a, e, m):
    result = 1 % m
    a %= m
    start = time.perf_counter()
    for _ in range(e):
        result = (result*a) % m
    return result, time.perf_counter()-start

def square_multiply(a, e, m):
    result = 1 % m
    a %= m
    steps = []
    start = time.perf_counter()
    while e > 0:
        bit = e & 1
        before = result
        if bit:
            result = (result*a) % m
        steps.append((e, bit, a, before, result))
        a = (a*a) % m
        e //= 2
    return result, time.perf_counter()-start, steps
