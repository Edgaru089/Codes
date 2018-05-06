/*
DOCUMENT CODE "20180505-luogu1339.cpp"
CREATION DATE 2018-05-05
SIGNATURE CODE_20180505_LUOGU1339
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180505_LUOGU1339

#include <cstdlib>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct node {
	int v, len;
	node* next;
};

node pool[70000], *h[30000];
int top;

node* alloc() { return &pool[++top]; }

void addedge(int u, int v, int len) {
	node* tmp = alloc();
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = alloc();
	tmp->v = u;
	tmp->len = len;
	tmp->next = h[v];
	h[v] = tmp;
}

int n, m, s, e;
int u, v, len;

queue<int> Q;
int S[30000], D[30000];

void spfa() {
	for (int i = 1; i <= n; i++) {
		S[i] = 0;
		D[i] = INT_MAX;
	}
	Q.push(s);
	S[s] = 1;
	D[s] = 0;
	while (!Q.empty()) {
		int u = Q.front(), v, len;
		Q.pop(); S[u] = 0;
		for (node* p = h[u]; p != NULL; p = p->next) {
			v = p->v;
			len = p->len;
			if (D[v] > D[u] + len) {
				D[v] = D[u] + len;
				if (S[v] == 0) {
					S[v] = 1;
					Q.push(v);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {

	cin >> n >> m >> s >> e;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> len;
		addedge(u, v, len);
	}

	spfa();
	cout << D[e] << endl;

	return 0;
}

#endif

