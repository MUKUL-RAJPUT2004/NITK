
#include <bits/stdc++.h>
using namespace std;

optional<int> majorityDC(const vector<int>& a, int l, int r) {
    if (l == r) return a[l];

    int mid = l + (r - l) / 2;
    auto left = majorityDC(a, l, mid);
    auto right = majorityDC(a, mid + 1, r);

    if (left && right && *left == *right)
        return left;

    int len = r - l + 1;

    if (left) {
        int count = 0;
        for (int i = l; i <= r; i++)
            if (a[i] == *left) count++;

        if (count > len / 2) return left;
    }

    if (right) {
        int count = 0;
        for (int i = l; i <= r; i++)
            if (a[i] == *right) count++;

        if (count > len / 2) return right;
    }

    return nullopt;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    if (n == 0) {
        cout << "No majority element\n";
        return 0;
    }

    auto result = majorityDC(a, 0, n - 1);

    if (result)
        cout << "Majority Element: " << *result << '\n';
    else
        cout << "No majority element\n";

    return 0;
}
