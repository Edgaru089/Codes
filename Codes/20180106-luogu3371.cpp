/*
DOCUMENT CODE "20180106-luogu3371.cpp"
CREATION DATE 2018-01-06
SIGNATURE CODE_20180106_LUOGU3371
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180106_LUOGU3371

#include <cstdlib>
#include <iostream>
#include <queue>
#include <climits>
#include <list>
using namespace std;

struct node {
	int v, len;
	node* next;
};

node pool[500001], *h[10001];
int top;

int n, m, s;

int len[10001];
bool inq[10001];
queue<int> Q;

void addedge(int u, int v, int len) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
}



int main(int argc, char* argv[]) {

	int u, v, l;

	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> l;
		addedge(u, v, l);
	}

	for (int i = 1; i <= n; i++)
		len[i] = INT_MAX;
	len[s] = 0;
	Q.push(s);
	inq[s] = true;

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		for (node* p = h[u]; p != NULL; p = p->next) {
			int v = p->v, l = p->len;
			if (len[u] + l < len[v]) {
				len[v] = len[u] + l;
				if (!inq[v]) {
					inq[v] = true;
					Q.push(v);
				}
			}
		}
	}

	cout << len[1];
	for (int i = 2; i <= n; i++)
		cout << " " << len[i];
	cout << endl;

	return 0;
}

#endif

