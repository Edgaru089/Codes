/*
DOCUMENT NAME "20180712-bnds0324.cpp"
CREATION DATE 2018-07-12
SIGNATURE CODE_20180712_BNDS0324
COMMENT ¹ØÑº×ï·¸
*/

/*
INPUT
4 6
1 4 2534
2 3 3512
1 2 28351
1 3 6618
2 4 1805
3 4 12884
OUTPUT
3512
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180712_BNDS0324

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 20000 + 10, MaxM = 100000 + 10;

struct event {
	short u, v;
	int w;
};

int n, m;
event e[MaxM];
int revid[MaxN];

int p[MaxN + 2];

int Find(short x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = Find(p[x]);
}

// Union x into y
void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x == y)
		return;
	p[y] += p[x];
	p[x] = y;
}


int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].w;
	}

	sort(e + 1, e + m + 1, [](event a, event b) {
		return a.w > b.w;
	});

	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int u = e[i].u, v = e[i].v;
		if (Find(u) == Find(v)) {
			ans = e[i].w;
			break;
		}
		if (revid[u] == 0)
			revid[u] = v;
		else
			Union(revid[u], v);
		if (revid[v] == 0)
			revid[v] = u;
		else
			Union(revid[v], u);
	}

	cout << ans << endl;

	return 0;
}

#endif

