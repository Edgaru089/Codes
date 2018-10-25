/*
 DOCUMENT NAME "20181024-luogu1508.cpp"
 CREATION DATE 2018-10-24
 SIGNATURE CODE_20181024_LUOGU1508
 COMMENT P1508 Likecloud-³Ô¡¢³Ô¡¢³Ô
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181024_LUOGU1508

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxN = 200 + 10, MaxM = 200 + 10;

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

int n, m;
long long a[MaxN][MaxM];
long long dp[MaxN][MaxN];


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(a[i][j]);
	

	for (int i = 1; i <= n + 1; i++)
		for (int j = 0; j <= m + 1; j++)
			dp[i][j] = -1e16;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][j] = a[i][j] + max(max(dp[i - 1][j - 1], dp[i - 1][j]), dp[i - 1][j + 1]);

	printf("%lld\n", max(max(dp[n][m / 2], dp[n][m / 2 + 1]), dp[n][m / 2 + 2]));

	return 0;
}

#endif

