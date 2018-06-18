/*
DOCUMENT CODE "20180613-bnds0173.cpp"
CREATION DATE 2018-06-13
SIGNATURE CODE_20180613_BNDS0173
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180613_BNDS0173

#include <cstdlib>
#include <iostream>
using namespace std;

long long dp[1001][11000];
int n, c;

const int mod = 1000000007;

int main(int argc, char* argv[]) {

	cin >> n >> c;

	dp[0][0] = dp[1][0] = 1;

	for (int i = 2; i <= n; i++) {
		for (int k = 0; k <= c; k++) {
			/*for (int j = 0; j <= i - 1; j++) {
				if (k - j < 0)
					continue;
				dp[i][k] += dp[i - 1][k - j];
			}*/
			dp[i][k] = (dp[i - 1][k] + dp[i][k - 1]) % mod;
			if (k - i >= 0)
				dp[i][k] = (dp[i][k] - dp[i - 1][k - i] + mod) % mod;
		}
	}

	cout << dp[n][c] << endl;

	return 0;
}

#endif

