/*
DOCUMENT NAME "20180630-luogu2756.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU2756
COMMENT 飞行员配对方案问题 / 二分图匹配（最大流）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU2756

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100 + 10, MaxM = MaxN * MaxN + 10, MaxNF = MaxN;

int read() {
	char c;
	int val = 0;
	bool minus = false;

	while (!isdigit(c = getchar()))
		if (c == '-')
			minus = true;

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	if (minus)
		return -val;
	else
		return val;
}

int read(int& val) {
	return val = read();
}

int n, nf, m;
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

node* h[MaxN];
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


int main(int argc, char* argv[]) {

	read(nf); read(n);
	int u, v;
	for (;;) {
		read(u); read(v);
		if (u == -1 && v == -1)
			break;
		m++;
		addedge(u, v, infinity);
	}

	s = n + 1;
	t = n + 2;

	for (int i = 1; i <= nf; i++)
		addedge(s, i, 1);
	for (int i = nf + 1; i <= n; i++)
		addedge(i, t, 1);

	printf("%d\n", dinic());
	for (int i = 1; i <= nf; i++) {
		for (node* p = h[i]; p != nullptr; p = p->next)
			if (p->rev->flow != 0 && p->v <= n) {
				printf("%d %d\n", i, p->v);
				break;
			}
	}

	return 0;
}

#endif

