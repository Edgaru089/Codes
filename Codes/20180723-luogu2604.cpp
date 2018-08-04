/*
DOCUMENT NAME "20180723-luogu2604.cpp"
CREATION DATE 2018-07-23
SIGNATURE CODE_20180723_LUOGU2604
COMMENT [ZJOI2010]ÍøÂçÀ©ÈÝ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180723_LUOGU2604

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

template<typename IntType>
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

#pragma region EdmondsKarpCostFlow
constexpr int infinity = 1e8;
constexpr int MaxN = 5000 + 10, MaxM = 50000 + 10;

int n, m;
int s, t;

struct node {
	int v, flow, cost;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int flow, int cost) {
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
int dis[MaxN], limit[MaxN], from[MaxN];
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
			int v = p->v, flow = p->flow, cost = p->cost;
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

int maxflow, mincost;
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
#pragma endregion

int n0, m0, k;
int t0;

struct edge {
	int u, v, c, w;
};
edge e[MaxM];


int main(int argc, char* argv[]) {

	read(n0, m0, k);
	t0 = n0;
	s = 1; t = n0;
	n = n0 + 1;
	int u, v, c, w;
	for (int i = 1; i <= m0; i++) {
		read(u, v, c, w);
		e[i] = edge{u, v, c, w};
		addedge(u, v, c, 0);
	}

	t = n0;
	edmondsKarp();
	printf("%d ", maxflow);

	//memset(h, 0, sizeof(h));
	//memtop = mem;
	for (int i = 1; i <= m0; i++) {
		addedge(e[i].u, e[i].v, infinity, e[i].w);
		//addedge(e[i].u, e[i].v, e[i].c, 0);
	}
	addedge(n0, n0 + 1, k, 0);
	t = n0 + 1;

	edmondsKarp();
	printf("%d\n", mincost);

	return 0;
}

#endif

