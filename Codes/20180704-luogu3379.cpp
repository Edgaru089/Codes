/*
DOCUMENT NAME "20180704-luogu3379.cpp"
CREATION DATE 2018-07-04
SIGNATURE CODE_20180704_LUOGU3379
COMMENT 【模板】最近公共祖先（LCA） / 树链剖分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180704_LUOGU3379

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

const int MaxN = 500000 + 10;

int read() {
	char c;
	int sum = 0;
	while (!isdigit(c = getchar()));
	do {
		sum = (sum << 1) + (sum << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return sum;
}

int read(int& x) {
	return x = read();
}

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *nodetop = mem;
#define ALLOCATE (++nodetop)

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


int ssize[MaxN], father[MaxN], dep[MaxN];
int heavyson[MaxN];
void dfs1(int u, int from = 0, int step = 1) {
	father[u] = from;
	ssize[u] = 1;
	dep[u] = step;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs1(v, u, step + 1);
			ssize[u] += ssize[v];
		}
	}
	int maxsize = 0, maxid = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			if (maxsize < ssize[v]) {
				maxsize = ssize[v];
				maxid = v;
			}
		}
	}
	heavyson[u] = maxid;
}


int stime;
int dfn[MaxN], top[MaxN];
void dfs2(int u, int t) {
	dfn[u] = ++stime;
	top[u] = t;
	if (heavyson[u] != 0)
		dfs2(heavyson[u], t);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavyson[u])
			dfs2(v, v);
	}
}


int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		u = father[top[u]];
	}
	if (dep[u] > dep[v])
		return v;
	else
		return u;
}


int n, m, s;
int a, b;


int main(int argc, char* argv[]) {

	read(n); read(m); read(s);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());

	dfs1(s);
	dfs2(s, s);

	for (int i = 1; i <= m; i++)
		printf("%d\n", lca(read(), read()));

	return 0;
}

#endif

