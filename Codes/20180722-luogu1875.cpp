/*
DOCUMENT NAME "20180722-luogu1875.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU1875
COMMENT ¼Ñ¼ÑµÄÄ§·¨Ò©Ë®
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU1875

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 1000 + 1 + 10, MaxM = 2 * MaxN;

int n, m;
int price;


struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}


queue<int> Q;
int start;
int dis[MaxN], discnt[MaxN];
void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(start);
	dis[start] = 0;
	discnt[start] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				discnt[v] = discnt[u];
				Q.push(v);
			}
			else if (dis[v] == dis[u] + len)
				discnt[v] += discnt[u];
		}
	}
}


int main(int argc, char* argv[]) {

	return 0;
}

#endif

