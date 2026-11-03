
#include <bits/stdc++.h>
using namespace std;

int selectK(vector<int>& a, int k);

int medianOfMedians(vector<int>& a) {
    if (a.size() <= 5) {
        sort(a.begin(), a.end());
        return a[a.size() / 2];
    }

    vector<int> medians;

    for (int i = 0; i < (int)a.size(); i += 5) {
        vector<int> group(
            a.begin() + i,
            a.begin() + min(i + 5, (int)a.size())
        );

        sort(group.begin(), group.end());
        medians.push_back(group[group.size() / 2]);
    }

    return selectK(medians, medians.size() / 2 + 1);
}

// k is a one-based rank.
int selectK(vector<int>& a, int k) {
    if (a.size() <= 5) {
        sort(a.begin(), a.end());
        return a[k - 1];
    }

    int pivot = medianOfMedians(a);
    int lt = 0, i = 0, gt = (int)a.size() - 1;

    // Three-way partition handles duplicate values.
    while (i <= gt) {
        if (a[i] < pivot) swap(a[lt++], a[i++]);
        else if (a[i] > pivot) swap(a[i], a[gt--]);
        else i++;
    }

    int smaller = lt;
    int equal = gt - lt + 1;

    if (k <= smaller) {
        vector<int> left(a.begin(), a.begin() + lt);
        return selectK(left, k);
    }

    if (k <= smaller + equal) return pivot;

    vector<int> right(a.begin() + gt + 1, a.end());
    return selectK(right, k - smaller - equal);
}

int main() {
    int n, k;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;
    cin >> k;

    if (k < 1 || k > n) {
        cout << "Invalid k\n";
        return 0;
    }

    cout << "K-th Smallest Element: " << selectK(a, k) << '\n';
    return 0;
}
