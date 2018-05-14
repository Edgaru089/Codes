/*
DOCUMENT CODE "20180511-luogu1346.cpp"
CREATION DATE 2018-05-11
SIGNATURE CODE_20180511_LUOGU1346
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180511_LUOGU1346

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

const int infinity = 1000000000;

struct node {
	int v, len;
	node* next;
};

int n, s, t;
int point[1001];
node pool[10001], *h[1001];
int top;

void addedge(int u, int v, int len) {
	node* p = &pool[++top];
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}

queue<int> Q;
int S[30000], D[30000];

void spfa() {
	for (int i = 1; i <= n; i++) {
		S[i] = 0;
		D[i] = infinity;
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

	cin >> n >> s >> t;

	int k;
	for (int i = 1; i <= n; i++) {
		cin >> k;
		int v;
		for (int j = 1; j <= k; j++) {
			cin >> v;
			if (j == 1)
				addedge(i, v, 0);
			else
				addedge(i, v, 1);
		}
	}

	spfa();

	if (D[t] >= infinity)
		cout << -1 << endl;
	else
		cout << D[t] << endl;

	return 0;
}

#endif

