/*
DOCUMENT NAME "20180722-luogu3381.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU3381
COMMENT 【模板】最小费用最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU3381

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;


#pragma region EdmondsKarpCostFlow
constexpr int infinity = 1e8;
constexpr int MaxN = 5000 + 10, MaxM = 50000 + 10;

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

void edmondsKarp(){
	while (bfs())
		update();
}
#pragma endregion


int main(int argc, char* argv[]) {

	read(n, m, s, t);
	for (int i = 1; i <= m; i++) {
		int u, v, f, c;
		read(u, v, f, c);
		addedge(u, v, f, c);
	}

	edmondsKarp();

	printf("%d %d\n", maxflow, mincost);

	return 0;
}

#endif

