/*
DOCUMENT CODE "20180617-luogu1294.cpp"
CREATION DATE 2018-06-17
SIGNATURE CODE_20180617_LUOGU1294
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180617_LUOGU1294

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int v, len;
	node* next;
};

int n, m;
int u, v, len;
node pool[10000], *h[100];
int top = 0;

bool been[10001];
int ans = 0;

void addedge(int u, int v, int len) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = &pool[++top];
	tmp->v = u;
	tmp->len = len;
	tmp->next = h[v];
	h[v] = tmp;
}

void dfs(int u, int dep) {
	been[u] = true;
	ans = max(ans, dep);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v, len = p->len;
		if (!been[v])
			dfs(v, dep + len);
	}
	been[u] = false;
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> len;
		addedge(u, v, len);
	}

	for (int i = 1; i <= n; i++)
		dfs(i, 0);

	cout << ans << endl;

	return 0;
}

#endif

