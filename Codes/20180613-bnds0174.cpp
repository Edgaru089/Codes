/*
DOCUMENT CODE "20180613-bnds0174.cpp"
CREATION DATE 2018-06-13
SIGNATURE CODE_20180613_BNDS0174
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180613_BNDS0174

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int w[100], v[100], flag[100];
int dp[100000];
vector<int> appx[100];

void check(int j, int w, int v) {
	dp[j + w] = max(dp[j + w], dp[j] + v);
}

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i] >> flag[i];
		v[i] *= w[i];
		if (flag[i] != 0)
			appx[flag[i]].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		if (flag[i] != 0)
			continue;
		for (int j = m; j >= 0; j--) {
			check(j, w[i], v[i]);
			if (appx[i].size() >= 1)
				check(j, w[i] + w[appx[i][0]], v[i] + v[appx[i][0]]);
			if (appx[i].size() >= 2) {
				check(j, w[i] + w[appx[i][1]], v[i] + v[appx[i][1]]);
				check(j, w[i] + w[appx[i][0]] + w[appx[i][1]], v[i] + v[appx[i][0]] + v[appx[i][1]]);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= m; i++) {
		ans = max(ans, dp[i]);
	}

	cout << ans << endl;

	return 0;
}

#endif

