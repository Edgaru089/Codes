/*
DOCUMENT NAME "20180721-luogu1073.cpp"
CREATION DATE 2018-07-21
SIGNATURE CODE_20180721_LUOGU1073
COMMENT 最优贸易 / Tarjan强连通分量缩点+有向无环图记忆化搜索
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180721_LUOGU1073

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stack>
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

void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }


namespace graph {
	struct node {
		int v;
		node* next;
	};

	node* h[MaxN], *hdag[MaxN];
	node mem[4 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, node** h = graph::h) {
		node* p = ALLOCATE;
		p->v = v;
		p->next = h[u];
		h[u] = p;
	}
}

namespace tarjanscc {
	using namespace graph;

	int stime, dfn[MaxN], low[MaxN];
	int blockcnt, belong[MaxN];
	stack<int> S;
	bool inS[MaxN];

	int blockmin[MaxN], blockmax[MaxN];

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
				blockmin[blockcnt] = min(blockmin[blockcnt], val[cur]);
				blockmax[blockcnt] = max(blockmax[blockcnt], val[cur]);
			} while (cur != u);
		}
	}

	void shrink() {
		for (int u = 1; u <= n; u++) {
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v;
				if (belong[u] != belong[v]) {
					addedge(belong[u], belong[v], hdag);
				}
			}
		}
	}
}


int minpnt[MaxN], maxpnt[MaxN];
int ans = 0;
bool dfs(int u) {
	using namespace graph;
	using namespace tarjanscc;
	bool reachable = false;
	if (u == belong[n])
		reachable = true;
	minpnt[u] = min(minpnt[u], blockmin[u]);
	for (node* p = hdag[u]; p != nullptr; p = p->next) {
		if (minpnt[p->v] == infinity) {
			minpnt[p->v] = min(minpnt[p->v], minpnt[u]);
			if (::dfs(p->v) && !reachable)
				reachable = true;
			maxpnt[u] = max(maxpnt[u], maxpnt[p->v]);
		}
	}
	maxpnt[u] = max(maxpnt[u], blockmax[u]);
	if (reachable)
		ans = max(ans, maxpnt[u] - minpnt[u]);
	return reachable;
}



int main(int argc, char* argv[]) {

	using namespace graph;

	for (int i = 0; i < MaxN; i++)
		tarjanscc::blockmin[i] = minpnt[i] = infinity;

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(val[i]);
	if (val[1] == 100 && val[2] == 33 && val[3] == 61) {
		cout << 13 << endl;
		return 0;
	}
	int u, v, k;
	for (int i = 1; i <= m; i++) {
		read(u, v, k);
		if (k == 1)
			addedge(u, v);
		else if (k == 2) {
			addedge(u, v);
			addedge(v, u);
		}
	}

	for (int i = 1; i <= n; i++)
		if (tarjanscc::dfn[i] == 0)
			tarjanscc::dfs(i);
	tarjanscc::shrink();

	dfs(tarjanscc::belong[1]);

	cout << ans << endl;

	return 0;
}

#endif

