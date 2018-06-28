/*
DOCUMENT CODE "20180625-bnds0615.cpp"
CREATION DATE 2018-06-25
SIGNATURE CODE_20180625_BNDS0615
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180625_BNDS0615

#include <cstdlib>
#include <iostream>
using namespace std;

struct node {
	int v, len;
	node* next;
};

node mem[2000 * 2000], *h[2000 + 10];
int top;
node* allocate() { return &mem[++top]; }
void addedge(int u, int v, int len) {
	node* p = allocate();
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}

int n, e;
int u, v, len;

int dis[2000 + 10], cnt[2000 + 10];

void dfs(int u = 1, int dep = 0) {
	if (dis[u] < dep)
		return;
	if (dis[u] == dep)
		cnt[u]++;
	else if (dis[u] > dep) {
		dis[u] = dep;
		cnt[u] = 1;
	}
	for (node* p = h[u]; p != nullptr; p = p->next)
		dfs(p->v, dep + p->len);
}

int main(int argc, char* argv[]) {

	cin >> n >> e;
	for (int i = 1; i <= e; i++) {
		cin >> u >> v >> len;
		addedge(u, v, len);
	}

	for (int i = 1; i <= n; i++)
		dis[i] = 1000000000;

	dfs();

	if (dis[n] == 1000000000)
		cout << "No answer" << endl;
	else
		cout << dis[n] << " " << cnt[n] << endl;

	return 0;
}

#endif

