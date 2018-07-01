/*
DOCUMENT NAME "20180629-luogu1038.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1038
COMMENT Éñ¾­ÍøÂç / Ï¹¸ã
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1038

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MaxN = 100 + 10, MaxM = 100 + 10;

int n, m;

struct node {
	int v;
	int w;
	node* next;
};

node pool[2 * MaxM], *top = pool, *h[MaxN], *rev[MaxN];
#define ALLOCATE (++top)

void addedge(int u, int v, int w) {
	node* p = ALLOCATE;
	p->v = v;
	p->w = w;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->w = w;
	p->next = rev[v];
	rev[v] = p;
}

int c[MaxN], u[MaxN];

int dep[MaxN];
vector<int> layer[MaxN];
int layerCnt;

queue<int> Q;
void layerize() {
	for (int i : layer[1]) {
		Q.push(i);
		dep[i] = 1;
	}
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (dep[v] == 0) {
				dep[v] = dep[u] + 1;
				Q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (dep[i] != 1) {
			layer[dep[i]].push_back(i);
			layerCnt = max(layerCnt, dep[i]);
		}
	}
}

void update() {
	for (int i = 2; i <= layerCnt; i++) {
		for (int u : layer[i]) {
			c[u] = -::u[u];
			for (node* p = rev[u]; p != nullptr; p = p->next) {
				if (c[p->v] > 0)
					c[u] += c[p->v] * p->w;
			}
		}
	}
}


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> c[i] >> u[i];

	layerCnt = 1;
	for (int i = 1; i <= n; i++) {
		if (c[i] != 0)
			layer[1].push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		addedge(u, v, w);
	}

	layerize();
	update();

	bool f = true;
	for (int i : layer[layerCnt])
		if (c[i] > 0) {
			printf("%d %d\n", i, c[i]);
			f = false;
		}
	if (f)
		printf("NULL\n");

	return 0;
}

#endif

