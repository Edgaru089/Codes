/*
 DOCUMENT NAME "20180920-bnds0752.cpp"
 CREATION DATE 2018-09-20
 SIGNATURE CODE_20180920_BNDS0752
 COMMENT #752. [HEOI2016]树 / DFS+倒序处理操作+并查集
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180920_BNDS0752

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int MaxN = 1e6 + 10, MaxQ = 1e6 + 10;

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
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<>
char read<char>() {
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	return c;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, q;

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

int p[MaxN];
int setfind(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = setfind(p[x]);
}

void setunion(int x, int y) {
	x = setfind(x);
	y = setfind(y);
	if (x == y)
		return;
	p[x] += p[y];
	p[y] = x;
}

int markcnt[MaxN];
int father[MaxN];
void dfs(int u = 1, int top = 1, int from = 0) {
	father[u] = from;
	if (markcnt[u] > 0)
		top = u;
	else
		setunion(top, u);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs(v, top, u);
		}
	}
}

pair<char, int> ops[MaxQ];
int ans[MaxQ];

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	read(n, q);
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		read(u, v);
		addedge(u, v);
	}
	markcnt[1] = 1;
	for (int i = 1; i <= q; i++) {
		char c;
		int k;
		read(c, k);
		ops[i] = make_pair(c, k);
		if (c == 'C')
			markcnt[k]++;
	}

	dfs();

	for (int i = q; i >= 1; i--) {
		char c = ops[i].first;
		int k = ops[i].second;
		if (c == 'C') {
			markcnt[k]--;
			if (markcnt[k] == 0)
				setunion(father[k], k);
		}
		else {
			ans[i] = setfind(k);
		}
	}

	for (int i = 1; i <= q; i++)
		if (ops[i].first == 'Q')
			printf("%d\n", ans[i]);


	return 0;
}

#endif

