/*
 DOCUMENT NAME "20181102-luogu1220.cpp"
 CREATION DATE 2018-11-02
 SIGNATURE CODE_20181102_LUOGU1220
 COMMENT P1220 ¹ØÂ·µÆ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181102_LUOGU1220

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
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

const int MaxN = 100;

int n, c;
int power[MaxN], pos[MaxN];
int ppow[MaxN], total;
int dp[MaxN][MaxN][2];
#define LEFT 0
#define RIGHT 1

inline int intabs(const int& a) { return a > 0 ? a : -a; }

int dis(int from, int to) {
	return intabs(pos[from] - pos[to]);
}

int totalpower(int l, int r) {
	if (l > r)
		swap(l, r);
	return ppow[n] - (ppow[r] - ppow[l - 1]);
}

void updatemin(int& val, int op) {
	val = min(val, op);
}


int main(int argc, char* argv[]) {

	read(n); read(c);
	for (int i = 1; i <= n; i++) {
		read(pos[i]); read(power[i]);
		ppow[i] = ppow[i - 1] + power[i];
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dp[i][j][0] = dp[i][j][1] = 1e8;

	dp[c][c][0] = dp[c][c][1] = 0;

	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= n - i + 1; j++) {
			updatemin(dp[j][j + i - 1][0], dp[j + 1][j + i - 1][0] + dis(j, j + 1)*totalpower(j + 1, j + i - 1));
			updatemin(dp[j][j + i - 1][0], dp[j + 1][j + i - 1][1] + dis(j, j + i - 1)*totalpower(j + 1, j + i - 1));
			updatemin(dp[j][j + i - 1][1], dp[j][j + i - 2][1] + dis(j + i - 2, j + i - 1)*totalpower(j, j + i - 2));
			updatemin(dp[j][j + i - 1][1], dp[j][j + i - 2][0] + dis(j, j + i - 1)*totalpower(j, j + i - 2));
		}

	printf("%d\n", min(dp[1][n][0], dp[1][n][1]));


	return 0;
}

#endif

