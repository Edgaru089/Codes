/*
DOCUMENT NAME "20180630-luogu1608.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU1608
COMMENT 路径统计 / SPFA最短路计数
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU1608

#include <cstdlib>
#include <iostream>
using namespace std;

const int infinity = 1e8;
const int MaxN = 2000 + 10, MaxM = 4000000 + 10;

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

template<typename Type, int Size = 26214400>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

struct node {
	int v;
	int len;
	node* next;
};
node mem[2 * MaxM], *h[MaxN];
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
bool flag[MaxN][MaxN];

queue<int> Q;
bool inQ[MaxN];
int dis[MaxN];
int ansS[MaxN];
void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	dis[1] = 0;
	Q.push(1);
	inQ[1] = true;
	ansS[1] = 1;
	while (!Q.empty()) {
		int u = Q.front(), v;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				ansS[v] = ansS[u];
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
			else if (dis[v] == dis[u] + len)
				ansS[v] = ansS[v] + ansS[u];
		}
	}
}


int ansD;
void dfs(int u) {
	if (u == n)
		ansD++;
	else if (dis[u] >= dis[n])
		return;
	else
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] == dis[u] + len && dis[v] <= dis[n])
				dfs(v);
		}
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= m; i++) {
		read(u); read(v); read(len);
		if (!flag[u][v]) {
			addedge(u, v, len);
			flag[u][v] = true;
		}
	}

	spfa();
	dfs(1);

	if (ansS[n] == 0)
		printf("No answer\n");
	else
		printf("%d %d\n", dis[n], ansD);

	return 0;
}

#endif

