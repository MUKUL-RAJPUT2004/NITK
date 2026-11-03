
#include <bits/stdc++.h>
using namespace std;

vector<int> countSmallerRight(const vector<int>& a) {
    int n = a.size();
vector<int> answer(n, 0);
vector<pair<int, int>> temp(n);
vector<pair<int, int>> items(n);

    for (int i = 0; i < n; i++)
        items[i] = {a[i], i};

    function<void(int, int)> mergeSort = [&](int l, int r) {
        if (l >= r) return;

        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);

        int i = l, j = m + 1, p = l;
        int rightSmaller = 0;

        while (i <= m && j <= r) {
            if (items[j].first < items[i].first) {
                temp[p++] = items[j++];
                rightSmaller++;
            } else {
                answer[items[i].second] += rightSmaller;
                temp[p++] = items[i++];
            }
        }

        while (i <= m) {
            answer[items[i].second] += rightSmaller;
            temp[p++] = items[i++];
        }

        while (j <= r) temp[p++] = items[j++];

        for (int x = l; x <= r; x++)
            items[x] = temp[x];
    };

    if (n > 0) mergeSort(0, n - 1);
    return answer;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> result = countSmallerRight(a);

    cout << "Counts: ";
    for (int x : result) cout << x << ' ';
    cout << '\n';

    return 0;
}

