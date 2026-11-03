
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    if (n == 0) {
        cout << "No majority element\n";
        return 0;
    }

    int candidate = 0, balance = 0;

    for (int x : a) {
        if (balance == 0) {
            candidate = x;
            balance = 1;
        } else if (x == candidate) {
            balance++;
        } else {
            balance--;
        }
    }

    int count = 0;
    for (int x : a)
        if (x == candidate) count++;

    if (count > n / 2)
        cout << "Majority Element: " << candidate << '\n';
    else
        cout << "No majority element\n";

    return 0;
}
