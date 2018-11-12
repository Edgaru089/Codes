/*
 DOCUMENT NAME "20181102-luogu1005.cpp"
 CREATION DATE 2018-11-02
 SIGNATURE CODE_20181102_LUOGU1005
 COMMENT P1005 æÿ’Û»° ˝”Œœ∑
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181102_LUOGU1005

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
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

typedef long long ll;
const int MaxN = 100, MaxM = 100;

int n, m;
int a[MaxN][MaxM];
ll dp[MaxM][MaxM];

#define PUTCHAR(c) putchar(c)

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[40], *buftop = buf + 39;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 39; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(a[i][j]);

	ll ans = 0;
	for (int k = 1; k <= n; k++) {
		int* d = a[k];
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m - i + 1; j++)
				dp[j][i] = max(dp[j + 1][i - 1] + d[j] * ((ll)(1) << (m - i + 1)), dp[j][i - 1] + d[j + i - 1] * ((ll)(1) << (m - i + 1)));
		ans += dp[1][m];
	}

	println(ans);

	return 0;
}

#endif

