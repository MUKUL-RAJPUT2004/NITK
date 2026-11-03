"""Clean terminal interface for Lab 3 primality experiments."""
from time import perf_counter
import re

from datasets import DATASETS, CATEGORIES, ALGORITHMS
from primality import (
    trial_division,
    fermat_test,
    miller_rabin_test,
    exact_reference,
)

MAX_INPUT = 1_000_000_000


def print_header(title):
    print("\n" + "=" * 58)
    print(title.center(58))
    print("=" * 58)


def read_choice(prompt, low, high):
    while True:
        raw = input(prompt).strip()
        try:
            value = int(raw)
        except ValueError:
            print(f"Enter a number from {low} to {high}.")
            continue
        if low <= value <= high:
            return value
        print(f"Enter a number from {low} to {high}.")


def choose_algorithm():
    print_header("LAB 3: PRIMALITY TESTING")
    print("Select algorithm:")
    for i, name in enumerate(ALGORITHMS, 1):
        print(f"  {i}. {name}")
    return ALGORITHMS[read_choice("Choice: ", 1, len(ALGORITHMS)) - 1]


def choose_category():
    print_header("EXPERIMENT CATEGORY")
    for i, name in enumerate(CATEGORIES, 1):
        print(f"  {i}. {name}")
    return CATEGORIES[read_choice("Choice: ", 1, len(CATEGORIES)) - 1]


def choose_inputs(category):
    print_header(category.upper())
    print("  1. Predefined inputs")
    print("  2. Custom inputs")
    choice = read_choice("Choice: ", 1, 2)
    if choice == 1:
        return DATASETS[category][:]

    while True:
        raw = input("Enter integers separated by commas or spaces: ").strip()
        parts = [part for part in re.split(r"[,\s]+", raw) if part]
        if not parts:
            print("No inputs entered. Try again.")
            continue
        try:
            values = [int(part) for part in parts]
        except ValueError:
            print("Invalid input. Enter integers only, separated by commas or spaces.")
            continue
        if any(n < 2 or n > MAX_INPUT for n in values):
            print(f"Each number must be between 2 and {MAX_INPUT:,}.")
            continue
        return values


def choose_rounds(algorithm):
    if algorithm == "Trial Division":
        return None
    print("\nFixed bases are used in this order: 2, 3, 5, 7, 11, ...")
    print("This makes every run repeatable; no random bases are generated.")
    print("Tip: choose 1 round to demonstrate known false positives (341/561 for Fermat; 2047 for both Fermat and Miller-Rabin).")
    return read_choice("Number of rounds/bases (1-5): ", 1, 5)


def run_one(algorithm, n, rounds):
    start = perf_counter()
    if algorithm == "Trial Division":
        result, iterations = trial_division(n)
    elif algorithm == "Fermat Primality Test":
        result, iterations = fermat_test(n, rounds)
    else:
        result, iterations = miller_rabin_test(n, rounds)
    elapsed = (perf_counter() - start) * 1000

    actual_prime = exact_reference(n)
    false_positive = bool(result and not actual_prime and algorithm != "Trial Division")
    if algorithm == "Trial Division":
        status = "PRIME" if result else "COMPOSITE"
    else:
        status = "PROBABLY PRIME" if result else "COMPOSITE"

    return status, elapsed, iterations, false_positive, actual_prime


def show_results(algorithm, numbers, rounds):
    print_header("EXPERIMENT RESULTS")
    print(f"Algorithm: {algorithm}")
    if rounds is not None:
        print(f"Rounds: {rounds} (fixed deterministic bases: 2, 3, 5, 7, 11)")
    print("\n{:<12} {:<18} {:>12} {:>12} {:>14}".format(
        "Number", "Result", "Time (ms)", "Iterations", "False Positive"
    ))
    print("-" * 72)

    false_positive_count = 0
    for n in numbers:
        status, elapsed, iterations, false_positive, actual_prime = run_one(
            algorithm, n, rounds
        )
        false_positive_count += int(false_positive)
        print("{:<12} {:<18} {:>12.4f} {:>12} {:>14}".format(
            n, status, elapsed, iterations, "YES" if false_positive else "NO"
        ))

    print("-" * 72)
    print(f"False positives in this experiment: {false_positive_count}")
    print("Reference classification: exact trial division.")
    if algorithm != "Trial Division" and rounds == 1:
        print("False-positive examples: Fermat accepts 341 and 561; Miller-Rabin accepts 2047 (base 2).")
    elif algorithm != "Trial Division" and rounds > 1:
        print("More rounds test additional bases and may eliminate false positives; this is expected.")
    print("Note: time is measured for the selected algorithm only; reference checking is excluded.")


def main():
    while True:
        algorithm = choose_algorithm()
        category = choose_category()
        numbers = choose_inputs(category)
        rounds = choose_rounds(algorithm)
        show_results(algorithm, numbers, rounds)

        print("\n  1. Run another experiment")
        print("  2. Exit")
        if read_choice("Choice: ", 1, 2) == 2:
            print("\nExperiment completed.")
            break


if __name__ == "__main__":
    main()
