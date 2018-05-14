/*
DOCUMENT CODE "20180512-bnds0110.cpp"
CREATION DATE 2018-05-12
SIGNATURE CODE_20180512_BNDS0110
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180512_BNDS0110

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge {
	int u, v;
	int len;
};

Edge e[200];
int n, m;

int p[10000];

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

	sort(e + 1, e + m + 1, [](Edge x, Edge y) {return x.len < y.len; });

	int sum = 0;
	for (int i = 1; i <= m; i++) {
		if (Find(e[i].u) != Find(e[i].v)) {
			Union(e[i].u, e[i].v);
			sum += e[i].len;
		}
	}

	cout << sum << endl;

	return 0;
}

#endif

