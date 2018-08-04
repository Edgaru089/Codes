/*
DOCUMENT NAME "20180803-luoguU34195.cpp"
CREATION DATE 2018-08-03
SIGNATURE CODE_20180803_LUOGUU34195
COMMENT 紫的贸易 标程 / 网络流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180803_LUOGUU34195

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 20000 + 10, MaxM = 1600000 + 10;

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

constexpr int MaxN0 = 100 + 10, MaxT = 100 + 10, MaxK = 100 + 10;

int t0, k, n0;
vector<int> h0[MaxK];
int c[MaxT][MaxK];
int b[MaxT][MaxN0], s0[MaxT][MaxN0];

int village(int time, int id) { return (time - 1)*n0 + id; }
int carryin(int time, int id) { return t0 * n0 + (time - 1)*k + id; }
int carryout(int time, int id) { return t0 * n0 + t0 * k + (time - 1)*k + id; }

int main(int argc, char* argv[]) {

	cin >> t0 >> k >> n0;
	for (int i = 1; i <= k; i++) {
		int cnt, x;
		cin >> cnt;
		for (int j = 1; j <= cnt; j++) {
			cin >> x;
			h0[i].push_back(x);
		}
	}
	for (int i = 1; i <= t0; i++)
		for (int j = 1; j <= k; j++)
			cin >> c[i][j];
	for (int i = 1; i <= t0; i++)
		for (int j = 1; j <= n0; j++)
			cin >> b[i][j] >> s0[i][j];

	s = t0 * n0 + t0 * k + t0 * k + 1;
	t = s + 1;
	n = t;

	// 第一天没有可售卖的东西
	for (int i = 2; i <= t0; i++) {
		for (int j = 1; j <= n0; j++) {
			addedge(village(i, j), t, b[i][j]);                       // 售卖
			addedge(village(i - 1, j), village(i, j), s0[i - 1][j]);  // 仓库
		}
		for (int j = 1; j <= k; j++) {                                // 罪袋
			addedge(carryin(i, j), carryout(i, j), c[i - 1][j]);
			for (int v : h0[j]) {
				if (v == 0)
					addedge(s, carryin(i, j), infinity);
				else {
					addedge(village(i - 1, v), carryin(i, j), infinity);
					addedge(carryout(i, j), village(i, v), infinity);
				}
			}
		}
	}

	cout << dinic() << endl;


	return 0;
}

#endif

