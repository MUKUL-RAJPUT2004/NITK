
#include <bits/stdc++.h>
using namespace std;

vector<int> longestIncreasingSubsequence(const vector<int>& a) {
    int n = a.size();
    if (n == 0) return {};

    vector<int> dp(n, 1), parent(n, -1);
    int best = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }

        if (dp[i] > dp[best]) best = i;
    }

    vector<int> result;
    for (int i = best; i != -1; i = parent[i])
        result.push_back(a[i]);

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> lis = longestIncreasingSubsequence(a);

    cout << "LIS Length: " << lis.size() << '\n';
    cout << "LIS: ";
    for (int x : lis) cout << x << ' ';
    cout << '\n';

    return 0;
}
