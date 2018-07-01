/*
DOCUMENT NAME "20180629-luogu1137.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1137
COMMENT 旅行计划 / 记忆化搜索
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1137

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10, MaxM = 200000 + 10;

int n, m;

struct node {
	int v;
	node* next;
};

node mem[MaxM], *top = mem, *h[MaxN];
#define ALLOCATE (++top)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}

int ans[MaxN];
int dfs(int u) {
	if (ans[u] > 0)
		return ans[u];
	else {
		ans[u] = 1;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			ans[u] = max(ans[u], dfs(p->v) + 1);
		}
		return ans[u];
	}
}

int main(int argc, char* argv[]) {

	memset(ans, -1, sizeof(ans));

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addedge(v, u);
	}

	for (int i = 1; i <= n; i++)
		cout << dfs(i) << endl;

	return 0;
}

#endif

