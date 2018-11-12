/*
DOCUMENT NAME "20180826-luogup3690.cpp"
CREATION DATE 2018-08-26
SIGNATURE CODE_20180826_LUOGUP3690
COMMENT ��ģ�塿Link Cut Tree ����̬����
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180826_LUOGUP3690

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 3e5 + 10;

template<typename IntType = int>   // ģ��Ĭ��������ҪC++11
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
template<typename IntType, typename... Args>     // ģ���������ҪC++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;

struct node {
	node* lson, *rson, *father;
	bool lazy;
	int val, xorsum, id;
};

node* nodes[MaxN];
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

typedef int sontype;
const sontype lson = 0, rson = 1, none = 2;
node*& getson(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
sontype tellwhich(node* son) {
	if (son->father == nullptr)
		return none;
	else if (son->father->lson == son)
		return lson;
	else if (son->father->rson == son)
		return rson;
	else
		return none;
}
void connect(node* father, node* son, sontype type) {
	if (father != nullptr)
		getson(father, type) = son;
	if (son != nullptr)
		son->father = father;
}

bool notroot(node* p) {
	return p->father != nullptr && (p->father->lson == p || p->father->rson == p);
}

void update(node* p) {
	p->xorsum = p->val;
	if (p->lson != nullptr)
		p->xorsum ^= p->lson->xorsum;
	if (p->rson != nullptr)
		p->xorsum ^= p->rson->xorsum;
}

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
	if (findroot(y) != x || y->lson != x || x->rson != nullptr)
		return;
	y->lson = x->father = nullptr;
	update(y);
}

void changeval(node* p, int val) {
	access(p);
	splay(p);
	p->val = val;
	update(p);
}



int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++) {
		nodes[i] = ALLOCATE;
		nodes[i]->id = i;
		nodes[i]->val = nodes[i]->xorsum = read();
	}

	int k, x, y;
	for (int i = 1; i <= m; i++) {
		read(k, x, y);
		if (k == 0)
			cout << split(nodes[x], nodes[y])->xorsum << endl;
		else if (k == 1)
			link(nodes[x], nodes[y]);
		else if (k == 2)
			cut(nodes[x], nodes[y]);
		else if (k == 3)
			changeval(nodes[x], y);
	}

	return 0;
}

#endif
