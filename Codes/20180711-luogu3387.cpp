/*
DOCUMENT NAME "20180711-luogu3387.cpp"
CREATION DATE 2018-07-11
SIGNATURE CODE_20180711_LUOGU3387
COMMENT ¡¾Ä£°å¡¿Ëõµã
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180711_LUOGU3387

#include <cstdlib>
#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 1e4 + 10, MaxM = 1e5 + 10;

int n, m;
int weight[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, node** h = ::h) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}


stack<int> S;
bool inS[MaxN];
int dfn[MaxN], stime, low[MaxN];
int blockcnt, belong[MaxN];
int blockweight[MaxN];
vector<int> blocks[MaxN];
void dfs(int u) {
	dfn[u] = ++stime;
	low[u] = stime;
	S.push(u);
	inS[u] = true;
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
		int cnt;
		do {
			cnt = S.top(); S.pop();
			inS[cnt] = false;
			blocks[blockcnt].push_back(cnt);
			blockweight[blockcnt] += weight[cnt];
			belong[cnt] = blockcnt;
		} while (cnt != u);
	}
}


node* dag[MaxN];
void shrink() {
	for (int u = 1; u <= n; u++) {
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (belong[u] != belong[v])
				addedge(belong[u], belong[v], dag);
		}
	}
}

int ans[MaxN];
int search(int u) {
	if (ans[u] != -1)
		return ans[u];
	else {
		ans[u] = 0;
		for (node* p = dag[u]; p != nullptr; p = p->next) {
			int v = p->v;
			ans[u] = max(ans[u], search(v));
		}
		ans[u] += blockweight[u];
		return ans[u];
	}
}



int main(int argc, char* argv[]) {

	memset(ans, -1, sizeof(ans));

	cin >> n >> m;
	int u, v, w;
	for (int i = 1; i <= n; i++)
		cin >> weight[i];
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			dfs(i);
	shrink();

	int ans = 0;
	for (int i = 1; i <= blockcnt; i++) {
		ans = max(ans, search(i));
	}

	cout << ans << endl;

	return 0;
}

#endif

