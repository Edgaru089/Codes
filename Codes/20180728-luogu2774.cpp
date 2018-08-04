/*
DOCUMENT NAME "20180728-luogu2774.cpp"
CREATION DATE 2018-07-28
SIGNATURE CODE_20180728_LUOGU2774
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180728_LUOGU2774

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

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

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


constexpr int MaxN0 = 100 + 10;

#define GETCHAR getchar()
#define UNGETCHAR(c) ungetc(c, stdin);
template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }
void readstr(string& str) {
	int c;
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
}

int m0, n0;
int val[MaxN0][MaxN0];
int getid(int i, int j) {
	return (i - 1)*n0 + j;
}

int main(int argc, char* argv[]) {

	read(m0, n0);
	n = m0 * n0 + 2;
	s = m0 * n0 + 1;
	t = m0 * n0 + 2;
	for (int i = 1; i <= m0; i++)
		for (int j = 1; j <= n0; j++)
			read(val[i][j]);
	int sum = 0;
	for (int i = 1; i <= m0; i++)
		for (int j = 1; j <= n0; j++) {
			if ((i + j) % 2 == 1) {
				addedge(s, getid(i, j), val[i][j]);
				if (i > 1)
					addedge(getid(i, j), getid(i - 1, j), infinity);
				if (i < m0)
					addedge(getid(i, j), getid(i + 1, j), infinity);
				if (j > 1)
					addedge(getid(i, j), getid(i, j - 1), infinity);
				if (j < n0)
					addedge(getid(i, j), getid(i, j + 1), infinity);
			}
			else
				addedge(getid(i, j), t, val[i][j]);
			sum += val[i][j];
		}

	printf("%d\n", sum - dinic());

	return 0;
}

#endif

