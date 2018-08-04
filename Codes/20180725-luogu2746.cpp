/*
DOCUMENT NAME "20180725-luogu2746.cpp"
CREATION DATE 2018-07-25
SIGNATURE CODE_20180725_LUOGU2746
COMMENT [USACO5.3]Ð£Ô°ÍøNetwork of Schools
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180725_LUOGU2746

#include <cstdlib>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

const int infinity = 1e5;
const int MaxN = 100000 + 10, MaxM = 500000 + 10;

int n, m;
int val[MaxN];

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

int read(int& val) { return val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

struct node {
	int v;
	node* next;
};

node* h[MaxN], *hdag[MaxN];
node mem[4 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, node** h = ::h) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}

int stime, dfn[MaxN], low[MaxN];
int blockcnt, belong[MaxN];
stack<int> S;
bool inS[MaxN];
void dfs(int u) {
	dfn[u] = low[u] = ++stime;
	S.push(u); inS[u] = true;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		blockcnt++;
		int cur;
		do {
			cur = S.top(); S.pop(); inS[cur] = false;
			belong[cur] = blockcnt;
		} while (cur != u);
	}
}


int dagin[MaxN], dagout[MaxN];
void shrink() {
	for (int u = 1; u <= n; u++) {
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (belong[u] != belong[v]) {
				addedge(belong[u], belong[v], hdag);
				dagout[belong[u]]++;
				dagin[belong[v]]++;
			}
		}
	}
}




int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		int x;
		while (read(x) != 0)
			addedge(x, i);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}
	shrink();

	int in0 = 0, out0 = 0;
	for (int i = 1; i <= blockcnt; i++) {
		if (dagin[i] == 0)
			in0++;
		if (dagout[i] == 0)
			out0++;
	}

	printf("%d\n%d\n", out0, blockcnt == 1 ? 0 : max(in0, out0));

	return 0;
}

#endif

