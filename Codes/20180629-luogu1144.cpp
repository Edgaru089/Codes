/*
DOCUMENT NAME "20180629-luogu1144.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1144
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1144

#include <cstdlib>
#include <iostream>
using namespace std;

const int infinity = 1e8;
const int MaxN = 1000000 + 10, MaxM = 2000000 + 10, Mod = 100003;

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
	node* next;
};
node mem[2 * MaxM], *h[MaxN];
int top;
node* allocate() { return &mem[++top]; }

void addedge(int u, int v) {
	node* p = allocate();
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = allocate();
	p->v = u;
	p->next = h[v];
	h[v] = p;
}

int n, m;
int u, v;

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
			v = p->v;
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				ansS[v] = ansS[u] % Mod;
				//if (!inQ[v]) {
					//inQ[v] = true;
				Q.push(v);
			//}
			}
			else if (dis[v] == dis[u] + 1)
				ansS[v] = (ansS[v] + ansS[u]) % Mod;
		}
	}
}


int ansD[MaxN];
void dfs(int u) {
	ansD[u]++;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dis[v] == dis[u] + 1)
			dfs(v);
	}
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= m; i++) {
		read(u); read(v);
		addedge(u, v);
	}

	spfa();
	//dfs(1);

	for (int i = 1; i <= n; i++) {
		printf("%d\n", ansS[i]);
	}

	return 0;
}

#endif

