/*
DOCUMENT NAME "20180629-luogu1828.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1828
COMMENT ÏãÌðµÄ»ÆÓÍ Sweet Butter / Floyd
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1828

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 800 + 10, MaxM = 1450 + 10;
const int MaxC = 500 + 10;

template<typename IntType>
IntType read() {
	char c;
	IntType val = 0;
	bool minus = false;

	while (!isdigit(c = getchar()))
		if (c == '-')
			minus = true;

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	if (minus)
		return -val;
	else
		return val;
}

template<typename IntType>
IntType read(IntType& val) {
	return val = read<IntType>();
}


int c, n, m;
int f; long long cnt[MaxN];
int u, v;
long long len;

long long dis[MaxN][MaxN];


int main(int argc, char* argv[]) {

	read(c); read(n); read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == j)
				dis[i][j] = 0;
			else
				dis[i][j] = infinity;
	for (int i = 1; i <= c; i++) {
		read(f);
		cnt[f]++;
	}
	for (int i = 1; i <= m; i++) {
		read(u); read(v); read(len);
		dis[u][v] = min(dis[u][v], len);
		dis[v][u] = min(dis[v][u], len);
	}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < i; j++)
				if (dis[i][j] > dis[i][k] + dis[k][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					dis[j][i] = dis[i][j];
				}

	long long ans = infinity;
	for (int i = 1; i <= n; i++) {
		long long sum = 0;
		for (int j = 1; j <= n; j++) {
			sum += dis[i][j] * cnt[j];
		}
		ans = min(ans, sum);
	}

	printf("%lld\n", ans);

	return 0;
}

#endif

