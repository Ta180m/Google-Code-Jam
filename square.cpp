#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cout << "Case #" << t + 1 << ": ";

		int R, C;
		cin >> R >> C;
		vector<vector<int>> S(R); // we have to use vector of vector because R or C could be 1e5
		set<pair<int, int>> check; // set of candidate competitors to check
		vector<set<int>> rs(R), cs(C); // sets to quickly determine a competitor's neighbors
		ll ans = 0, sum = 0;
		for (int i = 0; i < R; ++i) {
			S[i].resize(C);
			for (int j = 0; j < C; ++j) {
				cin >> S[i][j];
				sum += S[i][j];
				check.emplace(i, j);
			}
		}

		// prepare sets
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) rs[i].insert(j);
		}
		for (int j = 0; j < C; ++j) {
			for (int i = 0; i < R; ++i) cs[j].insert(i);
		}

		while (1) {
			vector<pair<int, int>> elim; // vector to store eliminated competitors
			for (auto& x : check) { // examine every candidate competitor
				int i = x.first, j = x.second, cnt = 0, num = 0;

				auto r = cs[j].find(i);
				if (r != cs[j].end()) { // get neighbors
					if (r != cs[j].begin()) cnt += S[*prev(r)][j], ++num;
					if (r != --cs[j].end()) cnt += S[*next(r)][j], ++num;
				}

				auto c = rs[i].find(j);
				if (c != rs[i].end()) { // get neighbors
					if (c != rs[i].begin()) cnt += S[i][*prev(c)], ++num;
					if (c != --rs[i].end()) cnt += S[i][*next(c)], ++num;
				}

				if (num * S[i][j] < cnt) elim.emplace_back(i, j);
			}

			check.clear(); // clear check for finding candidates for next round
			ans += sum;

			for (auto& x : elim) {
				int i = x.first, j = x.second, cnt = 0, num = 0;
				sum -= S[i][j];
				S[i][j] = 0;

				auto r = cs[j].find(i);
				if (r != cs[j].end()) { // get neighbors
					if (r != cs[j].begin()) check.emplace(*prev(r), j);
					if (r != --cs[j].end()) check.emplace(*next(r), j);
				}
				
				auto c = rs[i].find(j);
				if (c != rs[i].end()) { // get neighbors
					if (c != rs[i].begin()) check.emplace(i, *prev(c));
					if (c != --rs[i].end()) check.emplace(i, *next(c));
				}

				rs[i].erase(j), cs[j].erase(i); // remove competitor from sets
			}

			if (elim.empty()) break;
		}

		cout << ans << '\n';
	}
}