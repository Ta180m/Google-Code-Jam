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
		if (N <= 30) {
			// if N <= 30 then just use naïve method
			for (int i = 0; i < N; ++i) cout << i + 1 << " " << 1 << '\n';
		}
		else {
			// first we try to make N - 30
			int sum = 0, side = 0, goal = N - 30;
			for (int i = 0; i < 30; ++i) {
				cout << i + 1 << " " << (side ? i + 1 : 1) << '\n';

				// each row sums to 2 ^ i
				// check if goal has a 2 ^ i in its binary representation
				if (goal & (1 << i)) {
					// walk across the row
					for (int j = 1; j <= i; ++j) cout << i + 1 << " " << (side ? i - j + 1 : j + 1) << '\n';
					side = !side; // toggle the side
					sum += (1 << i);
				}
				else ++sum;
			}

			// we've undershot so we still need to walk down until our sum is N
			for (int i = 30; sum < N; ++i, ++sum) cout << i + 1 << ' ' << (side ? i + 1 : 1) << '\n';
		}
	}
}