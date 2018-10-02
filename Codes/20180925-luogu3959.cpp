/*
 DOCUMENT NAME "20180925-luogu3959.cpp"
 CREATION DATE 2018-09-25
 SIGNATURE CODE_20180925_LUOGU3959
 COMMENT NOIP2017D2T2 БІВи
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180925_LUOGU3959

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 12 + 1, MaxM = 1000 + 10, MaxV = 500000 + 10;

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

int n, m;
int u, v, l;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

int rans = infinity;

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}

int s, dis[MaxN], ans[1 << (MaxN + 1)];
void dfs(int state) {
	for (int i = 1; i <= n; i++) {
		if ((state&(1 << (i - 1))) != 0) {
			int u = i;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (ans[state] > rans)
					return;
				int nstate = state | (1 << (v - 1));
				if (nstate != state && ans[nstate] > ans[state] + dis[u] * len) {
					ans[nstate] = ans[state] + dis[u] * len;
					int tmp = dis[v];
					dis[v] = dis[u] + 1;
					dfs(nstate);
					dis[v] = tmp;
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= m; i++) {
		read(u, v, l);
		addedge(u, v, l);
	}

	for (int i = 1; i <= n; i++) {
		s = i;
		for (int j = 0; j <= (1 << n) - 1; j++)
			ans[j] = infinity;
		dis[i] = 1;
		ans[1<<(i-1)] = 0;
		dfs(1 << (i - 1));
		rans = min(rans, ans[(1 << n) - 1]);
	}

	printf("%d\n", rans);

	return 0;
}

#endif

