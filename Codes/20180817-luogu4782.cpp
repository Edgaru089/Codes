/*
DOCUMENT NAME "20180817-luogu4782.cpp"
CREATION DATE 2018-08-17
SIGNATURE CODE_20180817_LUOGU4782
COMMENT °æƒ£∞Â°ø2-SAT Œ Ã‚
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180817_LUOGU4782

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int MaxN = 1e6 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[4 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[v];
	h[v] = p;
}

template<typename Type, int Size = MaxN>
class stack {
public:
	stack() :stacktop(0) {}
	void clear() { stacktop = 0; }
	void push(Type x) { arr[stacktop++] = x; }
	void pop() { if (stacktop > 0) stacktop--; }
	Type top() { return arr[stacktop - 1]; }
	bool empty() { return stacktop <= 0; }
	int size() { return stacktop; }
private:
	int stacktop;
	Type arr[Size];
};

stack<int> S;
bool inS[MaxN];
int dfn[MaxN], sstime, low[MaxN];
int belong[MaxN], blockcnt;
void dfs(int u) {
	dfn[u] = low[u] = ++sstime;
	inS[u] = true;
	S.push(u);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int cur;
		blockcnt++;
		do {
			cur = S.top();
			S.pop(); inS[cur] = false;
			belong[cur] = blockcnt;
		} while (cur != u);
	}
}


void tarjan() {
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			dfs(i);
}


int n0, m0;
int i, j, a, b;

int pid(int id, int state) {
	return 2 * id - state;
}

int main(int argc, char* argv[]) {

	read(n0, m0);
	n = n0 * 2;
	for (int i = 1; i <= m0; i++) {
		read(i, a, j, b);
		addedge(pid(i, 1 - a), pid(j, b));
		addedge(pid(j, 1 - b), pid(i, a));
	}

	tarjan();

	bool ok = true;
	for (int i = 1; i <= n0 && ok; i++)
		if (belong[pid(i, 0)] == belong[pid(i, 1)])
			ok = false;
	if (!ok)
		puts("IMPOSSIBLE\n");
	else {
		printf("POSSIBLE\n");
		for (int i = 1; i <= n0; i++)
			printf("%d ", dfn[pid(i, 0)] < dfn[pid(i, 1)]);
	}

	return 0;
}

#endif

