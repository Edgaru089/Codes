/*
 DOCUMENT NAME "20180920-bnds0774.cpp"
 CREATION DATE 2018-09-20
 SIGNATURE CODE_20180920_BNDS0774
 COMMENT #774. »ð³µ / ÇóÁ´³¤
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180920_BNDS0774

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 500000 + 10, MaxM = 500000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;

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

int father[MaxN], ssize[MaxN], dep[MaxN], heavy[MaxN];
void dfs1(int u, int from = 0, int step = 1) {
	father[u] = from;
	ssize[u] = 1;
	dep[u] = step;
	int maxsize = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u]) {
			dfs1(v, u, step + 1);
			if (maxsize < ssize[v]) {
				maxsize = ssize[v];
				heavy[u] = v;
			}
		}
	}
}

int dfn[MaxN], sstime, top[MaxN];
void dfs2(int u, int t) {
	dfn[u] = ++sstime;
	top[u] = t;
	if (heavy[u] != 0)
		dfs2(heavy[u], t);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavy[u])
			dfs2(v, v);
	}
}

int d[MaxN];
void build() {
	dfs1(1);
	dfs2(1, 1);
}

int query(int u, int v) {
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			ans += dep[u] - dep[top[u]] + 1;
			u = father[top[u]];
		}
		else {
			ans += dep[v] - dep[top[v]] + 1;
			v = father[top[v]];
		}
	}
	if (dep[u] > dep[v])
		ans += dep[u] - dep[v];
	else
		ans += dep[v] - dep[u];
	return ans;
}

int a;
int k[MaxM];
bool flag[MaxN];

int main(int argc, char* argv[]) {

	read(n, m, a);
	for (int i = 1; i < n; i++) {
		int u, v;
		read(u, v);
		addedge(u, v);
	}

	build();

	flag[a] = true;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int k = read();
		if (!flag[k]) {
			flag[k] = true;
			ans += query(a, k);
			a = k;
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

