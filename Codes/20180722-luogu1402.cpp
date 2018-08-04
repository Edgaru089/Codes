/*
DOCUMENT NAME "20180722-luogu1402.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU1402
COMMENT ¾ÆµêÖ®Íõ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU1402

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#pragma region Dinic
constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

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


int n0, p, q;

int inpntid(int id) { return id; }
int outpntid(int id) { return n0 + id; }
int roompntid(int roomid) { return roomid + 2 * n0; }
int dishpntid(int dishid) { return dishid + 2 * n0 + p; }


int main(int argc, char* argv[]) {

	read(n0, p, q);
	n = 2 * n0 + p + q + 2;
	s = 2 * n0 + p + q + 1;
	t = 2 * n0 + p + q + 2;
	for (int i = 1; i <= p; i++)
		addedge(s, roompntid(i), 1);
	for (int i = 1; i <= q; i++)
		addedge(dishpntid(i), t, 1);
	for (int i = 1; i <= n0; i++)
		addedge(inpntid(i), outpntid(i), 1);
	for (int i = 1; i <= n0; i++) {
		for (int j = 1; j <= p; j++) {
			int x;
			read(x);
			if (x == 1)
				addedge(roompntid(j), inpntid(i), 1);
		}
	}
	for (int i = 1; i <= n0; i++) {
		for (int j = 1; j <= q; j++) {
			int x;
			read(x);
			if (x == 1)
				addedge(outpntid(i), dishpntid(j), 1);
		}
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

