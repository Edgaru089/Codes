/*
DOCUMENT NAME "20180629-luogu2832.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU2832
COMMENT 行路难 / 魔改SPFA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU2832

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

const int infinity = 1e8;
const int MaxN = 10000 + 10, MaxM = 200000 + 10;

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
	int v, len;
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
int u, v;

struct que {
	que() {}
	que(int u, vector<int>& been) :u(u), been(&been) {}
	int u;
	vector<int>* been;
};

queue<que> Q;
bool inQ[MaxN];
int dis[MaxN];
vector<int> ans[MaxN];
void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	dis[1] = 0;
	ans[1] = { 1 };
	Q.push(que(1, ans[1]));
	inQ[1] = true;
	while (!Q.empty()) {
		que q = Q.front();
		int u = q.u, v, len;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len + q.been->size() - 1) {
				dis[v] = dis[u] + len + q.been->size() - 1;
				ans[v] = *q.been;
				ans[v].push_back(v);
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(que(v, ans[v]));
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, len;
		cin >> u >> v >> len;
		addedge(u, v, len);
	}

	spfa();

	cout << dis[n] << endl;
	for (int i = 0; i < ans[n].size(); i++)
		if (i == 0)
			cout << ans[n][i];
		else
			cout << " " << ans[n][i];
	cout << endl;


	return 0;
}

#endif

