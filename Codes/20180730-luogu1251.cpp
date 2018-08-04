/*
DOCUMENT NAME "20180730-luogu1251.cpp"
CREATION DATE 2018-07-30
SIGNATURE CODE_20180730_LUOGU1251
COMMENT 餐巾计划问题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180730_LUOGU1251

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

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

using ll = long long;

constexpr int infinity = 1e8;
constexpr int MaxN = 4 * 2000 + 2 + 10, MaxM = 3 * MaxN + 10;
int n;
int s, t;
struct node {
	int v;
	ll flow, cost;
	node* next;
	node* rev;
};
node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)
void addedge(int u, int v, ll flow, ll cost) {
	node* p1 = ALLOCATE;
	p1->v = v;
	p1->flow = flow;
	p1->cost = cost;
	p1->next = h[u];
	h[u] = p1;
	node* p2 = ALLOCATE;
	p2->v = u;
	p2->flow = 0;
	p2->cost = -cost;
	p2->next = h[v];
	h[v] = p2;
	p1->rev = p2;
	p2->rev = p1;
}
template<typename Iterator, typename ValType>
void valfill(Iterator begin, Iterator end, ValType val) {
	while (begin != end) {
		*begin = val;
		begin++;
	}
}
queue<int> Q;
bool inQ[MaxN];
ll dis[MaxN], limit[MaxN];
int from[MaxN];
node* fromedge[MaxN];
bool bfs() {
	while (!Q.empty())
		Q.pop();
	valfill(inQ + 1, inQ + n + 1, false);
	valfill(dis + 1, dis + n + 1, infinity);
	valfill(limit + 1, limit + n + 1, infinity);
	Q.push(s);
	inQ[s] = true;
	dis[s] = 0;
	from[s] = 0;
	fromedge[s] = nullptr;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			ll flow = p->flow, cost = p->cost;
			if (flow > 0) {
				if (dis[v] > dis[u] + cost) {
					dis[v] = dis[u] + cost;
					limit[v] = min(limit[u], flow);
					from[v] = u;
					fromedge[v] = p;
					if (!inQ[v]) {
						inQ[v] = true;
						Q.push(v);
					}
				}
			}
		}
	}
	if (dis[t] == infinity)
		return false;
	else
		return true;
}
ll maxflow, mincost;
void update() {
	maxflow += limit[t];
	mincost += limit[t] * dis[t];
	int v = t;
	while (v != s) {
		node* p = fromedge[v];
		p->flow -= limit[t];
		p->rev->flow += limit[t];
		v = from[v];
	}
}
void edmondsKarp() {
	while (bfs())
		update();
}



int n0;
ll d[MaxN];
int newcost, fasttime, fastcost, slowtime, slowcost;

int inid(int day) { return day; }
int outid(int day) { return day + n0; }


int main(int argc, char* argv[]) {

	read(n0);
	s = 2 * n0 + 1;
	t = 2 * n0 + 2;
	n = 2 * n0 + 2;
	for (int i = 1; i <= n0; i++)
		read(d[i]);
	read(newcost, fasttime, fastcost, slowtime, slowcost);

	for (int i = 1; i <= n0; i++) {
		addedge(outid(i), t, d[i], 0);
		addedge(s, inid(i), d[i], 0);
		addedge(s, outid(i), infinity, newcost);
		if (i > 1) {
			addedge(inid(i - 1), inid(i), infinity, 0);
			addedge(outid(i - 1), outid(i), infinity, 0);
		}
		if (i + fasttime <= n0)
			addedge(inid(i), outid(i + fasttime), infinity, fastcost);
		if (i + slowtime <= n0)
			addedge(inid(i), outid(i + slowtime), infinity, slowcost);
	}

	edmondsKarp();

	printf("%lld\n", mincost);

	return 0;
}

#endif

