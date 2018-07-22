/*
DOCUMENT NAME "20180722-luogu1608.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU1608
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU1608

#include <cstdlib>
#include <iostream>
#include <queue>
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
class _queue {
public:
	_queue() { clear(); }
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
int ansD;

namespace spfa {
	_queue<int> Q;
	bool inQ[MaxN];
	int dis[MaxN];
	int ansS[MaxN];
	void run() {
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
}


namespace heapdijkstra {
	struct st {
		int u;
		int dis;
	};
	struct stcompare {
		bool operator ()(const st& x, const st& y) {
			return x.dis > y.dis;
		}
	};
	priority_queue<st, vector<st>, stcompare> Q;
	int dis[MaxN];
	int cnt = 0;
	void run() {
		for (int i = 1; i <= n; i++)
			dis[i] = 1e8;
		Q.push(st{ 1, 0 });
		dis[1] = 0;
		while (!Q.empty()) {
			int u = Q.top().u, dis = Q.top().dis;
			Q.pop();
			if (heapdijkstra::dis[u] < dis)
				continue;
			heapdijkstra::dis[u] = dis;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (heapdijkstra::dis[v] > dis + len) {
					heapdijkstra::dis[v] = dis + len;
					Q.push(st{ v, dis + len });
				}
			}
		}
	}
}


using namespace heapdijkstra;

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

	run();
	dfs(1);

	if (dis[n] == infinity)
		printf("No answer\n");
	else
		printf("%d %d\n", dis[n], ansD);

	return 0;
}

#endif

