/*
 DOCUMENT NAME "20181010-luogu3690.cpp"
 CREATION DATE 2018-10-10
 SIGNATURE CODE_20181010_LUOGU3690
 COMMENT ��ģ�塿Link Cut Tree����̬����
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181010_LUOGU3690

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

const int MaxN = 3e5;

void read(int& val) {
	val = 0;
	int c;
	bool inv = false;;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

int n, m;
int k, x, y;

struct node {
	node* lson, *rson, *father;
	int val, sum;
	bool lazy;
};

node nodes[MaxN];

typedef int sontype;
const sontype lson = 0, rson = 1;
node*& get(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
sontype tell(node* son) { return son->father->lson == son ? lson : rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}

bool notroot(node* p) {
	return p->father && (p->father->lson == p || p->father->rson == p);
}

void update(node* p) {
	p->sum = p->val;
	if (p->lson)
		p->sum ^= p->lson->sum;
	if (p->rson)
		p->sum ^= p->rson->sum;
}

void rotate(node* p) {
	sontype t = tell(p);
	node* f = p->father, *b = get(p, 1 - t);
	if (notroot(f))
		connect(f->father, p, tell(f));
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

void makeroot(node* p) {
	access(p);
	splay(p);
	p->lazy = !p->lazy;
}

void link(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x)
		x->father = y;
}

void cut(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x || y->lson != x || x->rson)
		return;
	y->lson = x->father = 0;
	update(y);
}

node* split(node* x, node* y) {
	makeroot(x);
	access(y);
	splay(y);
	return y;
}

void changeval(node* p, int val) {
	access(p);
	splay(p);
	p->val = val;
	update(p);
}




int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(k);
		nodes[i].val = nodes[i].sum = k;
	}

	for (int i = 1; i <= m; i++) {
		read(k); read(x); read(y);
		switch (k) {
			case 0:
				printf("%d\n", split(nodes + x, nodes + y)->sum);
				break;
			case 1:
				link(nodes + x, nodes + y);
				break;
			case 2:
				cut(nodes + x, nodes + y);
				break;
			case 3:
				changeval(nodes + x, y);
				break;
		}
	}

	return 0;
}

#endif
