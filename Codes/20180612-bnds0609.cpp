/*
DOCUMENT CODE "20180612-bnds0609.cpp"
CREATION DATE 2018-06-12
SIGNATURE CODE_20180612_BNDS0609
TOPIC test 2018-06-12
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180612_BNDS0609

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct datas {
	int t, f, h;
};

int d, g;
datas a[101];

// 表示当前时间为 i ，高度为 j 的状况能否达到
// 初始：dp[0 ~ 10][0] = 1, 其他 = 0
bool dp[3005][2505];

int main(int argc, char* argv[]) {
	cin >> d >> g;
	for (int i = 1; i <= g; i++) {
		cin >> a[i].t >> a[i].f >> a[i].h;
	}

	sort(a + 1, a + g + 1, [](const datas& x, const datas& y) {
		return x.t < y.t;
	});

	for (int i = 0; i <= 10; i++)
		dp[i][0] = true;

	for (int l = 1; l <= g; l++) {
		int T = a[l].t, F = a[l].f, H = a[l].h;
		for (int i = 3000 - F; i >= T; i--) {
			for (int j = d; j >= 0; j--) {
				if (dp[i][j]) {
					dp[i][j + H] = true;  // 垫在脚底下
					// 吃掉
					for (int k = i; k <= i + F; k++)
						dp[k][j] = true;
				}
			}
		}
	}

	int maxTime = 10, minTime = INT_MAX;

	for (int i = 0; i < 3000; i++) {
		for (int j = 0; j < 2500; j++) {
			if (dp[i][j]) {
				maxTime = max(maxTime, i);
				if (j >= d)
					minTime = min(minTime, i);
			}
		}
	}

	//cout << (minTime == INT_MAX ? "Failed" : "Success") << endl;

	if (minTime != INT_MAX)
		cout << minTime << endl;
	else
		cout << maxTime << endl;

	return 0;
}

#endif

