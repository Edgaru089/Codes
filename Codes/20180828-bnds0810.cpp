/*
DOCUMENT NAME "20180828-bnds0810.cpp"
CREATION DATE 2018-08-28
SIGNATURE CODE_20180828_BNDS0810
COMMENT B. 2018-8-28noip模拟测验（二）-球的序列
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180828_BNDS0810

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

const int MaxN = 50000 + 10;

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
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
int a[MaxN], b[MaxN];
int aid[MaxN], bid[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[10 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

int indeg[MaxN];

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;

	indeg[v]++;
}

int nodes[MaxN], nodestop = 0;
bool sorted[MaxN];

void sortnode(int u) {
	assert(indeg[u] == 0);
	nodes[++nodestop] = u;
	sorted[u] = true;
	for (node* p = h[u]; p != nullptr; p = p->next)
		indeg[p->v]--;
	for (node* p = h[u]; p != nullptr; p = p->next)
		if (indeg[p->v] == 0)
			sortnode(p->v);
}

int ans[MaxN];
void updateans(int u) {
	int maxans = 0;
	for (node* p = h[u]; p != nullptr; p = p->next)
		maxans = max(maxans, ans[p->v]);
	ans[u] = maxans + 1;
}



int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		aid[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		read(b[i]);
		bid[b[i]] = i;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (aid[i] < aid[j] && bid[i] < bid[j])
				addedge(i, j);
		}
	}

	for (int i = 1; i <= n; i++)
		if (indeg[i] == 0 && !sorted[i])
			sortnode(i);

	assert(nodestop == n);

	int maxans = 0;
	for (int i = nodestop; i >= 1; i--) {
		updateans(i);
		maxans = max(maxans, ans[i]);
	}

	printf("%d\n", maxans);

	return 0;
}

#endif

