/*
DOCUMENT NAME "20180702-luogu4016.cpp"
CREATION DATE 2018-07-02
SIGNATURE CODE_20180702_LUOGU4016
COMMENT 负载平衡问题 / 费用流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180702_LUOGU4016

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100 + 2 + 10, MaxM = 3 * MaxN + 10;

template<typename Iterator, typename ValueType>
void valfill(Iterator begin, Iterator end, ValueType value) {
	for (; begin != end; begin++)
		*begin = value;
}

struct node {
	int v, flow, cost;
	node* rev;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *top = mem;
#define ALLOCATE (++top)

int n;
int s, t;

void addedge(int u, int v, int flow, int cost) {
	node* p = ALLOCATE, *pr = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->cost = cost;
	p->next = h[u];
	h[u] = p;
	pr->v = u;
	pr->flow = 0;
	pr->cost = -cost;
	pr->next = h[v];
	h[v] = pr;
	p->rev = pr;
	pr->rev = p;
}


queue<int> Q;
bool inQ[MaxN];
int dis[MaxN], flowlimit[MaxN];
int pre[MaxN];
node* fromedge[MaxN];
bool bfs() {
	valfill(dis + 1, dis + n + 1, infinity);
	valfill(flowlimit + 1, flowlimit + n + 1, infinity);
	valfill(inQ + 1, inQ + n + 1, false);
	valfill(pre + 1, pre + n + 1, 0);
	valfill(fromedge + 1, fromedge + n + 1, nullptr);
	Q.push(s);
	dis[s] = 0;
	pre[s] = 0;
	inQ[s] = true;
	while (!Q.empty()) {
		int u = Q.front(), v, flow, cost;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow; cost = p->cost;
			if (flow != 0 && dis[v] > dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				fromedge[v] = p;
				flowlimit[v] = min(flowlimit[u], flow);
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
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
	int v = t;
	while (v != s) {
		node* p = fromedge[v];
		p->flow -= flowlimit[t];
		p->rev->flow += flowlimit[t];
		v = pre[v];
	}
	maxflow += flowlimit[t];
	mincost += flowlimit[t] * dis[t];
}


void edmondsKarp() {
	maxflow = 0;
	mincost = 0;
	while (bfs())
		update();
}

int k;
int a[MaxN];
int sum;

int main(int argc, char* argv[]) {

	cin >> k;
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
		sum += a[i];
	}
	s = k + 1; t = k + 2;
	n = k + 2;
	int val = sum / k;
	for (int i = 1; i <= k; i++)
		if (a[i] > val)
			addedge(s, i, a[i] - val, 0);
		else if (a[i] < val)
			addedge(i, t, val - a[i], 0);
	for (int i = 1; i <= k; i++) {
		addedge(i, i % k + 1, infinity, 1);
		addedge(i % k + 1, i, infinity, 1);
	}

	edmondsKarp();

	cout << mincost << endl;

	return 0;
}

#endif

