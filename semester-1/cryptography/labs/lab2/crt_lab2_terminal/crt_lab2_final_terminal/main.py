"""Terminal menu for Lab 2: Chinese Remainder Theorem."""
from crt import solve_crt, verify_solution
from rsa_demo import compare_decryption


def read_congruences():
    """Read lines in 'remainder modulus' format until a blank line."""
    print("\nEnter one congruence per line as: remainder modulus")
    print("Example: 2 3 means x ≡ 2 (mod 3).")
    print("Press Enter on a blank line when finished.\n")
    congruences = []

    while True:
        line = input(f"Congruence {len(congruences) + 1}: ").strip()
        if not line:
            break
        parts = line.replace(",", " ").split()
        if len(parts) != 2:
            print("Enter exactly two integers, for example: 2 3")
            continue
        try:
            remainder, modulus = map(int, parts)
        except ValueError:
            print("Both values must be integers.")
            continue
        if modulus <= 0:
            print("Modulus must be positive.")
            continue
        congruences.append((remainder, modulus))

    return congruences


def run_crt():
    print("\n--- CRT Solver ---")
    print("1. Enter your own congruences")
    print("2. Classic example")
    print("3. Generalized CRT (compatible, non-coprime moduli)")
    print("4. Generalized CRT (incompatible system)")
    choice = input("Choose example (1-4): ").strip()

    examples = {
        "2": [(2, 3), (3, 5), (2, 7)],
        "3": [(2, 6), (8, 10)],
        "4": [(1, 4), (2, 6)],
    }
    congruences = examples.get(choice) if choice in examples else read_congruences()

    if choice == "2":
        print("System: x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)")
    elif choice == "3":
        print("System: x ≡ 2 (mod 6), x ≡ 8 (mod 10)")
    elif choice == "4":
        print("System: x ≡ 1 (mod 4), x ≡ 2 (mod 6)")

    try:
        solution, modulus = solve_crt(congruences)
        print("\nRESULT")
        print(f"x ≡ {solution} (mod {modulus})")
        print(f"All solutions: x = {solution} + {modulus}k, for integer k.")
        print("\nVerification:")
        for remainder, mod in congruences:
            actual = solution % mod
            expected = remainder % mod
            print(
                f"x mod {mod} = {actual}; expected {expected}: "
                f"{'PASS' if actual == expected else 'FAIL'}"
            )
        print("Overall verification:", "PASS" if verify_solution(solution, congruences) else "FAIL")
    except ValueError as error:
        print("CRT error:", error)


def run_rsa():
    print("\n--- RSA Decryption: Direct vs CRT ---")
    print("Use small demo primes. Defaults: p=61, q=53, e=17, message=65.")
    try:
        use_defaults = input("Use defaults? (y/n): ").strip().lower()
        if use_defaults in ("", "y", "yes"):
            p, q, e, message = 61, 53, 17, 65
        else:
            p = int(input("Prime p: "))
            q = int(input("Prime q: "))
            e = int(input("Public exponent e: "))
            message = int(input("Message integer (0 <= message < p*q): "))

        result = compare_decryption(p, q, e, message)
        print(f"\nn = p*q = {result['n']}")
        print(f"phi(n) = {result['phi']}")
        print(f"Private exponent d = {result['d']}")
        print(f"Ciphertext = {result['ciphertext']}")
        print("\nDirect RSA:")
        print(f"Recovered message = {result['normal_message']}")
        print(f"Average time = {result['normal_seconds'] * 1e6:.3f} microseconds")
        print("\nCRT-based RSA:")
        print(f"dP = d mod (p-1) = {result['dp']}")
        print(f"dQ = d mod (q-1) = {result['dq']}")
        print(f"q inverse mod p = {result['q_inverse']}")
        print(f"m1 = c^dP mod p = {result['m1']}")
        print(f"m2 = c^dQ mod q = {result['m2']}")
        print(f"h = q_inverse * (m1-m2) mod p = {result['h']}")
        print(f"Recovered message = {result['crt_message']}")
        print(f"Average time = {result['crt_seconds'] * 1e6:.3f} microseconds")
        print(f"\nTiming repetitions per method: {result['repetitions']}")
        print(
            "Correctness:",
            "PASS" if result["normal_message"] == result["crt_message"] == message else "FAIL",
        )
        print("Note: tiny demo keys are for learning only, not real security.")
    except (ValueError, ZeroDivisionError) as error:
        print("RSA input error:", error)


def main():
    while True:
        print("\n" + "=" * 52)
        print("LAB 2 — CHINESE REMAINDER THEOREM")
        print("=" * 52)
        print("1. Solve CRT / generalized CRT")
        print("2. Compare normal RSA with CRT-based RSA")
        print("3. Exit")
        choice = input("Select: ").strip()

        if choice == "1":
            run_crt()
        elif choice == "2":
            run_rsa()
        elif choice == "3":
            print("Good luck with your lab viva!")
            break
        else:
            print("Please choose 1, 2, or 3.")


if __name__ == "__main__":
    main()
