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
		vector<pair<int, int>> check; // set of candidate competitors to check
		ll ans = 0, sum = 0;
		for (int i = 0; i < R; ++i) {
			S[i].resize(C);
			for (int j = 0; j < C; ++j) {
				cin >> S[i][j];
				sum += S[i][j];
				check.emplace_back(i, j);
			}
		}
		
		vector<vector<vector<int>>> neighbor(R);
		for (int i = 0; i < R; ++i) {
			neighbor[i].resize(C);
			for (int j = 0; j < C; ++j) {
				neighbor[i][j].resize(4);
				neighbor[i][j][0] = i > 0 ? i - 1 : -1;
				neighbor[i][j][1] = i < R - 1 ? i + 1 : -1;
				neighbor[i][j][2] = j > 0 ? j - 1 : -1;
				neighbor[i][j][3] = j < C - 1 ? j + 1 : -1;
			}
		}

		while (1) {
			vector<pair<int, int>> elim; // vector to store eliminated competitors
			for (auto& x : check) { // examine every candidate competitor
				int i = x.first, j = x.second, sum = 0, num = 0;
				if (S[i][j]) {
					if (neighbor[i][j][0] != -1) sum += S[neighbor[i][j][0]][j], ++num;
					if (neighbor[i][j][1] != -1) sum += S[neighbor[i][j][1]][j], ++num;
					if (neighbor[i][j][2] != -1) sum += S[i][neighbor[i][j][2]], ++num;
					if (neighbor[i][j][3] != -1) sum += S[i][neighbor[i][j][3]], ++num;

					if (num * S[i][j] < sum) elim.emplace_back(i, j);
				}
			}

			check.clear(); // clear check for finding candidates for next round
			ans += sum;

			for (auto& x : elim) {
				int i = x.first, j = x.second;
				if (S[i][j]) {
					sum -= S[i][j];
					S[i][j] = 0;

					if (neighbor[i][j][0] != -1) {
						neighbor[neighbor[i][j][0]][j][1] = neighbor[i][j][1];
						check.emplace_back(neighbor[i][j][0], j);
					}
					if (neighbor[i][j][1] != -1) {
						neighbor[neighbor[i][j][1]][j][0] = neighbor[i][j][0];
						check.emplace_back(neighbor[i][j][1], j);
					}
					if (neighbor[i][j][2] != -1) {
						neighbor[i][neighbor[i][j][2]][3] = neighbor[i][j][3];
						check.emplace_back(i, neighbor[i][j][2]);
					}
					if (neighbor[i][j][3] != -1) {
						neighbor[i][neighbor[i][j][3]][2] = neighbor[i][j][2];
						check.emplace_back(i, neighbor[i][j][3]);
					}
				}
			}

			if (elim.empty()) break;
		}

		cout << ans << '\n';
	}
}