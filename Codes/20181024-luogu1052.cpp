/*
 DOCUMENT NAME "20181024-luogu1052.cpp"
 CREATION DATE 2018-10-24
 SIGNATURE CODE_20181024_LUOGU1052
 COMMENT P1052 ¹ýºÓ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181024_LUOGU1052

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int MaxL = 1e9 + 10;
const int MaxST = 10 + 5, MaxM = 100 + 10;
const int Mod = 2520;
const int MaxTL = MaxM * Mod;

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

int l, s, t, m;
int pos[MaxM], dis[MaxM];
bool flag[MaxTL];
int dp[MaxTL];



int main(int argc, char* argv[]) {

	read(l);
	read(s); read(t); read(m);
	for (int i = 1; i <= m; i++)
		read(pos[i]);
	sort(pos + 1, pos + m + 1);
	for (int i = 1; i <= m; i++)
		dis[i] = pos[i] - pos[i - 1];
	dis[m + 1] = l - pos[m];
	for (int i = 1; i <= m + 1; i++)
		dis[i] %= Mod;
	for (int i = 1; i <= m; i++)
		pos[i] = pos[i - 1] + dis[i];
	l = pos[m] + dis[m + 1];

	for (int i = 1; i <= m; i++)
		flag[pos[i]] = true;

	for (int i = l; i >= 0; i--) {
		dp[i] = 1e8;
		for (int j = s; j <= t; j++)
			dp[i] = min(dp[i], dp[i + j]);
		if (flag[i])
			dp[i]++;
	}

	printf("%d\n", dp[0]);

	return 0;
}

#endif

