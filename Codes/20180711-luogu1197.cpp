/*
DOCUMENT NAME "20180711-luogu1197.cpp"
CREATION DATE 2018-07-11
SIGNATURE CODE_20180711_LUOGU1197
COMMENT [JSOI2008]–««Ú¥Û’Ω
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180711_LUOGU1197

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int MaxN = 400000 + 10, MaxM = MaxN / 2;

int p[MaxN];

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

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}


int n, m, k;
int u, v;
int a[MaxN];

bool flag[MaxN];
int blockcnt;
int ans[MaxN];

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		addedge(u, v);
	}
	cin >> k;
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
		flag[a[i]] = true;
	}

	blockcnt = n - k;
	for (int i = 0; i < n; i++) {
		if (!flag[i]) {
			for (node* p = h[i]; p != nullptr; p = p->next) {
				int u = i, v = p->v;
				if (!flag[v] && Find(u) != Find(v)) {
					Union(u, v);
					blockcnt--;
				}
			}
		}
	}

	ans[k + 1] = blockcnt;
	for (int i = k; i >= 1; i--) {
		int u = a[i];
		flag[u] = false;
		blockcnt++;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (!flag[v]) {
				if (Find(u) != Find(v)) {
					Union(u, v);
					blockcnt--;
				}
			}
		}
		ans[i] = blockcnt;
	}

	for (int i = 1; i <= k + 1; i++)
		cout << ans[i] << endl;

	return 0;
}

#endif

