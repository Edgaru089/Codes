/*
 DOCUMENT NAME "20181106-luogu3379-.cpp"
 CREATION DATE 2018-11-06
 SIGNATURE CODE_20181106_LUOGU3379_
 COMMENT P3379 【模板】最近公共祖先 / 倍增 再写一遍
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181106_LUOGU3379_

#include <cstdlib>
#include <iostream>
using namespace std;

template<typename IntType = int>
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
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

const int MaxN = 500000 + 10, MaxLogN = 20;

int n, m, r;
int u, v;
struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
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

int fa[MaxN], dep[MaxN];
void dfs1(int u, int from, int step) {
	fa[u] = from;
	dep[u] = step;
	for (node* p = h[u]; p; p = p->next) {
		if (p->v != from)
			dfs1(p->v, u, step + 1);
	}
}

int d[MaxN][MaxLogN];
int lg[MaxN];
void prepare() {
	dfs1(r, 0, 1);

	lg[1] = 0;
	for (int i = 2; i <= n; i++)
		lg[i] = lg[i - 1] + (int)(i == (1 << (lg[i - 1] + 1)));

	for (int i = 1; i <= n; i++)
		d[i][0] = fa[i];
	for (int i = 1; i <= lg[n]+1; i++)
		for (int j = 1; j <= n; j++)
			d[j][i] = d[d[j][i - 1]][i - 1];
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = lg[dep[v] - dep[u]]; i >= 0; i--)
		if (dep[d[u][i]] >= dep[v])
			u = d[u][i];
	if (u == v)
		return v;
	for (int i = lg[dep[u]]; i >= 0; i--)
		if (d[u][i] != d[v][i]) {
			u = d[u][i];
			v = d[v][i];
		}
	return fa[u];
}




int main(int argc, char* argv[]) {

	read(n, m, r);
	for (int i = 1; i <= n - 1; i++) {
		read(u, v);
		addedge(u, v);
	}

	prepare();
	for (int i = 1; i <= m; i++) {
		read(u, v);
		printf("%d\n", lca(u, v));
	}

	return 0;
}

#endif

