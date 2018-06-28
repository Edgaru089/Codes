/*
DOCUMENT CODE "20180626-bnds0615.cpp"
CREATION DATE 2018-06-26
SIGNATURE CODE_20180626_BNDS0615
TOPIC
*/

/*
INPUT
5 4
1 5 4
1 2 2
2 5 2
4 1 1
OUTPUT
4 2
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180626_BNDS0615

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

int read() {
	char c;
	int val = 0;

	while (!isdigit(c = getchar()));

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	return val;
}

int read(int& val) {
	return val = read();
}

int edge[2000 + 10][2000 + 10];

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

int n, m;
int u, v, len;

queue<int> Q;
bool inQ[2000 + 10];
int dis[2000 + 10];

void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = 1000000000;
	dis[1] = 0;
	Q.push(1);
	inQ[1] = true;
	while (!Q.empty()) {
		int u = Q.front(), v, len;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int ans[2000 + 10];
void dfs(int u) {
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v, len = p->len;
		if (dis[v] == dis[u] + len) {
			ans[v] += ans[u];
			dfs(v);
		}
	}
}

queue<int> Qb;
int ansX = 0;
void bfs() {
	Qb.push(1);
	while (!Qb.empty()) {
		int u = Qb.front(); Qb.pop();
		if (u == n)
			ansX++;
		else {
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (dis[v] == dis[u] + len) {
					Qb.push(v);
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			edge[i][j] = 1000000000;
		}
	}
	for (int i = 1; i <= m; i++) {
		read(u); read(v); read(len);
		edge[u][v] = min(edge[u][v], len);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (edge[i][j] != 1000000000)
				addedge(i, j, edge[i][j]);
		}
	}

	spfa();

	ans[1] = 1;
	//dfs(1);
	bfs();

	if (dis[n] == 1000000000)
		printf("No answer\n");
	else
		//printf("%d %d\n", dis[n], ans[n]);
		printf("%d %d\n", dis[n], ansX);

	return 0;
}

#endif

