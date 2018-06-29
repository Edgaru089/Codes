/*
DOCUMENT NAME "20180629-luogu1576.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1576
COMMENT 最小花费 / SPFA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1576

#include <cstdlib>
#include <iostream>
using namespace std;

const int infinity = 1e9;
const int MaxN = 2000 + 10, MaxM = 100000;

int n, m, a, b;

struct node {
	int v;
	double factor;
	node* next;
};

node mem[2 * MaxM], *top = mem, *h[MaxN];
#define ALLOCATE (top++);

void addedge(int from, int to, int factor) {
	node* p = ALLOCATE;
	p->v = to;
	p->factor = 100.0 / (100.0 - factor);
	p->next = h[from];
	h[from] = p;
	p = ALLOCATE;
	p->v = from;
	p->factor = 100.0 / (100.0 - factor);
	p->next = h[to];
	h[to] = p;
}

template<typename Type, int Size = 20 * MaxN>
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
bool inQ[MaxN];
double dis[MaxN];
void spfa() {
	Q.clear();
	for (int i = 1; i <= n; i++) {
		dis[i] = infinity;
		inQ[i] = false;
	}
	dis[b] = 100;
	Q.push(b);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); inQ[u] = false;
		int v; double factor;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; factor = p->factor;
			if (dis[v] > dis[u] * factor) {
				dis[v] = dis[u] * factor;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		addedge(x, y, z);
	}
	cin >> a >> b;

	spfa();

	printf("%.8lf\n", dis[a]);

	return 0;
}

#endif

