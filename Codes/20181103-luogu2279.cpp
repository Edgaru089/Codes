/*
 DOCUMENT NAME "20181103-luogu2279.cpp"
 CREATION DATE 2018-11-03
 SIGNATURE CODE_20181103_LUOGU2279
 COMMENT P2279 [HNOI2003]消防局的设立
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181103_LUOGU2279

#include <cstdlib>
#include <iostream>
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

int n, a[MaxN], p[MaxN], dep[MaxN], mindis[MaxN];

bool cmp(int x, int y) { return dep[x] > dep[y]; }


int main(int argc, char* argv[]) {

	read(n);

	p[1] = 1;
	mindis[1] = mindis[0] = 1e8;

	for (int i = 2; i <= n; i++) {
		read(a[i]);
		dep[i] = dep[a[i]] + 1;
		p[i] = i;
		mindis[i] = 1e8;
	}

	sort(p + 1, p + n + 1, cmp);

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int  u = a[a[p[i]]], v = p[i], w = a[v];
		mindis[v] = min({ mindis[v], mindis[w] + 1, mindis[u] + 2 });
		if (mindis[v] > 2) {
			ans++;
			mindis[u] = 0;
			mindis[a[u]] = min(mindis[a[u]], 1);
			mindis[a[a[u]]] = min(mindis[a[a[u]]], 2);
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

