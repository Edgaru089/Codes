/*
 DOCUMENT NAME "20181111-luogu1879.cpp"
 CREATION DATE 2018-11-11
 SIGNATURE CODE_20181111_LUOGU1879
 COMMENT P1879 [USACO06NOV]ÓñÃ×ÌïCorn Fields / ×´Ñ¹dp
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181111_LUOGU1879

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
{printf(#arr ":");												\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#endif

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
const int MaxN = 13, MaxM = 13;
const ll Mod = 100000000;

int n, m;
int flag[MaxN];
ll dp[MaxN][1 << MaxN];


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		flag[i] = 0;
		for (int j = 1; j <= m; j++) {
			int x;
			read(x);
			flag[i] |= (x << (j - 1));
		}
	}

	PRINTARR("%d", flag, 1, n);

	dp[0][0] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= (1 << m) - 1; j++) {
			if ((j | flag[i]) == flag[i] && !(((j << 1)&((1 << m) - 1))&j) && !((j >> 1)&j)) {
				DEBUG("i=%d valid, processing dp\n", j);
				for (int k = 0; k <= (1 << m) - 1; k++) {
					if (dp[i - 1][k] && !(j&k)) {
						dp[i][j] += dp[i - 1][k];
						if (dp[i][j] > Mod)
							dp[i][j] -= Mod;
					}
				}
			}
		}
		DEBUG("i=%d\n", i);
		PRINTARR("%lld", dp[i], 0, (1 << m));
	}

	ll ans = 0;
	for (int i = 0; i <= (1 << m) - 1; i++) {
		ans += dp[n][i];
		if (ans > Mod)
			ans -= Mod;
	}

	printf("%lld\n", ans);

	return 0;
}

#endif

