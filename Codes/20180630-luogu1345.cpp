/*
DOCUMENT NAME "20180630-luogu1345.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU1345
COMMENT [USACO5.4]奶牛的电信Telecowmunication / 建图+最小割（最大流）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU1345

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 1000, MaxM = 60000 + 10, MaxNR = 2 * MaxN;

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
int s, t;
int u, v, flow;
int nr;

#define IN(x)  (x)
#define OUT(x) (x + n)

struct node {
	int v, flow;
	node* next;
	node* rev;
};

node* h[MaxNR];
node mem[MaxN * MaxN], *top = mem;
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


//template<typename Type, int Size = MaxN>
//class queue {
//public:
//	queue() { clear(); }
//	void clear() { left = 1; right = 0; }
//	void push(Type val) { arr[++right] = val; }
//	void pop() { left++; }
//	Type front() { return arr[left]; }
//	bool empty() { return right >= left; }
//private:
//	Type arr[Size];
//	int left, right;
//};


queue<int> Q;
int dep[MaxNR];
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

int main(int argc, char* argv[]) {

	read(n); read(m); read(s); read(t);
	nr = 2 * n; s = OUT(s); t = IN(t);
	for (int i = 1; i <= m; i++) {
		read(u); read(v);
		addedge(OUT(u), IN(v), infinity);
		addedge(OUT(v), IN(u), infinity);
	}
	for (int i = 1; i <= n; i++)
		addedge(IN(i), OUT(i), 1);

	printf("%d\n", dinic());

	return 0;
}

#endif

