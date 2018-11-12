/*
 DOCUMENT NAME "20181111-luogu1137.cpp"
 CREATION DATE 2018-11-11
 SIGNATURE CODE_20181111_LUOGU1137
 COMMENT P1131 [ZJOI2007]Ê±Ì¬Í¬²½
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181111_LUOGU1137

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)								\
{printf(#arr ":");																\
for (int __i_##arr = beginoff; __i_##arr <= beginoff + size - 1; __i_##arr++)	\
	printf("\t%d", __i_##arr);													\
printf("\n");																	\
for (int __i_##arr = beginoff; __i_##arr <= beginoff + size - 1; __i_##arr++)	\
	printf("\t" formatstr, arr[__i_##arr]);										\
printf("\n"); }
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
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

typedef long long ll;
const int MaxN = 500000 + 10;

int n, s;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

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

ll cost[MaxN], maxlen[MaxN];

void dfs(int u, int from) {
	DEBUG("dfs u=%d, from=%d\n", u, from);
	cost[u] = 0;
	maxlen[u] = 0;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs(v, u);
			cost[u] += cost[v];
			maxlen[u] = max(maxlen[u], maxlen[v] + p->len);
		}
	}
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from) {
			cost[u] += maxlen[u] - (maxlen[v] + p->len);
		}
	}
}



int main(int argc, char* argv[]) {

	read(n); read(s);
	for (int i = 1; i <= n - 1; i++) {
		int u, v, l;
		read(u); read(v); read(l);
		addedge(u, v, l);
	}

	dfs(s, 0);
	printf("%lld\n", cost[s]);
	PRINTARR("%lld", cost, 1, n);
	PRINTARR("%lld", maxlen, 1, n);

	return 0;
}

#endif

