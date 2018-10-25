/*
 DOCUMENT NAME "20181024-luogu1006.cpp"
 CREATION DATE 2018-10-24
 SIGNATURE CODE_20181024_LUOGU1006
 COMMENT P1006 ´«Ö½Ìõ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181024_LUOGU1006

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MaxN = 50 + 10, MaxM = 50 + 10;

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
int a[MaxN][MaxM];
int dp[MaxN][MaxM][MaxN][MaxM];



int main(int argc, char* argv[]) {
	
	read(n); read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(a[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][j][i][j] = -1e8;
	dp[1][1][1][1] = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= n; k++)
				for (int l = 1; l <= m; l++)
					if ((i != k && j != l) || (i == n && j == m && k == n && l == m))
						dp[i][j][k][l] = max(max(dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1]),
											 max(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1])) + a[i][j] + a[k][l];

	printf("%d\n", dp[n][m][n][m]);

	return 0;
}

#endif

