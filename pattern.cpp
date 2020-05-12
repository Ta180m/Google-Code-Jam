#include <bits/stdc++.h>
using namespace std;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        string P[55];
        for (int i = 0; i < N; ++i) cin >> P[i];
        
        string a, b, c;
        bool found = 1;
        for (int i = 0; i < N && found; ++i) {
            vector<string> v;
			v.push_back("");
            for (auto& c : P[i]) {
                if (c == '*') v.push_back("");
                else v.back() += c;
            }
            for (int j = 0; j < v.front().size() && found; ++j) {
                if (j >= a.size()) a.push_back(v.front()[j]);
                else if (v.front()[j] != a[j]) found = 0;
            }
            reverse(v.back().begin(), v.back().end());
            for (int j = 0; j < v.back().size() && found; ++j) {
                if (j >= c.size()) c.push_back(v.back()[j]);
                else if (v.back()[j] != c[j]) found = 0;
            }
            for (int j = 1; j < v.size() - 1; ++j) b += v[j];
        }
        reverse(c.begin(), c.end());
		
        cout << "Case #" << t + 1 << ": ";
        if (found) cout << a << b << c << '\n';
        else cout << "*\n";
    }
}