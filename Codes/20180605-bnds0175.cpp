/*
DOCUMENT CODE "20180605-bnds0175.cpp"
CREATION DATE 2018-06-05
SIGNATURE CODE_20180605_BNDS0175
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180605_BNDS0175

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[500];
int dp[500][500];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
		a[i + 2 * n] = a[i];
	}

	for (int j = 2; j <= n; j++) {
		for (int i = n; i >= 1; i--) {
			for (int k = 1; k <= j - 1; k++) {
				int id2 = (i + k) % n;
				if (id2 == 0)
					id2 = n;
				if (k != 1 && dp[i][k] == 0) {
					cout << "WRONG1" << endl;
				}
				if (j - k != 1 && dp[id2][j - k] == 0) {
					cout << "WRONG2" << endl;
				}
				dp[i][j] = max(dp[i][j], dp[i][k] + dp[id2][j - k] + a[i] * a[i + k] * a[i + j]);
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[i][n]);
	cout << ans << endl;

	return 0;
}

#endif

