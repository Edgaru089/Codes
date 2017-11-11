/*
DOCUMENT CODE "luogu2296.cpp"
CREATION DATE 2017-10-14
SIGNATURE CODE_20171014_LUOGU2296
TOPIC NOIP2014 Ñ°ÕÒµÀÂ·
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171014_LUOGU2296

#include <cstdlib>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
using namespace std;

struct node {
	int v;
	node* next;
};

typedef pair<int, int> IntPair;

node* h[10001], *hrev[10001];
node pool[800001];
int top;

int n, m;
int s, t;
bool hasBeen[10001], isOk[10001];

int step[10001];

queue<IntPair> Q;

void addedge(int u, int v) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = &pool[++top];
	tmp->v = u;
	tmp->next = hrev[v];
	hrev[v] = tmp;
}

void dfs(int u) {
	hasBeen[u] = true;
	for (node* p = hrev[u]; p != NULL; p = p->next) {
		int v = p->v;
		if (!hasBeen[v])
			dfs(v);
	}
}

void bfs(int u, int layer) {
	for (node* p = hrev[u]; p != NULL; p = p->next) {
		int v = p->v;
		if (isOk[v] && step[v] == -1) {
			step[v] = layer + 1;
			Q.push(IntPair(v, layer + 1));
		}
	}
}

int main(int argc, char* argv[]) {
	cin >> n >> m;
	int u, v;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		addedge(u, v);
	}
	cin >> s >> t;

	dfs(t);

	memset(isOk, -1, sizeof(isOk));

	for (int i = 1; i <= n; i++) {
		if (!hasBeen[i]) {
			for (node* j = hrev[i]; j != NULL; j = j->next)
				isOk[j->v] = false;
		}
	}

	memset(step, -1, sizeof(step));
	step[t] = 0;
	Q.push(IntPair(t, 0));
	while (!Q.empty()) {
		IntPair p = Q.front();
		Q.pop();
		bfs(p.first, p.second);
	}

	cout << step[s] << endl;


	return 0;
}

#endif
