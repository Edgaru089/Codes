/*
DOCUMENT NAME "20180824-luogu3960.cpp"
CREATION DATE 2018-08-24
SIGNATURE CODE_20180824_LUOGU3960
COMMENT 【模板】Link Cut Tree （动态树）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180824_LUOGU3960

#include <cstdlib>
#include <iostream>
#include <exception>
using namespace std;

const int MaxN = 3e5 + 10;

//template<typename IntType = int>   // 模板默认类型需要C++11
//IntType read() {
//	IntType val = 0;
//	int c;
//	bool invflag = false;
//	while (!isdigit(c = getchar()))
//		if (c == '-')
//			invflag = true;
//	do {
//		val = (val << 1) + (val << 3) + c - '0';
//	} while (isdigit(c = getchar()));
//	ungetc(c, stdin);
//	if (invflag)
//		return -val;
//	else
//		return val;
//}
//template<>
//string read<string>() {
//	string str;
//	str.clear();
//	int c;
//	while (iscntrl(c = getchar()) || isblank(c));
//	do {
//		str.push_back(c);
//	} while (!(iscntrl(c = getchar()) || isblank(c)));
//	ungetc(c, stdin);
//	return str;
//}
//template<typename IntType>
//void read(IntType& x) { x = read<IntType>(); }
//template<typename IntType, typename... Args>     // 模板参数包需要C++11
//void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

constexpr int buffersize = 40 * 1024 * 1024;    // 40M的缓冲区
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)
template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }


int n, m;


struct node {
	node* father;
	node* lson, *rson;
	bool lazyflip;
	int id;
	int val;
	int xorsum;
};

node* nodes[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

typedef int sontype;
const sontype lson = 0, rson = 1;
node*& getson(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father != nullptr)
		getson(father, type) = son;
	if (son != nullptr)
		son->father = father;
}
sontype tellwhich(node* father, node* son) {
	if (father->lson == son)
		return lson;
	else if (father->rson == son)
		return rson;
	throw runtime_error("tellwhich error: unmatched father and son nodes");
}

bool notroot(node* p) {
	return p->father != nullptr && (p->father->lson == p || p->father->rson == p);
}

void pushdown(node* p) {
	if (p != nullptr&&p->lazyflip) {
		swap(p->lson, p->rson);
		if (p->lson != nullptr)
			p->lson->lazyflip = !p->lson->lazyflip;
		if (p->rson != nullptr)
			p->rson->lazyflip = !p->rson->lazyflip;
		p->lazyflip = false;
	}
}

void update(node* p) {
	if (p == nullptr)
		return;
	p->xorsum = (p->lson == nullptr ? 0 : p->lson->xorsum) ^ (p->rson == nullptr ? 0 : p->rson->xorsum) ^ p->val;
}

void rotate(node* p) {
	if (p->father != nullptr)
		pushdown(p->father->father);
	pushdown(p->father);
	pushdown(p);
	sontype t = tellwhich(p->father, p);
	node* f = p->father, *gf = p->father->father, *b = getson(p, 1 - t);
	if (notroot(f))
		connect(gf, p, tellwhich(gf, f));
	else
		p->father = f->father;
	connect(p, f, 1 - t);
	connect(f, b, t);
	update(f);
	update(p);
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
			if (tellwhich(p->father, p) == tellwhich(p->father->father, p->father))
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
	p->lazyflip = !p->lazyflip;
}

node* findroot(node* p) {
	access(p);
	splay(p);
	for (;;) {
		pushdown(p);
		if (p->lson != nullptr)
			p = p->lson;
		else
			break;
	}
	return p;
}

node* split(node* left, node* right) {
	makeroot(left);
	access(right);
	splay(right);
	return right;
}

// x(father) --> y(son), light
void link(node* x, node* y) {
	makeroot(y);
	if (findroot(x) != y)
		y->father = x;
}

bool cut(node* x, node* y) {
	makeroot(x);
	if (findroot(y) != x || x->father != y || x->rson != nullptr)
		return false;
	y->lson = x->father = nullptr;
	update(y);
	return true;
}

void changeval(node* p, int val) {
	makeroot(p);
	p->val = val;
	update(p);
}




int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	int k, x, y;
	read(n, m);
	for (int i = 1; i <= n; i++) {
		nodes[i] = ALLOCATE;
		nodes[i]->val = read();
		nodes[i]->id = i;
		update(nodes[i]);
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
			changeval(nodes[x], y);
	}


	return 0;
}

#endif

