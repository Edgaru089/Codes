/*
DOCUMENT NAME "20180715-bnds0723-test.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0723_TEST
COMMENT 2018-7-15基础班测验（附加题）-机房人民大团结
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0723_TEST

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const long long infinity = 1e14;
const int MaxN = 100 + 10, MaxM = 100 + 10;

int n, m;
long long a[MaxN], prefix[MaxN];

// [a, b]
long long segmentSum(int a, int b) {
	return prefix[b] - prefix[a - 1];
}

long long dp[MaxN][MaxN][MaxN];


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= n; i++)
		prefix[i] = prefix[i - 1] + a[i];

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= n; k++)
				dp[i][j][k] = infinity;
	dp[0][0][0] = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= i - 1; k++) {
				dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + segmentSum(k + 1, i));
				if (j > 0)
					dp[i][j][i] = min(dp[i][j][i], dp[i - 1][j - 1][k] + segmentSum(k + 1, i));
			}
		}

	long long ans = infinity;
	for (int j = 0; j <= m; j++)
		for (int k = 0; k <= n; k++)
			if (dp[n][j][k] != 0)
				ans = min(ans, dp[n][j][k]);

	cout << ans << endl;

	return 0;
}

#endif

