/*
 DOCUMENT NAME "20181027-luogu3690.cpp"
 CREATION DATE 2018-10-27
 SIGNATURE CODE_20181027_LUOGU3690
 COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181027_LUOGU3690

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 3e5 + 10;

struct node {
	int val, sum;
	bool lazy;
	node* lson, *rson;
	node* father;
};
node* nodes[MaxN];
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

typedef unsigned char sontype;
const sontype lson = 0, rson = 1;
sontype tell(node* son) { return son->father->lson == son ? lson : rson; }
node*& get(node* father, sontype type) { return type == lson ? p->lson : p->rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}

void update(node* p) {
	p->sum = p->val;
	if (p->lson)
		p->sum ^= p->lson->sum;
	if (p->rson)
		p->sum ^= p->rson->sum;
}

bool notroot(node* p) {
	return p->father && (p->father->lson == p || p->father->rson == p);
}

void rotate(node* p) {
	sontype t = tell(p);
	node* f = p->father, *b = get(p, 1 - t);
	if (notroot(f))
		connect(f->father, p, tell(f));
	else
		p->father = f->father;
	connect(p, f, 1 - t);
	connect(p, b, t);
	update(f);
	update(p);
}

void pushdown(node* p) {
	if (p->lazy) {
		swap(p->lson, p->rson);
		if (p->lson)
			p->lson->lazy = !p->lson->lazy;
		if (p->rson)
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
			if (tell(p) == tell(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}

void access(node* p) {
	node* prev = 0;
	while (p) {
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
	while (p->lson) {
		p = p->lson;
		pushdown(p);
	}
	return p;
}





int main(int argc, char* argv[]) {

	return 0;
}

#endif

