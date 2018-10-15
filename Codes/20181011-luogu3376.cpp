/*
 DOCUMENT NAME "20181011-luogu3376.cpp"
 CREATION DATE 2018-10-11
 SIGNATURE CODE_20181011_LUOGU3376
 COMMENT 【模板】网络最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181011_LUOGU3376

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int infinity = 1e8;
const int MaxN = 10000 + 10, MaxM = 100000 + 10;

void read(int& val) {
	val = 0;
	int c;
	bool inv = false;;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

int n, m;
int s, t;

struct node {
	int v, flow;
	node* next, *rev;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int flow) {
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h[u];
	h[u] = p;
	node* pr = ALLOCATE;
	pr->v = u;
	pr->next = h[v];
	h[v] = pr;
	pr->rev = p;
	p->rev = pr;
}

int dis[MaxN];
queue<int> Q;
bool bfs() {
	memset(dis, 0, sizeof(int)*(n + 1));
	Q.push(s);
	dis[s] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (node* p = h[u]; p; p = p->next) {
			int& v = p->v;
			if (p->flow != 0 && dis[v] == 0) {
				dis[v] = dis[u] + 1;
				Q.push(v);
			}
		}
	}
	return dis[t] != 0;
}

node* cur[MaxN];
int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int ans = 0;
	for (node*& p = cur[u]; p&&limit; p = p->next) {
		int v = p->v, &flow = p->flow;
		int f;
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(flow, limit))) != 0) {
			flow -= f;
			p->rev->flow += f;
			ans += f;
			limit -= f;
		}
		if (limit == 0)
			break;
	}
	return ans;
}

int dinic() {
	int ans = 0;
	while (bfs()) {
		for (int i = 1; i <= n; i++)
			cur[i] = h[i];
		ans += dfs(s, infinity);
	}
	return ans;
}




int main(int argc, char* argv[]) {

	read(n); read(m);
	read(s); read(t);
	for (int i = 1; i <= m; i++) {
		int u, v, flow;
		read(u); read(v); read(flow);
		addedge(u, v, flow);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

