#include <bits/stdc++.h>
using namespace std;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cout << "Case #" << t + 1 << ":\n";
		
		int N;
		cin >> N;
		if (N <= 31) {
			// if N <= 31 then just use naïve method
			for (int i = 0; i < N; ++i) cout << i + 1 << " " << 1 << '\n';
		}
		else {
			// first we try to make N - 31
			int sum = 0, side = 0, goal = N - 31;
			for (int i = 0; i < 31; ++i) {
				cout << i + 1 << " " << (side ? i + 1 : 1) << '\n';

				// each row sums to 2 ^ (i + 1)
				// check if goal has a 2 ^ (i + 1) in its binary representation
				if (goal & (1 << i)) {
					// walk across the row
					for (int j = 1; j <= i; ++j) cout << i + 1 << " " << (side ? i - j + 1 : j + 1) << '\n';
					side = !side; // toggle the side
					sum += (1 << i);
				}
				else ++sum;
			}

			for (int i = 31; sum < N; ++i, ++sum) cout << i + 1 << ' ' << (side ? i + 1 : 1) << '\n';
		}
	}
}