# Lab 2 — Chinese Remainder Theorem (Terminal Assignment)

This is a complete, terminal-based implementation of the objectives shown in the lab handout. It intentionally uses a small number of files so the code remains easy to explain in a viva.

## Objectives covered

1. Solve two congruences and extend the solver to multiple congruences.
2. Solve manually constructed CRT examples.
3. Implement generalized CRT for moduli that may not be coprime.
4. Demonstrate RSA decryption using CRT.
5. Compare direct RSA decryption with CRT-based decryption using average execution time.
6. Verify that computed answers satisfy the original congruences and that both RSA routes recover the same message.

## Files

```text
crt_lab2_final_terminal/
├── main.py        # Terminal menu, input, output, experiment flow
├── crt.py         # Extended Euclid, inverse, CRT merge, verification
├── rsa_demo.py    # RSA example, direct/CRT decryption, timing
├── tests/
│   └── test_lab2.py
└── README.md
```

The split is intentionally simple: mathematical CRT logic is separate from the terminal menu, and RSA comparison is separate because it is a distinct experiment.

## Run on Windows

Open PowerShell in this folder and run:

```powershell
python main.py
```

No third-party packages are required.

## Run automated tests

```powershell
python -m unittest discover -s tests -v
```

## CRT input format

Each congruence is entered as `remainder modulus`, one per line. For example:

```text
2 3
3 5
2 7
```

means x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7). The answer is x ≡ 23 (mod 105).

## Generalized CRT

For x ≡ a (mod m) and x ≡ b (mod n), let g = gcd(m,n). A solution exists if and only if g divides b-a. If compatible, the merged solution is unique modulo lcm(m,n).

## RSA experiment

The default demonstration uses p=61, q=53, e=17, and message=65. The program encrypts the message, decrypts it directly, then decrypts with CRT and compares average timings over repeated runs. Small values are used only to keep the example understandable; they are not secure RSA keys.

## Viva outline

- `extended_gcd`: computes gcd and Bezout coefficients recursively.
- `modular_inverse`: obtains the inverse from Extended Euclid.
- `combine_two`: merges two congruences using the generalized CRT condition.
- `solve_crt`: merges congruences one by one, so any number can be handled.
- `verify_solution`: checks the answer against each original equation.
- `compare_decryption`: performs direct RSA decryption and CRT-based decryption and times both.

## Notes on timing

Timing depends on the computer and Python runtime. Repeated measurements and average time are used to reduce timer noise, but the exact speed difference on tiny demo keys is not meaningful for production RSA.
