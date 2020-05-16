#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;

// trick to iterate through directions
constexpr int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };

int S[100001]; // skill levels
int neighbor[100001][4]; // array of neighbors for each competitor

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

	int T; cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << ": ";

		int R, C; cin >> R >> C;
		ll ans = 0, sum = 0;
		vector<int> check; // vector of candidate competitors to check
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				cin >> S[i * C + j]; sum += S[i * C + j];
				check.push_back(i * C + j);
			}
		}

		// checks if coordinates are out of range
		auto valid = [&R, &C](const int& x, const int& y) {
			return x >= 0 && x < R && y >= 0 && y < C;
		};
		
		// precompute neighbors
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				for (int d = 0; d < 4; ++d) {
					int x = i + dx[d], y = j + dy[d]; // get neighbor
					neighbor[i * C + j][d] = valid(x, y) ? x * C + y : -1;
				}
			}
		}

		while (1) { // simulate the competition
			vector<int> elim; // vector to store eliminated competitors
			for (auto& c : check) { // examine every candidate competitor
				int i = c / C, j = c % C, sum = 0, num = 0;
				if (S[c]) {
					for (int d = 0; d < 4; ++d) {
						if (neighbor[c][d] != -1) sum += S[neighbor[c][d]], ++num;
					}
					if (num * S[c] < sum) elim.push_back(c);
				}
			}

			check.clear(); // clear check for finding candidates for next round
			ans += sum;

			for (auto& c : elim) {
				int i = c / C, j = c % C;
				if (S[c]) { // remove each competitor
					sum -= S[c], S[c] = 0;
					for (int d = 0; d < 4; ++d) if (neighbor[c][d] != -1) {
						neighbor[neighbor[c][d]][(d + 2) % 4] = neighbor[c][(d + 2) % 4];
						check.push_back(neighbor[c][d]);
					}
				}
			}

			if (elim.empty()) break; // if no one eliminated we can end the competition
		}

		cout << ans << '\n';
	}
}