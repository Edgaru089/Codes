/*
DOCUMENT NAME "20180722-luogu2763.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_LUOGU2763
COMMENT 试题库问题 / 网络流Dinic
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_LUOGU2763

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int MaxK = 20 + 5;


#pragma region Dinic
constexpr int infinity = 1e8;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }


int n, m;
int s, t;

struct node {
	int v, flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int flow) {
	node* p1 = ALLOCATE;
	p1->v = v;
	p1->flow = flow;
	p1->next = h[u];
	h[u] = p1;
	node* p2 = ALLOCATE;
	p2->v = u;
	p2->flow = 0;
	p2->next = h[v];
	h[v] = p2;
	p1->rev = p2;
	p2->rev = p1;
}

int dis[MaxN];

queue<int> Q;
bool bfs() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(s);
	dis[s] = 0;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, flow = p->flow;
			if (flow > 0)
				if (dis[v] == infinity) {
					dis[v] = dis[u] + 1;
					Q.push(v);
				}
		}
	}
	if (dis[t] == infinity)
		return false;
	else
		return true;
}

int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int val = 0;
	for (node* p = h[u]; p != nullptr&&limit > 0; p = p->next) {
		int v = p->v, f;
		int& flow = p->flow;
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
			flow -= f;
			p->rev->flow += f;
			limit -= f;
			val += f;
		}
	}
	return val;
}

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}
#pragma endregion

int k, n0;
int target, x;
vector<int> targets[MaxK];

int probtypeid(int pntid) {
	return pntid - n0;
}

int pntid(int probtypeid) {
	return probtypeid + n0;
}

int main(int argc, char* argv[]) {

	read(k, n0);
	n = k + n0 + 2;
	s = k + n0 + 1;
	t = k + n0 + 2;
	for (int i = 1; i <= k; i++) {
		read(x);
		target += x;
		addedge(pntid(i), t, x);
	}
	for (int i = 1; i <= n0; i++) {
		addedge(s, i, 1);
		read(x);
		for (int j = 1; j <= x; j++)
			addedge(i, pntid(read()), 1);
	}

	if (dinic() < target)
		cout << "No Solution!" << endl;
	else {
		for (int i = 1; i <= n0; i++)
			for (node* p = h[i]; p != nullptr; p = p->next) {
				if (p->flow == 0) {
					targets[probtypeid(p->v)].push_back(i);
					break;
				}
			}
		for (int i = 1; i <= k; i++) {
			cout << i << ":";
			for (int j : targets[i])
				cout << " " << j;
			cout << endl;
		}
	}

	return 0;
}

#endif

