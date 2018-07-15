/*
DOCUMENT NAME "20180712-bnds0313.cpp"
CREATION DATE 2018-07-12
SIGNATURE CODE_20180712_BNDS0313
COMMENT NOIP2011D1T2 Ñ¡Ôñ¿ÍÕ»
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180712_BNDS0313

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 200000 + 10, MaxColor = 50 + 10;

int n, k, p;
int color[MaxN], cost[MaxN];

int colorprefixsum[MaxN][MaxColor];
int lastcafepos = 0;
int ans = 0;

int main(int argc, char* argv[]) {

	cin >> n >> k >> p;
	for (int i = 1; i <= n; i++)
		cin >> color[i] >> cost[i];

	for (int i = 1; i <= n; i++) {
		color[i]++;
		for (int j = 1; j <= k; j++)
			colorprefixsum[i][j] = colorprefixsum[i - 1][j];
		colorprefixsum[i][color[i]]++;
	}

	for (int i = 1; i <= n; i++) {
		if (cost[i] <= p)
			lastcafepos = i;
		ans += colorprefixsum[lastcafepos][color[i]];
		if (lastcafepos == i)
			ans--;
	}

	cout << ans << endl;

	return 0;
}

#endif

