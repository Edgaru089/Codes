/*
DOCUMENT NAME "20180628-luogu3376.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3376
COMMENT 【模板】网络最大流 / Dinic
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3376

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

constexpr int infinity = 1000000000;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

struct node {
	int v, flow;
	node* rev;
	node* next;
};

node mem[MaxM * 4], *h[MaxN];
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

int n, m;
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

	cin >> n >> m >> s >> t;
	int u, v, flow;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> flow;
		addedge(u, v, flow);
	}

	cout << dinic() << endl;

	return 0;
}

#endif

