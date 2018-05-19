/*
DOCUMENT CODE "20180514-bnds0587.cpp"
CREATION DATE 2018-05-14
SIGNATURE CODE_20180514_BNDS0587
TOPIC test 20180514
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180514_BNDS0587

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

int topId;
int getId() { return ++topId; }


struct node {
	int v;
	node* next;
};

node pool[31000000];
node* h[50000];
int top;

node* allocate() { return &pool[++top]; }

void addedge(int u, int v) {
	node* tmp = allocate();
	tmp->v = v;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = allocate();
	tmp->v = u;
	tmp->next = h[v];
	h[v] = tmp;
}


int clubId[1000], studentId[60000];
int n, m;

queue<int> Q;
bool flag[50000], been[50000];

void spfaX() {
	Q.push(1);
	flag[1] = true;
	been[1] = true;
	while (!Q.empty()) {
		int u = Q.front(), v;
		Q.pop(); flag[u] = false;
		for (node* p = h[u]; p != NULL; p = p->next) {
			v = p->v;
			if (!been[v]) {
				been[v] = true;
				if (!flag[v]) {
					flag[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {

	int k, a;

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		studentId[i] = getId();
	for (int i = 1; i <= m; i++)
		clubId[i] = getId();

	for (int i = 1; i <= m; i++) {
		cin >> k;
		for (int j = 1; j <= k; j++) {
			cin >> a;
			a++;
			addedge(clubId[i], studentId[a]);
		}
	}

	spfaX();

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (been[studentId[i]])
			ans++;
	}

	cout << ans << endl;

	return 0;
}

#endif

