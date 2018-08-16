/*
DOCUMENT NAME "20180815-bnds0780.cpp"
CREATION DATE 2018-08-15
SIGNATURE CODE_20180815_BNDS0780
COMMENT C. 2018-8-15模拟测验（三）-美丽的中国结 / 裸的dfs序
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180815_BNDS0780

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 100000 + 10;

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
char read<char>() {
	int c;
	while (isspace(c = getchar()) || iscntrl(c));
	return c;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

//#define DEBUG(...) printf(__VA_ARGS__)
#define DEBUG(...)


int n, m;

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

int sstime;
int dfn[MaxN], fa[MaxN], ssize[MaxN];
void dfs(int u, int from) {
	DEBUG("dfs from %d to %d\n", from, u);
	fa[u] = from;
	dfn[u] = ++sstime;
	ssize[u] = 1;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs(v, u);
			ssize[u] += ssize[v];
		}
	}
}

namespace segtree {
	struct node {
		bool lazy;
		int sum;
		int left, right;
		node* lson, *rson;
	};

	node* root;
	node mem[4 * MaxN], *memtop = mem;

	void build(int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->sum = 0;
		else {
			int mid = (left + right) / 2;
			build(left, mid, p->lson);
			build(mid + 1, right, p->rson);
			p->sum = 0;
		}
	}

	void pushdown(node* p) {
		if (p == nullptr || !p->lazy)
			return;
		p->sum = (p->right - p->left + 1) - p->sum;
		if (p->lson != nullptr)
			p->lson->lazy = !p->lson->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = !p->rson->lazy;
		p->lazy = false;
	}

	void flip(int left, int right, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazy = !p->lazy;
			return;
		}
		if (p->lson->right >= right)
			flip(left, right, p->lson);
		else if (p->rson->left <= left)
			flip(left, right, p->rson);
		else {
			flip(left, p->lson->right, p->lson);
			flip(p->rson->left, right, p->rson);
		}
		pushdown(p);
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}

	int query(int left, int right, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right)
			return p->sum;
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return (query(left, p->lson->right, p->lson) +
					query(p->rson->left, right, p->rson));
	}
}

void change(int x) {
	segtree::flip(dfn[x], dfn[x] + ssize[x] - 1);
}

int query(int x) {
	return segtree::query(dfn[x], dfn[x] + ssize[x] - 1);
}


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());
	dfs(1, 0);
	segtree::build();
	char c;
	int x;
	read(m);
	for (int i = 1; i <= m; i++) {
		read(c, x);
		if (c == 'C')
			change(x);
		else if (c == 'Q')
			printf("%d\n", query(x));
	}

	return 0;
}

#endif

