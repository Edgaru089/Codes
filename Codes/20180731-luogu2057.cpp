/*
DOCUMENT NAME "20180731-luogu2057.cpp"
CREATION DATE 2018-07-31
SIGNATURE CODE_20180731_LUOGU2057
COMMENT [SHOI2007]ÉÆÒâµÄÍ¶Æ±
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180731_LUOGU2057

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

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
	node* p1 = ALLOCATE;
	p1->v = v;
	p1->flow = flow;
	p1->next = h[u];
	h[u] = p1;
	node* p2 = ALLOCATE;
	p2->v = u;
	p2->flow = 0;
	p2->next = h[v];
	h[v] = p2;
	p1->rev = p2;
	p2->rev = p1;
}

int dis[MaxN];

queue<int> Q;
bool bfs() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(s);
	dis[s] = 0;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, flow = p->flow;
			if (flow > 0)
				if (dis[v] == infinity) {
					dis[v] = dis[u] + 1;
					Q.push(v);
				}
		}
	}
	if (dis[t] == infinity)
		return false;
	else
		return true;
}

int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int val = 0;
	for (node* p = h[u]; p != nullptr&&limit > 0; p = p->next) {
		int v = p->v, f;
		int& flow = p->flow;
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
			flow -= f;
			p->rev->flow += f;
			limit -= f;
			val += f;
		}
	}
	return val;
}

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}

int n0, m0;
int u, v;

int main(int argc, char* argv[]) {

	read(n0, m0);
	s = n0 + 1;
	t = n0 + 2;
	n = n0 + 2;
	for (int i = 1; i <= n0; i++)
		if (read() == 1)
			addedge(s, i, 1);
		else
			addedge(i, t, 1);
	for (int i = 1; i <= m0; i++) {
		read(u, v);
		addedge(u, v, 1);
		addedge(v, u, 1);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

