/*
 DOCUMENT NAME "20181017-luogu1941.cpp"
 CREATION DATE 2018-10-17
 SIGNATURE CODE_20181017_LUOGU1941
 COMMENT P1941 ·ÉÑïµÄÐ¡Äñ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181017_LUOGU1941

#include <cstdlib>
#include <iostream>
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

const int infinity = 1e8;
const int MaxN = 10000 + 10, MaxM = 1000 + 10;

int n, m, k;
int p, l, h;
int x[MaxN], y[MaxN];
bool flag[MaxN][MaxM];
int f[MaxN][MaxM];


int main(int argc, char* argv[]) {

	read(n); read(m); read(k);
	for (int i = 1; i <= n; i++) {
		read(x[i]); read(y[i]);
	}

	for (int i = 1; i <= k; i++) {
		read(p); read(l); read(h);
		for (int j = 0; j <= l; j++)
			flag[p][j] = true;
		for (int j = h; j <= m; j++)
			flag[p][j] = true;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = infinity;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			if (flag[i - 1][j])
				f[i][j] = f[i - 1][j];


	}


	return 0;
}

#endif

