/*
DOCUMENT NAME "20180708-luogu3379.cpp"
CREATION DATE 2018-07-08
SIGNATURE CODE_20180708_LUOGU3379
COMMENT 【模板】最近公共祖先（LCA） / 树链剖分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180708_LUOGU3379

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 500000 + 10;

int read() {
	int ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 1) + (ans << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}

int read(int& x) {
	return x = read();
}

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[MaxN * 2], *memtop = mem;
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

int root;
int dep[MaxN];
int ssize[MaxN], father[MaxN], heavy[MaxN];
void _dfs1(int u) {
	ssize[u] = 1;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u]) {
			father[v] = u;
			dep[v] = dep[u] + 1;
			_dfs1(v);
			ssize[u] += ssize[v];
		}
	}
	int maxsize = 0, maxid = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u]) {
			if (maxsize < ssize[v]) {
				maxsize = ssize[v];
				maxid = v;
			}
		}
	}
	heavy[u] = maxid;
}
void dfs1() {
	dep[root] = 1;
	_dfs1(root);
}

int stime;
int dfn[MaxN], top[MaxN];
void dfs2(int u = root, int t = root) {
	dfn[u] = ++stime;
	top[u] = t;
	if (heavy[u] != 0)
		dfs2(heavy[u], t);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavy[u])
			dfs2(v, v);
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = father[top[x]];
	}
	if (dep[x] < dep[y])
		return x;
	else
		return y;
}

int n, m;
int u, v;

int main(int argc, char* argv[]) {

	read(n); read(m); read(root);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());
	dfs1();
	dfs2();
	for (int i = 1; i <= m; i++)
		printf("%d\n", lca(read(), read()));

	return 0;
}

#endif

