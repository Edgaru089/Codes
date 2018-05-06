/*
DOCUMENT CODE "20180430-luogu1111.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1111
TOPIC kruskal
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1111

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge {
	int u, v, len;
};

int p[100001];
int n, m;
int x, y, z;
Edge e[100001];

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

	sort(e + 1, e + m + 1, [](Edge& x, Edge& y) {return x.len <= y.len; });

	int Max = 0;
	for (int i = 1; i <= m; i++) {
		if (Find(e[i].u) != Find(e[i].v)) {
			Union(e[i].u, e[i].v);
			Max = max(Max, e[i].len);
		}
	}

	if (p[Find(1)] != -n)
		cout << -1 << endl;
	else
		cout << Max << endl;

	return 0;
}

#endif

