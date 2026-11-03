"""Small, fixed datasets for repeatable Lab 3 experiments."""

DATASETS = {
    "Small primes": [2, 3, 5, 7, 11, 13, 17, 19],
    "Large primes": [1009, 10007, 100003, 1000003],
    "Composite numbers": [4, 21, 91, 221, 341, 1001, 2047, 1000005],
    "Carmichael numbers": [561, 1105, 1729, 2465, 2821],
}

CATEGORIES = list(DATASETS.keys())
ALGORITHMS = ["Trial Division", "Fermat Primality Test", "Miller-Rabin Primality Test"]
