/*
DOCUMENT CODE "20180617-luogu1855.cpp"
CREATION DATE 2018-06-17
SIGNATURE CODE_20180617_LUOGU1855
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180617_LUOGU1855

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, t;
int cm[1000], ct[1000];
int dp[1000][1000];

int main(int argc, char* argv[]) {

	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++)
		cin >> cm[i] >> ct[i];

	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= cm[i]; j--)
			for (int k = t; k >= ct[i]; k--) {
				dp[j][k] = max(dp[j][k], dp[j - cm[i]][k - ct[i]] + 1);
			}
	}

	cout << dp[m][t] << endl;

	return 0;
}

#endif

