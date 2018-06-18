/*
DOCUMENT CODE "20180616-bnds0177.cpp"
CREATION DATE 2018-06-16
SIGNATURE CODE_20180616_BNDS0177
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180616_BNDS0177

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int m, n;
int a[150][150];
int dp[300][150][150];

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];

	memset(dp, -1, sizeof(dp));
	dp[2][1][1] = 0;

	for (int k = 3; k < m + n; k++)
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++) {
				int s = dp[k][i][j];
				if (dp[k - 1][i][j] > s)
					s = dp[k - 1][i][j];
				if (dp[k - 1][i - 1][j] > s)
					s = dp[k - 1][i - 1][j];
				if (dp[k - 1][i][j - 1] > s)
					s = dp[k - 1][i][j - 1];
				if (dp[k - 1][i - 1][j - 1] > s)
					s = dp[k - 1][i - 1][j - 1];
				if (s != -1)
					dp[k][i][j] = s + a[k - i][i] + a[k - j][j];
			}

	cout << dp[m + n - 1][n - 1][n] << endl;

	return 0;
}

#endif

