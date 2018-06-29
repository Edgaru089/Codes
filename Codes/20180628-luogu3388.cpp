/*
DOCUMENT NAME "20180628-luogu3388.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3388
COMMENT ¡¾Ä£°å¡¿¸îµã£¨¸î¶¥£© / Tarjan
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3388

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 100000 + 10, MaxM = 100000 + 10;

int min(int x, int y) { return x < y ? x : y; }

int read() {
	char c;
	int val = 0;
	bool minus = false;

	while (!isdigit(c = getchar()))
		if (c == '-')
			minus = true;

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	if (minus)
		return -val;
	else
		return val;
}

int read(int& val) {
	return val = read();
}

int n, m;

struct node {
	int v;
	node* next;
};

int top;
node mem[2 * MaxM], *h[MaxN];
#define ALLOCATE (&mem[++top])

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}


template<typename Type, int Size = MaxN>
class stack {
public:
	stack() :mtop(0) {}
	void clear() { mtop = 0; }
	void push(Type val) { arr[++mtop] = val; }
	void pop() { mtop--; }
	Type top() { return arr[mtop]; }
private:
	int mtop;
	Type arr[Size];
};

stack<int> S;
bool inS[MaxN];
int mtime = 0;
int dfn[MaxN], low[MaxN];
bool isCut[MaxN];

void dfs(int u, int from = 0) {
	S.push(u); inS[u] = true;
	dfn[u] = low[u] = ++mtime;

	int subtreeCnt = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && from != 0)
				isCut[u] = true;
			if (from == 0) // is root --> count subtree
				subtreeCnt++;
		}
		low[u] = min(low[u], dfn[v]);
	}

	if (subtreeCnt >= 2 && from == 0)
		isCut[u] = true;

}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		read(u); read(v);
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			dfs(i);

	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (isCut[i])
			cnt++;
	printf("%d\n", cnt);
	bool flag = true;
	for (int i = 1; i <= n; i++)
		if (isCut[i]) {
			if (flag)
				flag = false;
			else
				printf(" ");
			printf("%d", i);
		}

	return 0;
}

#endif

