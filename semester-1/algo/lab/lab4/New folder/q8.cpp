
#include <bits/stdc++.h>
using namespace std;
using Matrix = vector<vector<long long>>;

Matrix addM(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subM(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();

    if (n <= 32)
        return standardMultiply(A, B);

    int h = n / 2;
    Matrix A11(h, vector<long long>(h)), A12 = A11;
    Matrix A21 = A11, A22 = A11;
    Matrix B11 = A11, B12 = A11, B21 = A11, B22 = A11;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+h];
            A21[i][j] = A[i+h][j];
            A22[i][j] = A[i+h][j+h];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+h];
            B21[i][j] = B[i+h][j];
            B22[i][j] = B[i+h][j+h];
        }
    }

    Matrix M1 = strassen(addM(A11,A22), addM(B11,B22));
    Matrix M2 = strassen(addM(A21,A22), B11);
    Matrix M3 = strassen(A11, subM(B12,B22));
    Matrix M4 = strassen(A22, subM(B21,B11));
    Matrix M5 = strassen(addM(A11,A12), B22);
    Matrix M6 = strassen(subM(A21,A11), addM(B11,B12));
    Matrix M7 = strassen(subM(A12,A22), addM(B21,B22));

    Matrix C11 = addM(subM(addM(M1,M4),M5),M7);
    Matrix C12 = addM(M3,M5);
    Matrix C21 = addM(M2,M4);
    Matrix C22 = addM(addM(subM(M1,M2),M3),M6);

    Matrix C(n, vector<long long>(n));

    for (int i = 0; i < h; i++)
        for (int j = 0; j < h; j++) {
            C[i][j] = C11[i][j];
            C[i][j+h] = C12[i][j];
            C[i+h][j] = C21[i][j];
            C[i+h][j+h] = C22[i][j];
        }

    return C;
}

Matrix strassenPadded(const Matrix& A, const Matrix& B) {
    int n = A.size(), p = 1;
    while (p < n) p *= 2;

    Matrix X(p, vector<long long>(p, 0)), Y = X;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            X[i][j] = A[i][j];
            Y[i][j] = B[i][j];
        }

    Matrix Z = strassen(X, Y);
    Matrix C(n, vector<long long>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = Z[i][j];

    return C;
}

int main() {
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "Invalid matrix size\n";
        return 0;
    }

    // Fixed seed makes the test reproducible.
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, 9);

    Matrix A(n, vector<long long>(n));
    Matrix B(n, vector<long long>(n));

    for (auto& row : A)
        for (auto& x : row) x = dist(rng);

    for (auto& row : B)
        for (auto& x : row) x = dist(rng);

    auto start1 = chrono::steady_clock::now();
    Matrix C1 = standardMultiply(A, B);
    auto end1 = chrono::steady_clock::now();

    auto start2 = chrono::steady_clock::now();
    Matrix C2 = strassenPadded(A, B);
    auto end2 = chrono::steady_clock::now();

    double t1 = chrono::duration<double, milli>(end1-start1).count();
    double t2 = chrono::duration<double, milli>(end2-start2).count();

    cout << fixed << setprecision(3);
    cout << "Matrix size: " << n << " x " << n << '\n';
    cout << "Results match: " << (C1 == C2 ? "YES" : "NO") << '\n';
    cout << "Standard multiplication: " << t1 << " ms\n";
    cout << "Strassen multiplication: " << t2 << " ms\n";

    return 0;
}
