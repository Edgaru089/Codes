/*
 DOCUMENT NAME "20181218-luogu3376.cpp"
 CREATION DATE 2018-12-18
 SIGNATURE CODE_20181218_LUOGU3376
 COMMENT 【模板】网络最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181218_LUOGU3376

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <queue>
using namespace std;

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
const int MaxN = 10000 + 10, MaxM = 1000000 + 10;

int n, m;
int s, t;

struct node {
	int v, flow;
	node* next;
	node* rev;
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
	memset(dis, 0, sizeof(dis));
	Q.push(s);
	dis[s] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (node* p = h[u]; p; p = p->next) {
			int v = p->v;
			if (p->flow && !dis[v]) {
				dis[v] = dis[u] + 1;
				Q.push(v);
			}
		}
	}
	return dis[t];
}

node* cur[MaxN];
int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int ans = 0;
	for (node*& p = cur[u]; p; p = p->next) {
		int v = p->v;
		int d;
		if (dis[v] == dis[u] + 1 && (d = dfs(v, min(limit, p->flow))) != 0) {
			limit -= d;
			p->flow -= d;
			p->rev->flow += d;
			ans += d;
		}
		if (!limit)
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

	read(n); read(m); read(s); read(t);
	for (int i = 1; i <= n; i++) {
		int u, v, f;
		read(u); read(v); read(f);
		addedge(u, v, f);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

