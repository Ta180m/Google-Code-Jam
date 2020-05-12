#include <bits/stdc++.h>
using namespace std;

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        cout << "Case #" << t + 1 << ":\n";
        if (N <= 500) {
            for (int i = 0; i < N; ++i) cout << i + 1 << " " << 1 << '\n';
        }
        else {
            N -= 32;
            int sum = 0;
            bool side = 0;
            for (int i = 0; i < 32; ++i) {
                cout << i + 1 << " " << (side ? i + 1 : 1) << '\n';
                if (N & (1 << i)) {
                    if (side) {
                        for (int j = i; j > 0; --j) cout << i + 1 << " " << j << '\n';
                        side = 0;
                    }
                    else {
						for (int j = 2; j <= i + 1; ++j) cout << i + 1 << " " << j << '\n';
                        side = 1;
					}
					sum += (1 << i);                    
                }
				else ++sum;
            }
			int x = 32;
			N += 32;
			while (sum < N) {
				cout << x + 1 << ' ' << (side ? x + 1 : 1) << '\n';
				++x, ++sum;
			}
        }
    }
}