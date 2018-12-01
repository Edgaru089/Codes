/*
 DOCUMENT NAME "20181116-luogu1282.cpp"
 CREATION DATE 2018-11-16
 SIGNATURE CODE_20181116_LUOGU1282
 COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181116_LUOGU1282

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;

template<typename IntType>
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

const int MaxN = 1000 + 10, MaxA = 8 * MaxN * 2;

int n;
int a[MaxN], b[MaxN];
int dp[MaxN][MaxA];


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		read(b[i]);
	}

	memset(dp, 0x3f3f3f3f, sizeof(dp));
	dp[0][MaxA / 2] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < MaxA; j++) {
			if (j + (a[i] - b[i]) > 0 && j + (a[i] - b[i]) < MaxA)
				dp[i][j + (a[i] - b[i])] = min(dp[i][j + (a[i] - b[i])], dp[i - 1][j]);
			if (j + (b[i] - a[i]) > 0 && j + (b[i] - a[i]) < MaxA)
				dp[i][j + (b[i] - a[i])] = min(dp[i][j + (b[i] - a[i])], dp[i - 1][j] + 1);
		}
	}

	int mindist = 1e8;
	int mindval = 1e8;
	for (int i = 0; i < MaxA; i++) {
		if (dp[n][i] < 1e8) {
			if (mindist > i + MaxA / 2) {
				mindist = i + MaxA / 2;
				mindval = dp[n][i];
			} else if (mindist == i + MaxA / 2)
				mindval = min(mindval, dp[n][i]);
		}
	}

	printf("%d\n", mindval);


	return 0;
}

#endif

