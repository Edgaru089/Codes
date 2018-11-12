/*
 DOCUMENT NAME "20181103-luogu1736.cpp"
 CREATION DATE 2018-11-03
 SIGNATURE CODE_20181103_LUOGU1736
 COMMENT P1736 ¥¥“‚≥‘”„∑®
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181103_LUOGU1736

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename IntType = int>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

const int MaxN = 3000, MaxM = 3000;

int n, m;
char flag[MaxN][MaxM];
short llen[MaxN][MaxM], rlen[MaxN][MaxM], tlen[MaxN][MaxM];
short dp[MaxN][MaxM];



int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(flag[i][j]);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i > 1 && !flag[i - 1][j])
				tlen[i][j] = tlen[i - 1][j] + 1;
			if (j > 1 && !flag[i][j - 1])
				llen[i][j] = llen[i][j - 1] + 1;
		}
		for (int j = m - 1; j >= 1; j--)
			if (!flag[i][j + 1])
				rlen[i][j] = rlen[i][j + 1] + 1;
	}

	short ans = 0;
	// LT-RB axis
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (flag[i][j])
				dp[i][j] = min({ dp[i - 1][j - 1], llen[i][j], tlen[i][j] }) + 1;
			ans = max(ans, dp[i][j]);
		}
	// RT-LB axis
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--) {
			if (flag[i][j])
				dp[i][j] = min({ dp[i - 1][j + 1], rlen[i][j], tlen[i][j] }) + 1;
			ans = max(ans, dp[i][j]);
		}

	printf("%d\n", ans);

	return 0;
}

#endif

