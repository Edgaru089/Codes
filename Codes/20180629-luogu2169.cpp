/*
DOCUMENT NAME "20180629-luogu2169.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU2169
COMMENT 正则表达式 / Tarjan强连通分量缩点+SPFA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU2169

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 200000 + 10, MaxM = 1000000 + 10;

int n, m;

struct edge {
	edge() {}
	edge(int u, int v, int len) :u(u), v(v), len(len) {}
	int u, v;
	int len;
};

edge es[MaxM];

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *top = mem;
#define ALLOCATE (++top)

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}


stack<int> S;
bool inS[MaxN];
int stime, dfn[MaxN], low[MaxN];
//vector<int> blocks[MaxN];
int belong[MaxN];
int blockCnt;
void dfs(int u) {
	S.push(u); inS[u] = true;
	dfn[u] = low[u] = ++stime;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v, len = p->len;
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int cnt;
		blockCnt++;
		do {
			cnt = S.top(); S.pop(); inS[cnt] = false;
			//blocks[blockCnt].push_back(cnt);
			belong[cnt] = blockCnt;
		} while (cnt != u);
	}
}

void reconstruct() {
	memset(h, 0, sizeof(h));
	top = mem;
	for (int i = 1; i <= m; i++) {
		int u = belong[es[i].u], v=belong[es[i].v], len = es[i].len;
		if (u != v) {
			addedge(u, v, len);
		}
	}
}

queue<int> Q;
bool inQ[MaxN];
int dis[MaxN];
void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(belong[1]);
	inQ[belong[1]] = true;
	dis[belong[1]] = 0;
	while (!Q.empty()) {
		int u = Q.front(), v, len;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> es[i].u >> es[i].v >> es[i].len;
		addedge(es[i].u, es[i].v, es[i].len);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}

	reconstruct();

	spfa();

	cout << dis[belong[n]] << endl;

	return 0;
}

#endif

