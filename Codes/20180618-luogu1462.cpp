/*
DOCUMENT CODE "20180618-luogu1462.cpp"
CREATION DATE 2018-06-18
SIGNATURE CODE_20180618_LUOGU1462
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180618_LUOGU1462

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

const int infinity = 1000000000;

struct node {
	int v, len;
	node* next;
};

node pool[100001], *h[10001];
int top;

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

int n, m, b;
int f[10001];
int u, v, len;

queue<int> Q;
bool inQ[10001];
int dis[10001];

bool spfacheck(int maxCost) {
	for (int i = 1; i <= n; i++) {
		inQ[i] = false;
		dis[i] = infinity;
	}
	while (!Q.empty())
		Q.pop();
	dis[1] = 0;
	Q.push(1);
	inQ[1] = true;

	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (f[v] <= maxCost && dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}

	if (dis[n] <= b)
		return true;
	else
		return false;

}

int main(int argc, char* argv[]) {

	cin >> n >> m >> b;
	for (int i = 1; i <= n; i++)
		cin >> f[i];

	int l, r;

	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> len;
		addedge(u, v, len);
		r = max(r, len);
	}
	l = max(f[1], f[n]);

	// SPFA1 Damage
	// Damage check
	if (!spfacheck(1000000001)) {
		cout << "AFK" << endl;
		return 0;
	}

	// SPFA2 Cost
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (spfacheck(mid))
			r = mid;
		else
			l = mid;
	}

	if (spfacheck(l))
		cout << l << endl;
	else
		cout << r << endl;

	return 0;
}

#endif

