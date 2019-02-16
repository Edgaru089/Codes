/*
 DOCUMENT NAME "20190120-luogu1099.cpp"
 CREATION DATE 2019-01-20
 SIGNATURE CODE_20190120_LUOGU1099
 COMMENT Ê÷ÍøµÄºË£¨bndsoj0640£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190120_LUOGU1099

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
#endif

template<typename IntType>
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

const int infinity = 1e8;
const int MaxN = 300 + 10;

struct node {
	int v, len;
	node* next;
};

node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

node* h[MaxN];

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}

int n;
int s;
int l, r;
int dis[MaxN], fa[MaxN];

bool used[MaxN];
int fa0[MaxN], falen0[MaxN], dis0[MaxN];

void dfs(int u, int from, int len) {
	fa[u] = from;
	dis[u] = len;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from)
			dfs(v, u, len + p->len);
	}
}

void dfspre0(int u, int from, int fromlen) {
	fa0[u] = from;
	falen0[u] = fromlen;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from)
			dfspre0(v, u, p->len);
	}
}

int dfs0(int u) {
	if (dis0[u] >= 0)
		return dis0[u];
	else {
		DEBUG("        Calculating value for dfs0(%d)\n", u);
		return dis0[u] = dfs0(fa0[u]) + falen0[u];
	}
}


int main(int argc, char* argv[]) {

	read(n); read(s);
	for (int i = 1; i <= n - 1; i++) {
		int u, v, l;
		read(u); read(v); read(l);
		addedge(u, v, l);
	}

	dfs(1, 0, 0);
	int maxdis = 0;
	for (int i = 1; i <= n; i++)
		if (dis[i] > maxdis) {
			maxdis = dis[i];
			l = i;
		}
	dfs(l, 0, 0);
	maxdis = 0;
	for (int i = 1; i <= n; i++)
		if (dis[i] > maxdis) {
			maxdis = dis[i];
			r = i;
		}

	DEBUG("l=%d, r=%d\n", l, r);
	PRINTARR("%d", fa, 1, n);

	int ans = infinity;

	for (int i = r; i; i = fa[i]) {
		for (int j = i; j; j = fa[j]) {
			if (dis[i] - dis[j] <= s) {
				DEBUG("Checking chain %d - %d:\n", i, j);
				memset(dis0, -1, sizeof(dis0));
				memset(used, 0, sizeof(used));
				for (int k = i; k != j; k = fa[k]) {
					DEBUG("    %d used\n", k);
					used[k] = true;
					dis0[k] = 0;
				}
				DEBUG("    %d used\n", j);
				used[j] = true;
				dis0[j] = 0;
				dfspre0(j, 0, 0);
				PRINTARR("%d", fa0, 1, n);

				int val = 0;
				for (int k = 1; k <= n; k++)
					if (!used[k]) {
						int d0 = dfs0(k);
						DEBUG("    %d not used, dis=%d\n", k, d0);
						val = max(val, d0);
					}

				ans = min(ans, val);
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

