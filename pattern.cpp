#include <bits/stdc++.h>
using namespace std;

int main() {
    if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        
        int N;
        cin >> N;
        string P[55];
        for (int i = 0; i < N; ++i) cin >> P[i];
        
        string l, m, r; // left, middle, end parts of final answer
        bool ans = 1; // flag so we can quickly break when no solution exists
        for (int i = 0; i < N && ans; ++i) {
            // tokenize string
            vector<string> parts;
			parts.push_back("");
            for (auto& c : P[i]) {
                if (c == '*') parts.push_back(""); // add new string
                else parts.back() += c; // add c to current string
            }
            
            string& s = parts.front(); // leftmost part
            for (int j = 0; j < s.size() && ans; ++j) {
                if (j >= l.size()) l.push_back(s[j]); // extend l
                else if (s[j] != l[j]) ans = 0; // s doesn't match with current l
            }
            
            s = parts.back(); // rightmost part
            reverse(s.begin(), s.end());
            for (int j = 0; j < s.size() && ans; ++j) {
                if (j >= r.size()) r.push_back(s[j]); // extend r
                else if (s[j] != r[j]) ans = 0; // s doesn't match with current r
            }
            
            // add other parts to the middle string
            for (int j = 1; j < parts.size() - 1 && ans; ++j) m += parts[j];
        }
		
        reverse(r.begin(), r.end());
        
		// Creates at most 2 * 99 + 50 * 98 = 5098 < 1e4 characters
        cout << (ans ? l + m + r : "*") << '\n';
    }
}