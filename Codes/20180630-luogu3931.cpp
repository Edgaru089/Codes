/*
DOCUMENT NAME "20180630-luogu3931.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU3931
COMMENT SAC E#1 - 一道难题 Tree / 最小割（最大流/Dinic）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU3931

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10, MaxM = 10 * MaxN;

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

int n, m;
int root;
int s, t;
int u, v, flow;

#define IN(x)  (x)
#define OUT(x) (x + n)

struct node {
	int v, flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[MaxM], *top = mem;
#define ALLOCATE (++top)

void addedge(int u, int v, int flow) {
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h[u];
	h[u] = p;
	node* pr = ALLOCATE;
	pr->v = u;
	pr->flow = 0;
	pr->next = h[v];
	h[v] = pr;
	p->rev = pr;
	pr->rev = p;
}


template<typename Type, int Size = MaxN>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

queue<int> Q;
int dep[MaxN];
bool bfs() {
	memset(dep, 0, sizeof(dep));
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow;
			if (flow != 0) {
				if (dep[v] == 0) {
					dep[v] = dep[u] + 1;
					Q.push(v);
				}
			}
		}
	}
	if (dep[t] == 0)
		return false;
	else
		return true;
}

int dfs(int u, int limit) {
	if (limit == 0 || u == t)
		return limit;
	int f, ans = 0;
	for (node* p = h[u]; p != nullptr && limit > 0; p = p->next) {
		v = p->v; flow = p->flow;
		if (dep[v] == dep[u] + 1 && (f = dfs(v, min(flow, limit))) != 0) {
			limit -= f;
			p->flow -= f;
			p->rev->flow += f;
			ans += f;
		}
	}
	return ans;
}

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


node* h0[MaxN];
void addedgeH0(int u, int v, int flow) {
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h0[u];
	h0[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->flow = flow;
	p->next = h0[v];
	h0[v] = p;
}

queue<int> Q0;
bool been[MaxN];
vector<int> leaves;
void bfsH0() {
	Q0.push(root);
	been[root] = true;
	while (!Q0.empty()) {
		int u = Q0.front(), v, flow; Q0.pop();
		bool flag = false;
		for (node* p = h0[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow;
			if (!been[v]) {
				flag = true;
				been[v] = true;
				Q0.push(v);
				addedge(u, v, flow);
			}
		}
		if (!flag)
			leaves.push_back(u);
	}
}


int main(int argc, char* argv[]) {

	read(n); read(root);
	for (int i = 1; i <= n - 1; i++) {
		int u, v, flow;
		read(u); read(v); read(flow);
		addedgeH0(u, v, flow);
		addedgeH0(v, u, flow);
	}

	bfsH0();

	s = n + 1;
	t = n + 2;
	addedge(s, root, infinity);
	for (int i : leaves)
		addedge(i, t, infinity);

	printf("%d\n", dinic());

	return 0;
}

#endif

