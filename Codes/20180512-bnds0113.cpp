/*
DOCUMENT CODE "20180512-bnds0113.cpp"
CREATION DATE 2018-05-12
SIGNATURE CODE_20180512_BNDS0113
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180512_BNDS0113

#include <cstdlib>
#include <iostream>
#include <queue>
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
}

int n, m, s, e;
int u, v, len;

queue<int> Q;
int S[30000], D[30000];

const int infinity = 1000000000;

void spfa() {
	for (int i = 1; i <= n; i++) {
		S[i] = 0;
		D[i] = infinity;
	}
	Q.push(1);
	S[1] = 1;
	D[1] = 0;
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

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> len;
		addedge(u, v, len);
	}

	spfa();
	

	for (int i = 2; i <= n; i++) {
		if (i > 2)
			cout << ' ';
		if (D[i] < infinity)
			cout << D[i];
		else
			cout << -32767;
	}
	cout << endl;

	return 0;
}

#endif

