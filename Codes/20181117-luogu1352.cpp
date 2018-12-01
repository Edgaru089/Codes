/*
 DOCUMENT NAME "20181117-luogu1352.cpp"
 CREATION DATE 2018-11-17
 SIGNATURE CODE_20181117_LUOGU1352
 COMMENT P1352 没有上司的舞会
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181117_LUOGU1352

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

const int MaxN = 6000 + 10;

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

int n;
int a[MaxN];
int l, k;
int incnt[MaxN];

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
	incnt[v]++;
}

int dp[MaxN][2];

void dfs(int u, int from) {
	dp[u][1] = a[u];
	dp[u][0] = 0;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs(v, u);
			dp[u][1] += dp[v][0];
			dp[u][0] += max(dp[v][1], dp[v][0]);
		}
	}
}



int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i < n; i++) {
		read(l); read(k);
		addedge(k, l);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (incnt[i] == 0) {
			dfs(i, 0);
			ans += max(dp[i][1], dp[i][0]);
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

