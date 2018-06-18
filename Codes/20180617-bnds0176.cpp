/*
DOCUMENT CODE "20180617-bnds0176.cpp"
CREATION DATE 2018-06-17
SIGNATURE CODE_20180617_BNDS0176
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180617_BNDS0176

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, num[500], dp[50][50][50][50];
int cnt[5];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> num[i];
	for (int i = 1; i <= m; i++) {
		int t;
		cin >> t;
		cnt[t]++;
	}

	dp[0][0][0][0] = num[1];

	for (int a = 0; a <= cnt[1]; a++)
		for (int b = 0; b <= cnt[2]; b++)
			for (int c = 0; c <= cnt[3]; c++)
				for (int d = 0; d <= cnt[4]; d++) {
					int r = a + b * 2 + c * 3 + d * 4 + 1;
					if (a != 0)
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a - 1][b][c][d] + num[r]);
					if (b != 0)
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b - 1][c][d] + num[r]);
					if (c != 0)
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c - 1][d] + num[r]);
					if (d != 0)
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d - 1] + num[r]);
				}

	cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]] << endl;

	return 0;
}

#endif

