
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mergeCount(vector<int>& a, vector<int>& temp, int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    ll inversions = 0;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            inversions += m - i + 1;
        }
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (int p = l; p <= r; p++) a[p] = temp[p];
    return inversions;
}

ll countInversions(vector<int>& a, vector<int>& temp, int l, int r) {
    if (l >= r) return 0;

    int m = l + (r - l) / 2;
    ll count = countInversions(a, temp, l, m);
    count += countInversions(a, temp, m + 1, r);
    count += mergeCount(a, temp, l, m, r);

    return count;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n), temp(n);
    for (int& x : a) cin >> x;

    cout << "Inversion Count: ";
    cout << countInversions(a, temp, 0, n - 1) << '\n';
    return 0;
}
