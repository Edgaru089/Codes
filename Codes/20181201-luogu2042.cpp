/*
 DOCUMENT NAME "20181201-luogu2042.cpp"
 CREATION DATE 2018-12-01
 SIGNATURE CODE_20181201_LUOGU2042
 COMMENT [NOI2005] Î¬»¤ÊýÁÐ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181201_LUOGU2042

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int infinity = 1e8;
const int MaxN = 4000000 + 10, MaxM = 20000 + 10;

int n, m;
int d[MaxN];

struct node {
	int val, max, sum;
	int size;
	int lazyset;
	bool lazyswap;
	node* lson, *rson;
	node* father;
};

node* overroot;
#define ROOT (overroot->lson)
node mem[MaxN], *memtop = mem;

stack<node*> gc;

node* allocate() {
	node* p;
	if (!gc.empty()) {
		p = gc.top();
		gc.pop();
		memset(p, 0, sizeof(node));
	} else
		p = ++memtop;
	p->lazyset = -infinity;
	return p;
}

void recycle(node* p) {
	gc.push(p);
}

int ssize(node* p) {
	if (p)
		return p->size;
	else
		return 0;
}

int ssum(node* p) {
	if (p)
		return p->sum;
	else
		return 0;
}

int smax(node* p) {
	if (p)
		return p->max;
	else
		return 0;
}

void update(node* p) {
	if (p) {
		p->sum = p->val + ssize(p->lson) + ssize(p->rson);
		p->max = max(0, p->val);
		p->max = max(p->max, smax(p->lson));
		p->max = max(p->max, smax(p->rson));
		p->max = max(p->max, smax(p->lson) + p->val);
		p->max = max(p->max, smax(p->rson) + p->val);
		p->max = max(p->max, smax(p->lson) + smax(p->rson));
		p->max = max(p->max, smax(p->lson) + p->val + smax(p->rson));
		p->size = ssize(p->lson) + ssize(p->rson) + 1;
	}
}

void pushdown(node* p) {
	if (p->lazyset != -infinity) {
		p->val = p->lazyset;
		if (p->lson)
			p->lson->lazyset = p->lazyset;
		if (p->rson)
			p->rson->lazyset = p->lazyset;
		p->lazyset = -infinity;
	}
	if (p->lazyswap) {
		swap(p->lson, p->rson);
		if (p->lson)
			p->lson->lazyswap = !p->lson->lazyswap;
		if (p->rson)
			p->rson->lazyswap = !p->rson->lazyswap;
		p->lazyswap = false;
	}
}

typedef unsigned char sontype;
const sontype lson = 0, rson = 1;
sontype tell(node* p) { return p->father&&p->father->lson == p ? lson : rson; }
node*& get(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}

void rotate(node* p) {
	sontype t = tell(p);
	node* fa = p->father, *b = get(p, 1 - t);
	connect(p, fa->father, tell(fa));
	connect(fa, p, 1 - t);
	connect(b, p, t);
	update(fa);
	update(p);
}

void pushchain(node* p, node* target) {
	if (p->father != target)
		pushchain(p->father, target);
	pushdown(p);
}

void splay(node* p, node* target) {
	pushchain(p, target);
	while (p->father != target) {
		if (p->father->father != target)
			if (tell(p) == tell(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}


void build(int left = 1, int right = n, node*& p = ROOT) {
	if (left < right)
		return;
	int mid = (left + right) / 2;
	p = allocate();
	p->val = d[mid];
	build(left, mid - 1, p->lson);
	build(mid + 1, right, p->rson);
	update(p);
}

node* getkth(int k, node* p = ROOT) {
	pushdown(p);
	if (ssize(p->lson) >= k)
		return getkth(k, p->lson);
	else if (k == ssize(p->lson) + 1)
		return p;
	else
		return getkth(k - ssize(p->lson) - 1, p->rson);
}







int main(int argc, char* argv[]) {






	return 0;
}

#endif

