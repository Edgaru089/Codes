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
int dp[110][110];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
		a[i + 2 * n] = a[i];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 2; j <= n; j++) {
			for (int k = 1; k <= j - 1; k++) {
				dp[i][j] = max(dp[i][j], dp[i][k] + dp[i + k][j - k] + a[i] * a[i + k] * a[i + j + 1]);
			}
		}
	}

	cout << dp[1][n] << endl;

	return 0;
}

#endif

