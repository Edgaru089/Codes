/*
DOCUMENT NAME "20180628-luogu3387.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3387
COMMENT 【模板】缩点 / Tarjan强连通分量 + 记忆化搜索
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3387

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr int infinity = 1000000000;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

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
int pointSize[MaxN];

struct edge {
	int u, v;
};
edge e[MaxM];


struct node {
	int v;
	node* next;
};

node mem[MaxM * 2], *h[MaxN];
int top;
#define ALLOCATE (&mem[++top])

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}


template<typename Type, int Size = 2 * MaxN>
class stack {
public:
	stack() { _top = 0; }
	void clear() { _top = 0; }
	void push(Type val) { arr[++_top] = val; }
	Type top() { return arr[_top]; }
	void pop() { _top--; }
	bool empty() { return _top <= 0; }
private:
	int _top;
	Type arr[Size];
};

vector<int> blocks[MaxN];
int blockCnt = 0, blockSize[MaxN];
int belongBlock[MaxN];

stack<int> S;
bool inS[MaxN];
int Time = 0, dfn[MaxN], low[MaxN];

void dfsTarjan(int u) {

	dfn[u] = low[u] = ++Time;
	S.push(u); inS[u] = true;

	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfsTarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}

	if (dfn[u] == low[u]) {
		int x;
		blockCnt++;
		blocks[blockCnt].clear();
		blockSize[blockCnt] = 0;
		do {
			x = S.top(); S.pop(); inS[x] = false;
			belongBlock[x] = blockCnt;
			blocks[blockCnt].push_back(x);
			blockSize[blockCnt] += pointSize[x];
		} while (x != u);
	}
}


node* hx[MaxN];

void addedgeX(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = hx[u];
	hx[u] = p;
}

void initBlockPoints() {
	for (int i = 1; i <= m; i++) {
		int u = belongBlock[e[i].u], v = belongBlock[e[i].v];
		if (u != v) {
			addedgeX(u, v);
		}
	}
}

int dfsAns[MaxN];
bool been[MaxN];
int dfs(int u) {
	if (dfsAns[u] != -1)
		return dfsAns[u];
	else {
		been[u] = true;

		int ans = 0;
		for (node* p = hx[u]; p != nullptr; p = p->next)
			ans = max(ans, dfs(p->v));

		been[u] = false;
		return dfsAns[u] = blockSize[u] + ans;
	}
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++)
		read(pointSize[i]);
	for (int i = 1; i <= m; i++) {
		read(e[i].u); read(e[i].v);
		addedge(e[i].u, e[i].v);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfsTarjan(i);
	}
	initBlockPoints();

	memset(dfsAns, -1, sizeof(dfsAns));

	int ans = 0;
	for (int i = 1; i <= blockCnt; i++) {
		ans = max(ans, dfs(i));
	}

	printf("%d\n", ans);

	return 0;
}

#endif

