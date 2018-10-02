/*
 DOCUMENT NAME "20180911-luogu3376.cpp"
 CREATION DATE 2018-09-11
 SIGNATURE CODE_20180911_LUOGU3376
 COMMENT 【模板】网络最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180911_LUOGU3376

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = getchar()));
	do { ans = (ans << 1) + (ans << 3) + c - '0'; } while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return ans;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;
int s, t;
struct node {
	int v, flow;
	node* next, *rev;
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
template<typename Type, int Size = 4 * MaxN>
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
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.clear();
	dis[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (p->flow > 0 && dis[v] == infinity) {
				dis[v] = dis[u] + 1;
				Q.push(v);
			}
		}
	}
	return dis[t] < infinity;
}

node* cur[MaxN];
int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int ans = 0;
	for (node*& p = cur[u]; limit > 0 && p != nullptr; p = p->next) {
		int v = p->v, f;
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(limit, p->flow))) > 0) {
			limit -= f;
			p->flow -= f;
			p->rev->flow += f;
			ans += f;
		}
		if (limit == 0)
			break;
	}
	return ans;
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



int main(int argc, char* argv[]) {

	read(n, m, s, t);
	int u, v, flow;
	for (int i = 1; i <= m; i++) {
		read(u, v, flow);
		addedge(u, v, flow);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

