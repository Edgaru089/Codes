/*
DOCUMENT NAME "20180628-luogu3386.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3386
COMMENT 【模板】二分图匹配 / 网络流建图+Dinic
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3386

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

constexpr int infinity = 1000000000;
constexpr int MaxN = 3000 + 10, MaxM = 7500000 + 10;

int read() {
	char c;
	int val = 0;

	while (!isdigit(c = getchar()));

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	return val;
}

int read(int& val) {
	return val = read();
}


struct node {
	int v, flow;
	node* rev;
	node* next;
};

node mem[MaxM], *h[MaxN];
int top;
node* allocate() { return &mem[++top]; }

void addedge(int u, int v, int flow) {
	node* reg = allocate();
	reg->v = v;
	reg->flow = flow;
	reg->next = h[u];
	h[u] = reg;
	node* rev = allocate();
	rev->v = u;
	rev->flow = 0;
	rev->next = h[v];
	h[v] = rev;
	reg->rev = rev;
	rev->rev = reg;
}

int n1, n2, m;
int n;
int s, t;
int dep[MaxN];

queue<int> Q;
bool bfs() {
	while (!Q.empty())
		Q.pop();
	for (int i = 1; i <= n; i++)
		dep[i] = infinity;
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front(), v, flow;
		Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow;
			if (flow > 0) {
				if (dep[v] == infinity) {
					dep[v] = dep[u] + 1;
					Q.push(v);
				}
			}
		}
	}
	if (dep[t] == infinity)
		return false;
	else
		return true;
}

int dfs(int u, int limit) {
	if (limit == 0 || u == t)
		return limit;
	int total = 0, f;
	for (node* p = h[u]; p != nullptr && limit > 0; p = p->next) {
		int v = p->v; int& flow = p->flow;
		if (dep[v] == dep[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
			flow -= f;
			p->rev->flow += f;
			total += f;
			limit -= f;
		}
	}
	return total;
}

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


int main(int argc, char* argv[]) {

	read(n1); read(n2); read(m);
	for (int i = 1; i <= m; i++) {
		int x1, x2;
		read(x1); read(x2);
		if (x2 > n2)
			continue;
		addedge(x1, n1 + x2, 1);
	}

	s = n1 + n2 + 1; t = n1 + n2 + 2;
	n = n1 + n2 + 2;
	for (int i = 1; i <= n1; i++)
		addedge(s, i, 1);
	for (int i = 1; i <= n2; i++)
		addedge(n1 + i, t, 1);

	printf("%d\n", dinic());

	return 0;
}

#endif

