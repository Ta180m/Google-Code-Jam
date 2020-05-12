#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int R, C;
        cin >> R >> C;
		cout << "Case #" << t + 1 << ": ";
        
		vector<vector<int>> S(R);
        set<pair<int, int>> check;
		vector<set<int>> rs(R), cs(C);
		ll ans = 0, sum = 0;
		for (int i = 0; i < R; ++i) {
            S[i].resize(C);
            for (int j = 0; j < C; ++j) {
				cin >> S[i][j];
				check.emplace(i, j);
				sum += S[i][j];
			}
        }

		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) rs[i].insert(j);
		}
		for (int j = 0; j < C; ++j) {
			for (int i = 0; i < R; ++i) cs[j].insert(i);
		}

		while (1) {
			vector<pair<int, int>> elim;
			for (auto& x : check) {
				int i = x.first, j = x.second;
				if (S[i][j]) {
					int cnt = 0, num = 0;
					auto r = cs[j].find(i);
					if (r != cs[j].end()) {
						if (r != cs[j].begin()) cnt += S[*(--r)][j], ++num, ++r;
						if (r != --cs[j].end()) cnt += S[*(++r)][j], ++num;
					}
					auto c = rs[i].find(j);
					if (c != rs[i].end()) {
						if (c != rs[i].begin()) cnt += S[i][*(--c)], ++num, ++c;
						if (c != --rs[i].end()) cnt += S[i][*(++c)], ++num;
					}
					if (num * S[i][j] < cnt) elim.emplace_back(i, j);
				}
			}
			check.clear();
			ans += sum;
			for (auto& x : elim) {
				int i = x.first, j = x.second, cnt = 0, num = 0;
				sum -= S[i][j];
				S[i][j] = 0;
				auto r = cs[j].find(i);
				if (r != cs[j].end()) {
					if (r != cs[j].begin()) check.emplace(*(--r), j), ++r;
					if (r != --cs[j].end()) check.emplace(*(++r), j);
				}
				auto c = rs[i].find(j);
				if (c != rs[i].end()) {
					if (c != rs[i].begin()) check.emplace(i, *(--c)), ++c;
					if (c != --rs[i].end()) check.emplace(i, *(++c));
				}
				rs[i].erase(j);
				cs[j].erase(i);
			}
			if (elim.empty()) break;
		}
        cout << ans << '\n';
    }
}