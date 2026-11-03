
#include <bits/stdc++.h>
using namespace std;

string longestCommonPrefix(const vector<string>& words) {
    if (words.empty()) return "";

    for (int i = 0; i < (int)words[0].size(); i++) {
        char c = words[0][i];

        for (int j = 1; j < (int)words.size(); j++) {
            if (i >= (int)words[j].size() || words[j][i] != c) {
                return words[0].substr(0, i);
            }
        }
    }

    return words[0];
}

int main() {
    int n;
    cin >> n;

    vector<string> words(n);
    for (string& word : words) cin >> word;

    cout << "Longest Common Prefix: "
         << longestCommonPrefix(words) << '\n';

    return 0;
}
