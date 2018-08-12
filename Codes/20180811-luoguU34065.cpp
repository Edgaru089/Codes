/*
DOCUMENT NAME "20180811-luoguU34065.cpp"
CREATION DATE 2018-08-11
SIGNATURE CODE_20180811_LUOGUU34065
COMMENT 難題「仏の御石の鉢　-砕けぬ意思-」
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180811_LUOGUU34065

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MaxN = 100000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;
int a[MaxN];
int ans[MaxN];

struct node {
	int v;
	node* next;
};
node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

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


void dfs(int u, int from) {
	ans[u] = a[u];
	for (node* p = h[u]; p != nullptr; p = p->next) {
		if (p->v != from) {
			dfs(p->v, u);
			ans[u] = max(ans[u], ans[p->v]);
		}
	}
}


int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());

	dfs(1, 0);

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[read()]);

	return 0;
}

#endif

