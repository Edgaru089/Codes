/*
DOCUMENT NAME "20180630-luogu3701.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU3701
COMMENT 「伪模板」主席树 / 最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU3701

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

const int infinity = 1e8;
const int MaxN = 1000 + 10, MaxM = 2 * MaxN * MaxN;

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

int n, m;
int root;
int s, t;
int u, v, flow;

#define IN(x)  (x)
#define OUT(x) (x + n)

struct node {
	int v, flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[MaxM], *top = mem;
#define ALLOCATE (++top)

void addedge(int u, int v, int flow) {
	if (flow == 0)
		return;
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h[u];
	h[u] = p;
	node* pr = ALLOCATE;
	pr->v = u;
	pr->flow = 0;
	pr->next = h[v];
	h[v] = pr;
	p->rev = pr;
	pr->rev = p;
}


template<typename Type, int Size = MaxN>
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

queue<int> Q;
int dep[MaxN];
bool bfs() {
	memset(dep, 0, sizeof(dep));
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow;
			if (flow != 0) {
				if (dep[v] == 0) {
					dep[v] = dep[u] + 1;
					Q.push(v);
				}
			}
		}
	}
	if (dep[t] == 0)
		return false;
	else
		return true;
}

int dfs(int u, int limit) {
	if (limit == 0 || u == t)
		return limit;
	int f, ans = 0;
	for (node* p = h[u]; p != nullptr && limit > 0; p = p->next) {
		v = p->v; flow = p->flow;
		if (dep[v] == dep[u] + 1 && (f = dfs(v, min(flow, limit))) != 0) {
			limit -= f;
			p->flow -= f;
			p->rev->flow += f;
			ans += f;
		}
	}
	return ans;
}

int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


struct player {
	string name;
	int life;
};

int n0, m0;
player byx[MaxN], shouq[MaxN];
#define BYX(x)    (x)
#define SHOUQ(x)  (x + n0)
int xubyx, xushouq;

int main(int argc, char* argv[]) {

	cin >> n0 >> m0;
	for (int i = 1; i <= n0; i++)
		cin >> byx[i].name;
	for (int i = 1; i <= n0; i++)
		cin >> shouq[i].name;
	for (int i = 1; i <= n0; i++)
		cin >> byx[i].life;
	for (int i = 1; i <= n0; i++)
		cin >> shouq[i].life;

	int s0 = 2 * n0 + 1;
	s = 2 * n0 + 2; t = 2 * n0 + 3;
	n = 2 * n0 + 3;
	addedge(s, s0, m0);
	for (int i = 1; i <= n0; i++) {
		if (byx[i].name == "YYY")
			xubyx++;
		if (shouq[i].name == "YYY")
			xushouq++;
	}
	for (int i = 1; i <= n0; i++) {
		addedge(s0, BYX(i), (byx[i].name == "J") ? byx[i].life + xubyx : byx[i].life);
		addedge(SHOUQ(i), t, (shouq[i].name == "J") ? shouq[i].life + xushouq : shouq[i].life);
		for (int j = 1; j <= n0; j++) {
			string& byxn = byx[i].name, &shouqn = shouq[j].name;
			if (byxn == "W")
				if (shouqn == "YYY" || shouqn == "E")
					addedge(BYX(i), SHOUQ(j), 1);
			if (byxn == "J")
				if (shouqn == "W" || shouqn == "HK")
					addedge(BYX(i), SHOUQ(j), 1);
			if (byxn == "E")
				if (shouqn == "J" || shouqn == "YYY")
					addedge(BYX(i), SHOUQ(j), 1);
			if (byxn == "YYY")
				if (shouqn == "HK" || shouqn == "J")
					addedge(BYX(i), SHOUQ(j), 1);
			if (byxn == "HK")
				if (shouqn == "W" || shouqn == "E")
					addedge(BYX(i), SHOUQ(j), 1);
		}
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

