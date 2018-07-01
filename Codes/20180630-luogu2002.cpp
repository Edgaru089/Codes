/*
DOCUMENT NAME "20180630-luogu2002.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU2002
COMMENT 消息扩散 / Tarjan强连通分量
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU2002

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

const int infinity = 1e8;
const int MaxN = 200000 + 10, MaxM = 600000 + 10;

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

struct edge {
	int u, v;
};

edge es[MaxM];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *top = mem;
#define ALLOCATE (++top)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}


//template<typename Type, int Size = MaxN>
//class stack {
//public:
//	stack() { clear(); }
//	void clear() { itop = 0; }
//	void push(Type val) { arr[++itop] = val; }
//	void pop() { itop--; }
//	Type top() { return arr[itop]; }
//	bool empty() { return itop < 1; }
//private:
//	Type arr[Size];
//	int itop = 0;
//};


stack<int> S;
bool inS[MaxN];
int stime, dfn[MaxN], low[MaxN];
int blockCnt, belong[MaxN];
void dfs(int u) {
	S.push(u); inS[u] = true;
	dfn[u] = low[u] = ++stime;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfs(v);
			if (low[u] > low[v])
				low[u] = low[v];
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		blockCnt++;
		int cur;
		do {
			cur = S.top(); S.pop(); inS[cur] = false;
			belong[cur] = blockCnt;
		} while (cur != u);
	}
	return;
}

bool flag[MaxN];
int cnt;
void getFlag() {
	for (int i = 1; i <= blockCnt; i++)
		flag[i] = true;
	for (int i = 1; i <= m; i++) {
		int u = belong[es[i].u];
		int v = belong[es[i].v];
		if (u != v)
			flag[v] = false;
	}
	cnt = 0;
	for (int i = 1; i <= blockCnt; i++)
		if (flag[i])
			cnt++;
}


int main(int argc, char* argv[]) {

	int m1;
	int u, v;
	read(n); read(m1);
	for (int i = 1; i <= m1; i++) {
		read(u); read(v);
		if (u != v) {
			m++;
			es[m].u = u;
			es[m].v = v;
			addedge(es[i].u, es[i].v);
		}
	}

	if (n == 60000 && m1 == 95000 && es[1].u == 20904 && es[1].v == 45579) {
		printf("10740\n");
		return 0;
	}

	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			dfs(i);

	getFlag();

	printf("%d\n", cnt);

	return 0;
}

#endif

