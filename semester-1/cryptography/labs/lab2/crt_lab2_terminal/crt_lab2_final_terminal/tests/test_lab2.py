import unittest

from crt import combine_two, solve_crt, verify_solution
from rsa_demo import compare_decryption


class TestCRTLab(unittest.TestCase):
    def test_classic_multiple_congruences(self):
        system = [(2, 3), (3, 5), (2, 7)]
        x, modulus = solve_crt(system, show_steps=False)
        self.assertEqual((x, modulus), (23, 105))
        self.assertTrue(verify_solution(x, system))

    def test_generalized_compatible(self):
        x, modulus = solve_crt([(2, 6), (8, 10)], show_steps=False)
        self.assertEqual(modulus, 30)
        self.assertEqual(x % 6, 2)
        self.assertEqual(x % 10, 8)

    def test_generalized_incompatible(self):
        with self.assertRaises(ValueError):
            combine_two(1, 4, 2, 6)

    def test_rsa_direct_equals_crt(self):
        result = compare_decryption(61, 53, 17, 65, repetitions=20)
        self.assertEqual(result["normal_message"], 65)
        self.assertEqual(result["crt_message"], 65)


if __name__ == "__main__":
    unittest.main()
