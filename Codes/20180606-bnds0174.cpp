/*
DOCUMENT CODE "20180606-bnds0174.cpp"
CREATION DATE 2018-06-06
SIGNATURE CODE_20180606_BNDS0174
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180606_BNDS0174

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int v[100], w[100], flag[100];
vector<int> belongs[100];

int dp[100][100000];

void check(int i, int bagOccupied, int weight, int value) {
	if (bagOccupied + weight <= m)
		dp[i][bagOccupied + weight] = max(dp[i][bagOccupied + weight], dp[i - 1][bagOccupied] + value);
}

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i] >> flag[i];
		v[i] *= w[i];
		if (flag[i] != 0)
			belongs[flag[i]].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		if (flag[i] != 0)
			continue;
		for (int j = 0; j <= m; j++) {
			check(i, j, w[i], v[i]);
			if (belongs[i].size() == 1)
				check(i, j, w[i] + w[belongs[i][0]], v[i] + v[belongs[i][0]]);
			else if (belongs[i].size() == 2) {
				check(i, j, w[i] + w[belongs[i][0]], v[i] + v[belongs[i][0]]);
				check(i, j, w[i] + w[belongs[i][1]], v[i] + v[belongs[i][1]]);
				check(i, j, w[i] + w[belongs[i][0]] + w[belongs[i][1]], v[i] + v[belongs[i][0]] + v[belongs[i][1]]);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, dp[n][i]);

	cout << ans << endl;

	return 0;
}

#endif

