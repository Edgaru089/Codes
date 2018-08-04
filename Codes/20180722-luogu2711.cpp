/*
DOCUMENT NAME "20180722-luogu2711.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU2711
COMMENT 小行星 / 最小割（最大流）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU2711

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int MaxXYZ = 500 + 10;

#pragma region Dinic
constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 3 * 500 + 3 * 50000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }


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
#pragma endregion

int n0;
int x, y, z;

int xpnt(int x) { return x; };
int zpnt(int z) { return z + MaxXYZ; }
int yinpnt(int y) { return y + 2 * MaxXYZ; }
int youtpnt(int y) { return y + 3 * MaxXYZ; }

int main(int argc, char* argv[]) {

	read(n0);
	s = 4 * MaxXYZ + 1;
	t = 4 * MaxXYZ + 2;
	n = 4 * MaxXYZ + 2;
	for (int i = 1; i <= MaxXYZ; i++) {
		addedge(s, xpnt(i), 1);
		addedge(yinpnt(i), youtpnt(i), 1);
		addedge(zpnt(i), t, 1);
	}
	for (int i = 1; i <= n0; i++) {
		read(x, y, z);
		addedge(xpnt(x), yinpnt(y), infinity);
		addedge(youtpnt(y), zpnt(z), infinity);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

