/*
DOCUMENT CODE "20180506-luogu2330.cpp"
CREATION DATE 2018-05-06
SIGNATURE CODE_20180506_LUOGU2330
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180506_LUOGU2330

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct edge {
	int u, v;
	int len;
};

int p[1001];
edge e[10001];
int n, m;

int Find(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	p[x] += p[y];
	p[y] = x;
}

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].len;
	}

	sort(e + 1, e + m + 1, [](edge& x, edge& y) {return x.len < y.len; });

	int Max = 0;
	for (int i = 1; i <= m; i++) {
		if (Find(e[i].u) != Find(e[i].v)) {
			Union(e[i].u, e[i].v);
			Max = max(Max, e[i].len);
		}
	}

	cout << n - 1 << " " << Max << endl;

	return 0;
}

#endif

