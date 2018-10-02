/*
 DOCUMENT NAME "20180909-luogu3690.cpp"
 CREATION DATE 2018-09-09
 SIGNATURE CODE_20180909_LUOGU3690
 COMMENT P3690 ¡¾Ä£°å¡¿Link Cut Tree£¨¶¯Ì¬Ê÷£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180909_LUOGU3690

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 7e5 + 10, MaxM = 7e5 + 10;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = getchar()));
	do { ans = (ans << 1) + (ans << 3) + c - '0'; } while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return ans;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;

struct node {
	node* lson, *rson;
	node* father;
	int val, xorsum;
	bool lazy;
};

node* nodes[MaxN];
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

typedef int sontype;
constexpr sontype lson = 0, rson = 1, lightson = 2;
constexpr sontype tellwhich(node* son) {
	if (son->father == nullptr)
		return lightson;
	else if (son->father->lson == son)
		return lson;
	else if (son->father->rson == son)
		return rson;
	else
		return lightson;
}
node*& getson(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father != nullptr)
		getson(father, type) = son;
	if (son != nullptr)
		son->father = father;
}

bool notroot(node* p) { return p->father != nullptr && (p->father->lson == p || p->father->rson == p); }

void update(node* p) {
	p->xorsum = p->val;
	if (p->lson != nullptr)
		p->xorsum ^= p->lson->xorsum;
	if (p->rson != nullptr)
		p->xorsum ^= p->rson->xorsum;
}

void rotate(node* p) {
	sontype t = tellwhich(p);
	node* f = p->father, *b = getson(p, 1 - t);
	if (notroot(f))
		connect(f->father, p, tellwhich(f));
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

void link(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x)
		x->father = y;
}

void cut(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x || y->lson != x || x->rson != nullptr)
		return;
	y->lson = x->father = nullptr;
}

node* split(node* x, node* y) {
	makeroot(x);
	access(y);
	splay(y);
	return y;
}

void changepnt(node* p, int val) {
	access(p);
	splay(p);
	p->val = val;
	update(p);
}

int k, x, y;

int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++) {
		node* p = nodes[i] = ALLOCATE;
		p->val = p->xorsum = read();
	}
	for (int i = 1; i <= m; i++) {
		read(k, x, y);
		if (k == 0)
			printf("%d\n", split(nodes[x], nodes[y])->xorsum);
		else if (k == 1)
			link(nodes[x], nodes[y]);
		else if (k == 2)
			cut(nodes[x], nodes[y]);
		else if (k == 3)
			changepnt(nodes[x], y);
	}

	return 0;
}

#endif

