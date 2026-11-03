
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Matrix = vector<vector<ll>>;

ll countLE(const Matrix& a, ll x) {
    int m = a.size(), n = a[0].size();
    int r = m - 1, c = 0;
    ll count = 0;

    while (r >= 0 && c < n) {
        if (a[r][c] <= x) {
            count += r + 1;
            c++;
        } else {
            r--;
        }
    }
    return count;
}

ll kthSmallest(const Matrix& a, ll k) {
    int m = a.size(), n = a[0].size();
    ll low = a[0][0], high = a[m - 1][n - 1];

    while (low < high) {
        ll mid = low + (high - low) / 2;

        if (countLE(a, mid) >= k)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}

int main() {
    int m, n;
    cin >> m >> n;

    if (m <= 0 || n <= 0) {
        cout << "Invalid dimensions\n";
        return 0;
    }

    Matrix a(m, vector<ll>(n));
    for (auto& row : a)
        for (ll& x : row)
            cin >> x;

    ll k;
    cin >> k;

    if (k < 1 || k > 1LL * m * n) {
        cout << "Invalid k\n";
        return 0;
    }

    cout << "K-th Smallest Element: " << kthSmallest(a, k) << '\n';
    return 0;
}
