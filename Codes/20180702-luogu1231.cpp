/*
DOCUMENT NAME "20180702-luogu1231.cpp"
CREATION DATE 2018-07-02
SIGNATURE CODE_20180702_LUOGU1231
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180702_LUOGU1231

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 4 * 10000 + 2 + 10, MaxM = MaxN + 2 * 20000;

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
bool bfs() {
	Q.clear();
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

node* cur[MaxN];
int dfs(int u, int limit) {
	if (limit == 0 || u == t)
		return limit;
	int total = 0, f;
	for (node*& p = cur[u]; p != nullptr && limit > 0; p = p->next) {
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
	while (bfs()) {
		for (int i = 1; i <= n; i++)
			cur[i] = h[i];
		ans += dfs(s, infinity);
	}
	return ans;
}

#define GETPNT (++n)

int n1, n2, n3;
int m1, m2;

int n1in[MaxN], n1out[MaxN], n2id[MaxN], n3id[MaxN];


int main(int argc, char* argv[]) {

	cin >> n1 >> n2 >> n3;
	s = GETPNT; t = GETPNT;
	for (int i = 1; i <= n1; i++) {
		n1in[i] = GETPNT;
		n1out[i] = GETPNT;
		addedge(n1in[i], n1out[i], 1);
	}
	for (int i = 1; i <= n2; i++) {
		n2id[i] = GETPNT;
		addedge(s, n2id[i], 1);
	}
	for (int i = 1; i <= n3; i++) {
		n3id[i] = GETPNT;
		addedge(n3id[i], t, 1);
	}
	cin >> m1;
	int x, y;
	for (int i = 1; i <= m1; i++) {
		cin >> x >> y;
		addedge(n2id[y], n1in[x], 1);
	}
	cin >> m2;
	for (int i = 1; i <= m2; i++) {
		cin >> x >> y;
		addedge(n1out[x], n3id[y], 1);
	}

	cout << dinic() << endl;

	return 0;
}

#endif

