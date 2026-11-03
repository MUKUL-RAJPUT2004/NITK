import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from primality import trial_division, fermat_test, miller_rabin_test
from datasets import DATASETS


class TestPrimalityAlgorithms(unittest.TestCase):
    def test_trial_division(self):
        self.assertEqual(trial_division(2)[0], True)
        self.assertEqual(trial_division(97)[0], True)
        self.assertEqual(trial_division(91)[0], False)

    def test_fermat_carmichael_base_two(self):
        self.assertEqual(fermat_test(561, 1), (True, 1))

    def test_fermat_rejects_composite_with_factor_base(self):
        self.assertEqual(fermat_test(561, 2)[0], False)

    def test_miller_rabin_rejects_carmichael(self):
        self.assertEqual(miller_rabin_test(561, 1)[0], False)

    def test_fermat_false_positive_examples(self):
        # 341 and 2047 are composite, but pass Fermat with base 2.
        self.assertTrue(fermat_test(341, 1)[0])
        self.assertTrue(fermat_test(2047, 1)[0])

    def test_miller_rabin_false_positive_example(self):
        # 2047 = 23 * 89 is a strong pseudoprime to base 2.
        self.assertTrue(miller_rabin_test(2047, 1)[0])

    def test_miller_rabin_primes(self):
        for n in DATASETS["Small primes"] + DATASETS["Large primes"]:
            self.assertTrue(miller_rabin_test(n, 5)[0], n)

    def test_invalid_rounds(self):
        with self.assertRaises(ValueError):
            fermat_test(17, 0)
        with self.assertRaises(ValueError):
            miller_rabin_test(17, 0)


if __name__ == "__main__":
    unittest.main()
