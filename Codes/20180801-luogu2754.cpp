/*
DOCUMENT NAME "20180801-luogu2754.cpp"
CREATION DATE 2018-08-01
SIGNATURE CODE_20180801_LUOGU2754
COMMENT [CTSC1999]家园
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180801_LUOGU2754

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
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

int ans = 0;
int dinic() {
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


constexpr int MaxN0 = 13 + 2 + 10, MaxM0 = 20 + 10;;
int n0, m0, k;
int h[MaxM0], r[MaxM0];
vector<int> s0[MaxM0];

int ans = 0;
int curid[MaxM0];

int stationpnt(int id, int time) {
	if (id == 0)
		id = n0 + 1;
	if (id == -1)
		id = n0 + 2;
	return id + time * (n0 + 2);
}


int main(int argc, char* argv[]) {

	read(n0, m0, k);
	n = (n0 * n0 + 2 * n0)*(n0 + 2) + 2;

	for (int i = 1; i <= m0; i++) {
		read(h[i], r[i]);
		for (int j = 1; j <= r[i]; j++)
			s0[i].push_back(read());
	}

	s = (n0 * n0 + 2 * n0)*(n0 + 2) + 1;
	t = (n0 * n0 + 2 * n0)*(n0 + 2) + 2;
	addedge(s, stationpnt(0, 0), k);
	addedge(stationpnt(-1, 0), t, k);

	for (ans = 0; ans <= n0 * n0 + n0; ans++) {
		if (ans > 0) {
			for (int i = -1; i < n0; i++) {
				addedge(stationpnt(i, ans - 1), stationpnt(i, ans), infinity);
			}
			addedge(stationpnt(m0, ans), stationpnt(m0, ans - 1), infinity);
			for (int i = 1; i <= m0; i++) {
				int uid=
			}
		}
	}

	return 0;
}

#endif

