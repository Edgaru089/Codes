/*
DOCUMENT CODE "20180106-luogu3366.cpp"
CREATION DATE 2018-01-06
SIGNATURE CODE_20180106_LUOGU3366
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180106_LUOGU3366

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct node {
	int v, len;
	node* next;
};

struct edge {
	int u, v, len;
};

int p[5001];
int n, m;
edge e[200000];

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

void addedge(int u, int v, int len) {

}

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> e[i].u >> e[i].v >> e[i].len;

	sort(e + 1, e + m + 1, [](edge x, edge y)->bool {return x.len < y.len; });

	int count = 0, size = 0;
	for (int i = 1; i <= m; i++) {
		edge x = e[i];
		if (Find(x.u) != Find(x.v)) {
			Union(x.u, x.v);
			size += x.len;
		}
	}

	int root = Find(1);
	bool flag = true;
	for (int i = 2; i <= n; i++) {
		if (Find(i) != root) {
			flag = false;
			break;
		}
	}
	if (flag)
		cout << size << endl;
	else
		cout << "orz" << endl;

	return 0;
}

#endif

