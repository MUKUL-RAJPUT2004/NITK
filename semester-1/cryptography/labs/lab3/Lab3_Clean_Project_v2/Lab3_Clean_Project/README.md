# Lab 3 — Primality Testing

## Implemented algorithms
1. Trial Division
2. Fermat Primality Test
3. Miller–Rabin Primality Test

## Experiment categories
- Small primes
- Large primes
- Composite numbers
- Carmichael numbers

For each algorithm, select a category and then choose predefined or custom inputs. Fermat and Miller–Rabin also ask for the number of rounds/bases.

## Clean and repeatable behaviour
- No random numbers or random bases are generated.
- Probabilistic tests use fixed bases in the order `2, 3, 5, 7, 11`.
- Terminal output contains only menus and experiment results; no debug prints.
- Custom input accepts comma-separated or space/newline-separated integers from 2 to 1,000,000,000.
- Execution time measures only the selected algorithm. Exact reference checking is performed separately and excluded from the measured time.

## False-positive definition
A false positive occurs when Fermat or Miller–Rabin reports `PROBABLY PRIME` for a number that the exact trial-division reference identifies as composite. Trial Division itself cannot produce a false positive in this program.

Example: `561 = 3 × 11 × 17`. Fermat with only base 2 accepts 561, so the output records a false positive. With two rounds, base 3 shares a factor with 561 and exposes that it is composite. Miller–Rabin rejects 561 with base 2.

## Run
Windows: `py main.py`

Linux/macOS: `python3 main.py`

## Run tests
Windows: `py -m unittest discover -s tests -v`

Linux/macOS: `python3 -m unittest discover -s tests -v`

## Iteration-count convention
- Trial Division: number of odd divisors actually checked.
- Fermat: number of bases actually tested.
- Miller–Rabin: number of bases actually tested.

This convention is stated explicitly because the internal arithmetic work per round differs between algorithms.


## Demonstrating false positives

Choose **Composite numbers** → **Predefined inputs** → select either probabilistic test → set **1 round**. The fixed first base is 2. The dataset includes:

- `341 = 11 × 31`: Fermat accepts it with base 2 (false positive).
- `561 = 3 × 11 × 17`: Fermat accepts it with base 2 (false positive; Carmichael number).
- `2047 = 23 × 89`: Fermat and Miller–Rabin both accept it with base 2 (false positive for both).

The program compares each result with exact trial-division classification. With more rounds, additional bases may expose these composites, so a false positive may disappear. That is expected: the experiment demonstrates how additional rounds reduce the chance of a false positive. Prime-only categories cannot produce false positives because a false positive requires a composite input.
