/*
 DOCUMENT NAME "20181116-luogu1216.cpp"
 CREATION DATE 2018-11-16
 SIGNATURE CODE_20181116_LUOGU1216
 COMMENT P1216 [USACO1.5]Êý×ÖÈý½ÇÐÎ Number Triangles
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181116_LUOGU1216

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
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

const int MaxN = 1000 + 10;

int n;
int a[MaxN][MaxN];
int d[MaxN][MaxN];



int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			read(a[i][j]);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			d[i][j] = max(d[i - 1][j], d[i - 1][j - 1]) + a[i][j];
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, d[n][i]);

	printf("%d\n", ans);

	return 0;
}

#endif

