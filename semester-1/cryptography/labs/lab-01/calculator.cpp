#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <chrono>

using namespace std;
using namespace boost::multiprecision;


// ============================================================
// GENERATE A RANDOM 512-BIT INTEGER
// ============================================================

cpp_int generate512BitNumber()
{
    random_device rd;
    mt19937_64 gen(rd());

    cpp_int number = 0;

    // 512 bits = 8 × 64 bits
    for (int i = 0; i < 8; i++)
    {
        number <<= 64;
        number += gen();
    }

    // Make sure the highest bit is 1,
    // so the number is definitely 512 bits.
    number |= (cpp_int(1) << 511);

    return number;
}


// ============================================================
// GET INTEGER
//
// User can:
// 1. Enter a number manually
// 2. Generate a random 512-bit number
// ============================================================

cpp_int getNumber(string name)
{
    int choice;

    cout << "\nHow do you want to enter " << name << "?\n";
    cout << "1. Enter manually\n";
    cout << "2. Generate random 512-bit number\n";
    cout << "Choice: ";

    cin >> choice;

    if (choice == 2)
    {
        cpp_int number = generate512BitNumber();

        cout << "\nGenerated " << name << ":\n";
        cout << number << endl;

        cout << "\nBit length: "
             << boost::multiprecision::msb(number) + 1
             << endl;

        return number;
    }

    cpp_int number;

    cout << "Enter " << name << ": ";
    cin >> number;

    return number;
}


// ============================================================
// 1. EUCLIDEAN GCD
// ============================================================

cpp_int euclideanGCD(cpp_int a, cpp_int b)
{
    if (a < 0)
        a = -a;

    if (b < 0)
        b = -b;

    while (b != 0)
    {
        cpp_int r = a % b;

        a = b;
        b = r;
    }

    return a;
}


// ============================================================
// 2. EXTENDED EUCLIDEAN ALGORITHM
//
// Finds:
//
//      ax + by = gcd(a,b)
//
// Returns gcd(a,b)
// ============================================================

cpp_int extendedEuclidean(
    cpp_int a,
    cpp_int b,
    cpp_int &x,
    cpp_int &y)
{
    // Base case
    if (b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    cpp_int x1, y1;

    cpp_int g =
        extendedEuclidean(
            b,
            a % b,
            x1,
            y1
        );

    // Back substitution
    x = y1;

    y = x1 - (a / b) * y1;

    return g;
}


// ============================================================
// 3. MODULAR INVERSE
//
// Finds x such that:
//
//      ax ≡ 1 (mod m)
//
// Exists only when gcd(a,m) = 1.
// ============================================================

cpp_int modularInverse(cpp_int a, cpp_int m)
{
    cpp_int x, y;

    cpp_int g =
        extendedEuclidean(a, m, x, y);

    if (g != 1)
    {
        return -1;
    }

    x = x % m;

    if (x < 0)
        x += m;

    return x;
}


// ============================================================
// 4. MODULAR ADDITION
//
//      (a + b) mod m
// ============================================================

cpp_int modularAddition(
    cpp_int a,
    cpp_int b,
    cpp_int m)
{
    return (a + b) % m;
}


// ============================================================
// 5. MODULAR MULTIPLICATION
//
//      (a × b) mod m
// ============================================================

cpp_int modularMultiplication(
    cpp_int a,
    cpp_int b,
    cpp_int m)
{
    return (a * b) % m;
}


// ============================================================
// 6. NAIVE MODULAR EXPONENTIATION
//
//      a^e mod m
//
// Repeated multiplication.
//
// Complexity: O(e)
// ============================================================

cpp_int naiveExponentiation(
    cpp_int a,
    cpp_int e,
    cpp_int m)
{
    cpp_int result = 1;

    a = a % m;

    for (cpp_int i = 0; i < e; i++)
    {
        result = (result * a) % m;
    }

    return result;
}


// ============================================================
// 7. SQUARE-AND-MULTIPLY
//
// Also called repeated squaring.
//
// Complexity: O(log e)
// ============================================================

cpp_int squareAndMultiply(
    cpp_int a,
    cpp_int e,
    cpp_int m)
{
    cpp_int result = 1;

    a = a % m;

    while (e > 0)
    {
        // If exponent is odd
        if (e % 2 == 1)
        {
            result = (result * a) % m;
        }

        // Square the base
        a = (a * a) % m;

        // Divide exponent by 2
        e = e / 2;
    }

    return result;
}


// ============================================================
// TASK 1: GCD
// ============================================================

void performGCD()
{
    cout << "\n========== EUCLIDEAN GCD ==========\n";

    cpp_int a = getNumber("a");
    cpp_int b = getNumber("b");

    cpp_int result =
        euclideanGCD(a, b);

    cout << "\nGCD(a,b) = "
         << result
         << endl;
}


// ============================================================
// TASK 2 & 3: EXTENDED EUCLIDEAN
// ============================================================

void performExtendedEuclidean()
{
    cout << "\n===== EXTENDED EUCLIDEAN =====\n";

    cpp_int a = getNumber("a");
    cpp_int b = getNumber("b");

    cpp_int x, y;

    cpp_int g =
        extendedEuclidean(a, b, x, y);

    cout << "\nGCD = " << g << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << "\nBezout identity:\n";

    cout << a << " × (" << x << ") + "
         << b << " × (" << y << ") = "
         << a * x + b * y
         << endl;

    if (a * x + b * y == g)
        cout << "\nVerification: PASS\n";
    else
        cout << "\nVerification: FAIL\n";
}


// ============================================================
// TASK 4: MODULAR INVERSE
// ============================================================

void performModularInverse()
{
    cout << "\n========== MODULAR INVERSE ==========\n";

    cpp_int a = getNumber("a");
    cpp_int m = getNumber("modulus m");

    cpp_int inverse =
        modularInverse(a, m);

    if (inverse == -1)
    {
        cout << "\nModular inverse does not exist.\n";
        cout << "Because gcd(a,m) != 1.\n";
    }
    else
    {
        cout << "\nInverse = "
             << inverse
             << endl;

        cout << "\nVerification:\n";

        cout << "(" << a << " × "
             << inverse << ") mod "
             << m << " = "
             << (a * inverse) % m
             << endl;
    }
}


// ============================================================
// TASK 5: MODULAR ADDITION
// ============================================================

void performModularAddition()
{
    cout << "\n========== MODULAR ADDITION ==========\n";

    cpp_int a = getNumber("a");
    cpp_int b = getNumber("b");
    cpp_int m = getNumber("modulus m");

    cpp_int result =
        modularAddition(a, b, m);

    cout << "\n(a + b) mod m = "
         << result
         << endl;
}


// ============================================================
// TASK 5: MODULAR MULTIPLICATION
// ============================================================

void performModularMultiplication()
{
    cout << "\n======= MODULAR MULTIPLICATION =======\n";

    cpp_int a = getNumber("a");
    cpp_int b = getNumber("b");
    cpp_int m = getNumber("modulus m");

    cpp_int result =
        modularMultiplication(a, b, m);

    cout << "\n(a × b) mod m = "
         << result
         << endl;
}


// ============================================================
// TASK 6: MODULAR EXPONENTIATION
// ============================================================

void performModularExponentiation()
{
    cout << "\n======= MODULAR EXPONENTIATION =======\n";

    cpp_int a = getNumber("base a");

    cpp_int e;

    cout << "\nEnter exponent e: ";
    cin >> e;

    cpp_int m =
        getNumber("modulus m");

    cout << "\nChoose method:\n";
    cout << "1. Naive exponentiation\n";
    cout << "2. Square-and-multiply\n";

    int choice;

    cout << "Choice: ";
    cin >> choice;

    cpp_int result;

    auto start =
        chrono::high_resolution_clock::now();

    if (choice == 1)
    {
        result =
            naiveExponentiation(a, e, m);
    }
    else if (choice == 2)
    {
        result =
            squareAndMultiply(a, e, m);
    }
    else
    {
        cout << "Invalid choice.\n";
        return;
    }

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed =
        end - start;

    cout << "\nResult = "
         << result
         << endl;

    cout << "Execution time = "
         << elapsed.count()
         << " seconds\n";
}


// ============================================================
// TASK 7: PERFORMANCE EXPERIMENT
// ============================================================

void performanceExperiment()
{
    cout << "\n======= PERFORMANCE EXPERIMENT =======\n";

    cpp_int a = getNumber("base a");
    cpp_int m = getNumber("modulus m");

    // Increasing exponents
    int exponents[] =
    {
        10,
        100,
        1000,
        10000,
        100000,
        1000000
    };

    cout << "\n";
    cout << "------------------------------------------------------\n";

    cout << "Exponent\tNaive Time\tFast Time\n";

    cout << "------------------------------------------------------\n";

    for (int e : exponents)
    {
        // -----------------------------
        // Naive
        // -----------------------------

        auto start1 =
            chrono::high_resolution_clock::now();

        cpp_int result1 =
            naiveExponentiation(
                a,
                e,
                m
            );

        auto end1 =
            chrono::high_resolution_clock::now();

        chrono::duration<double> time1 =
            end1 - start1;


        // -----------------------------
        // Square-and-multiply
        // -----------------------------

        auto start2 =
            chrono::high_resolution_clock::now();

        cpp_int result2 =
            squareAndMultiply(
                a,
                e,
                m
            );

        auto end2 =
            chrono::high_resolution_clock::now();

        chrono::duration<double> time2 =
            end2 - start2;


        cout << e << "\t\t"
             << time1.count() << " s\t"
             << time2.count() << " s";


        if (result1 == result2)
            cout << "\tPASS";

        else
            cout << "\tFAIL";

        cout << endl;
    }

    cout << "------------------------------------------------------\n";
}


// ============================================================
// TASK 8: VERIFY IMPLEMENTATIONS
// ============================================================

void verifyImplementations()
{
    cout << "\n========== VERIFY IMPLEMENTATIONS ==========\n";

    // --------------------------------------------------------
    // GCD
    // --------------------------------------------------------

    cout << "\n--- GCD ---\n";

    cpp_int a = getNumber("a");
    cpp_int b = getNumber("b");

    cpp_int result =
        euclideanGCD(a, b);

    cout << "Our GCD = "
         << result
         << endl;

    /*
       For verification we check the defining property:

       gcd divides both a and b.
    */

    if (a % result == 0 &&
        b % result == 0)
    {
        cout << "GCD verification: PASS\n";
    }
    else
    {
        cout << "GCD verification: FAIL\n";
    }


    // --------------------------------------------------------
    // Extended Euclidean
    // --------------------------------------------------------

    cout << "\n--- Extended Euclidean ---\n";

    cpp_int x, y;

    cpp_int g =
        extendedEuclidean(a, b, x, y);

    cout << "gcd = " << g << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    if (a * x + b * y == g)
        cout << "Bezout verification: PASS\n";
    else
        cout << "Bezout verification: FAIL\n";


    // --------------------------------------------------------
    // Modular Exponentiation
    // --------------------------------------------------------

    cout << "\n--- Modular Exponentiation ---\n";

    a = getNumber("base");
    
    cpp_int e;

    cout << "Enter exponent: ";
    cin >> e;

    cpp_int m =
        getNumber("modulus");

    cpp_int ourResult =
        squareAndMultiply(a, e, m);

    /*
       Boost provides cpp_int arithmetic, but not a direct
       one-line modular exponentiation function equivalent
       to Python's pow(a,e,m).

       So we independently verify using naive exponentiation.
    */

    cpp_int trustedResult =
        naiveExponentiation(a, e, m);

    cout << "Square-and-multiply = "
         << ourResult
         << endl;

    cout << "Naive/reference     = "
         << trustedResult
         << endl;

    if (ourResult == trustedResult)
        cout << "Verification: PASS\n";
    else
        cout << "Verification: FAIL\n";


    // --------------------------------------------------------
    // Modular inverse
    // --------------------------------------------------------

    cout << "\n--- Modular Inverse ---\n";

    a = getNumber("a");
    m = getNumber("modulus");

    cpp_int inverse =
        modularInverse(a, m);

    if (inverse == -1)
    {
        cout << "Inverse does not exist.\n";
    }
    else
    {
        cout << "Inverse = "
             << inverse
             << endl;

        if ((a * inverse) % m == 1)
            cout << "Inverse verification: PASS\n";
        else
            cout << "Inverse verification: FAIL\n";
    }
}


// ============================================================
// MAIN
//
// Program performs ONE selected operation and terminates.
// ============================================================

int main()
{
    cout << "\n";
    cout << "=================================================\n";
    cout << "       CRYPTOGRAPHY CALCULATOR - LAB 1\n";
    cout << "=================================================\n";

    cout << "\nSelect an operation:\n";

    cout << "1. Euclidean GCD\n";
    cout << "2. Extended Euclidean Algorithm\n";
    cout << "3. Modular Inverse\n";
    cout << "4. Modular Addition\n";
    cout << "5. Modular Multiplication\n";
    cout << "6. Modular Exponentiation\n";
    cout << "7. Performance Experiment\n";
    cout << "8. Verify Implementations\n";

    cout << "\nEnter choice: ";

    int choice;
    cin >> choice;


    switch (choice)
    {
        case 1:
            performGCD();
            break;

        case 2:
            performExtendedEuclidean();
            break;

        case 3:
            performModularInverse();
            break;

        case 4:
            performModularAddition();
            break;

        case 5:
            performModularMultiplication();
            break;

        case 6:
            performModularExponentiation();
            break;

        case 7:
            performanceExperiment();
            break;

        case 8:
            verifyImplementations();
            break;

        default:
            cout << "\nInvalid choice.\n";
    }


    cout << "\nProgram finished.\n";

    return 0;
}