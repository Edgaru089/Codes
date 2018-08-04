/*
DOCUMENT NAME "20180716-luogu3371.cpp"
CREATION DATE 2018-07-16
SIGNATURE CODE_20180716_LUOGU3371
COMMENT 【模板】单源最短路径 / 堆优化Dijstra
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180716_LUOGU3371

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

const int infinity = 2147483647;
const int MaxN = 100000 + 10, MaxM = 500000 + 10;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

int n, m;
int s;
int dis[MaxN];

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

namespace dijstra {
	typedef pair<int, int> pii;
	priority_queue<pii, vector<pii>, greater<pii>> Q;
	bool been[MaxN];
	void run() {
		for (int i = 1; i <= n; i++)
			dis[i] = infinity;
		Q.push(make_pair(0, s));
		dis[s] = 0;
		while (!Q.empty()) {
			pii t = Q.top(); Q.pop();
			int u = t.second, d = t.first;
			if (been[u])
				continue;
			been[u] = true;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (dis[v] > dis[u] + len) {
					dis[v] = dis[u] + len;
					Q.push(make_pair(d + len, v));
				}
			}
		}
	}
}

namespace spfa {
	queue<int> Q;
	bool inQ[MaxN];
	void run() {
		for (int i = 1; i <= n; i++)
			dis[i] = infinity;
		dis[s] = 0;
		Q.push(s);
		inQ[s] = true;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop(); inQ[u] = false;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
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
}

int main(int argc, char* argv[]) {

	read(n, m, s);
	int u, v, l;
	for (int i = 1; i <= m; i++) {
		read(u, v, l);
		addedge(u, v, l);
	}

	dijstra::run();
	//spfa::run();

	for (int i = 1; i <= n; i++) {
		if (i != 1)
			printf(" %d", dis[i]);
		else
			printf("%d", dis[i]);
	}
	printf("\n");

	return 0;
}

#endif

