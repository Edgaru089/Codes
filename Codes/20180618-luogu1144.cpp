/*
DOCUMENT CODE "20180618-luogu1144.cpp"
CREATION DATE 2018-06-18
SIGNATURE CODE_20180618_LUOGU1144
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180618_LUOGU1144

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int infinity = 1000000000;

struct node {
	int v, len;
	node* next;
};

node pool[1000001], *h[4000001];
int top;

void addedge(int u, int v) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->len = 1;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = &pool[++top];
	tmp->v = u;
	tmp->len = 1;
	tmp->next = h[v];
	h[v] = tmp;
}

int n, m;
int u, v;

int cnt[1000001];
bool inQ[1000001];
bool been[1000001];
int dep[1000001];
queue<int> Q;

int bfs() {
	been[1] = inQ[1] = true;
	cnt[1] = 1;
	dep[1] = 0;
	Q.push(1);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (!been[v]) {
				been[v] = true;
				Q.push(v); inQ[v] = true;
				dep[v] = dep[u] + 1;
				cnt[v] = cnt[u];
			}
			else if (dep[v] == dep[u] + 1) {
				cnt[v] += cnt[u];
			}
		}
	}
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		addedge(u, v);
	}

	bfs();

	for (int i = 1; i <= n; i++)
		cout << cnt[i] << endl;

	return 0;
}

#endif

