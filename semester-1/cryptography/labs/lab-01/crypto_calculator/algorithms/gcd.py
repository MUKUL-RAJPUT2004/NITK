import math, time

def gcd(a, b):
    a, b = abs(a), abs(b)
    steps = []
    start = time.perf_counter()
    while b != 0:
        q, r = divmod(a, b)
        steps.append((a, b, q, r))
        a, b = b, r
    return a, steps, time.perf_counter() - start

def extended_gcd(a, b):
    sa = 1 if a >= 0 else -1
    sb = 1 if b >= 0 else -1
    a, b = abs(a), abs(b)
    old_r, r = a, b
    old_x, x = 1, 0
    old_y, y = 0, 1
    steps = []
    start = time.perf_counter()

    while r != 0:
        q = old_r // r
        nr = old_r - q*r
        nx = old_x - q*x
        ny = old_y - q*y
        steps.append((old_r, r, q, nr, old_x, x, old_y, y, nx, ny))
        old_r, r = r, nr
        old_x, x = x, nx
        old_y, y = y, ny

    elapsed = time.perf_counter() - start
    X, Y = old_x*sa, old_y*sb
    return old_r, X, Y, steps, elapsed

def trusted_gcd(a, b):
    return math.gcd(a, b)
