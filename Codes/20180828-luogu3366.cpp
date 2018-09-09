/*
DOCUMENT NAME "20180828-luogu3366.cpp"
CREATION DATE 2018-08-28
SIGNATURE CODE_20180828_LUOGU3366
COMMENT 【模板】最小生成树 / LCT动态加边
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180828_LUOGU3366

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

const int MaxN = 1e4 + 10, MaxM = 2e5 + 10;

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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

struct node {
	node* lson, *rson, *father;
	int val, id;
	int maxval;
	node* maxfrom;
	bool lazy;
};

node* nodes[MaxN];
node* nodeedges[MaxM];
node mem[2 * (MaxN + MaxM)], *memtop = mem;
#define ALLOCATE (memtop++)

typedef int sontype;
const sontype lson = 0, rson = 1, lightson = 2;
node*& getson(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
sontype tellwhich(node* son) {
	if (son->father == nullptr)
		return lightson;
	else if (son->father->lson == son)
		return lson;
	else if (son->father->rson == son)
		return rson;
	else
		return lightson;
}
void connect(node* father, node* son, sontype type) {
	if (father != nullptr)
		getson(father, type) = son;
	if (son != nullptr)
		son->father = father;
}

void update(node* p) {
	p->maxval = p->val;
	p->maxfrom = p;
	if (p->lson != nullptr)
		if (p->lson->maxval > p->maxval) {
			p->maxval = p->lson->maxval;
			p->maxfrom = p->lson->maxfrom;
		}
	if (p->rson != nullptr)
		if (p->rson->maxval > p->maxval) {
			p->maxval = p->rson->maxval;
			p->maxfrom = p->rson->maxfrom;
		}
}

bool notroot(node* p) { return p->father != nullptr && (p->father->lson == p || p->father->rson == p); }

void rotate(node* p) {
	sontype t = tellwhich(p);
	node* f = p->father, *gf = p->father->father, *b = getson(p, 1 - t);
	if (notroot(f))
		connect(gf, p, tellwhich(f));
	else
		p->father = f->father;
	connect(p, f, 1 - t);
	connect(f, b, t);
	update(f);
	update(p);
}

void pushdown(node* p) {
	if (p->lazy) {
		swap(p->lson, p->rson);
		if (p->lson != nullptr)
			p->lson->lazy = !p->lson->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = !p->rson->lazy;
		p->lazy = false;
	}
}

void pushchain(node* p) {
	if (notroot(p))
		pushchain(p->father);
	pushdown(p);
}

void splay(node* p) {
	pushchain(p);
	while (notroot(p)) {
		if (notroot(p->father))
			if (tellwhich(p) == tellwhich(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}

void access(node* p) {
	node* prev = nullptr;
	while (p != nullptr) {
		splay(p);
		p->rson = prev;
		update(p);
		prev = p;
		p = p->father;
	}
}

void makeroot(node* p) {
	access(p);
	splay(p);
	p->lazy = !p->lazy;
}

node* findroot(node* p) {
	access(p);
	splay(p);
	pushdown(p);
	while (p->lson != nullptr) {
		p = p->lson;
		pushdown(p);
	}
	return p;
}

node* split(node* x, node* y) {
	makeroot(x);
	access(y);
	splay(y);
	return y;
}

void link(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x)
		x->father = y;
}

void cut(node* x, node* y) {
	makeroot(x);
	access(y);
	splay(y);
	x->father = y->lson = nullptr;
	update(y);
}


void cutedge(node* e) {
	splay(e);
	node* l = e->lson, *r = e->rson;
	assert(l != nullptr);
	assert(r != nullptr);
	while (l->rson != nullptr)
		l = l->rson;
	while (r->lson != nullptr)
		r = r->lson;
	cut(l, e);
	cut(r, e);
}

int ans;
void addedge(int id, int u, int v, int len) {
	node* e = nodeedges[id] = ALLOCATE;
	e->maxval = e->val = len;
	e->id = -id;
	node* p = nodes[u], *q = nodes[v];
	makeroot(p);
	if (findroot(q) != p) {
		link(p, e);
		link(q, e);
		ans += len;
	}
	else {
		node* s = split(p, q);
		if (s->maxval > len) {
			node* from = s->maxfrom;
			ans = ans - s->maxval + len;
			cutedge(from);
			link(p, e);
			link(q, e);
		} // Else: do nothing (skip edge)
	}
}

int n, m;
int u, v, len;

int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++) {
		nodes[i] = ALLOCATE;
		nodes[i]->id = i;
	}
	for (int i = 1; i <= m; i++) {
		read(u, v, len);
		addedge(i, u, v, len);
	}

	printf("%d\n", ans);

	return 0;
}

#endif

