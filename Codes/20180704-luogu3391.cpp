/*
DOCUMENT NAME "20180704-luogu3391.cpp"
CREATION DATE 2018-07-04
SIGNATURE CODE_20180704_LUOGU3391
COMMENT 【模板】文艺平衡树（Splay） / Splay
*/

/* 你需要资瓷一个「区间翻转」的操作 */

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180704_LUOGU3391

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

const int MaxN = 100000 + 10;

int read() {
	char c;
	int val = 0;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

int read(int& x) { return x = read(); }

struct node {
	int val, id;
	bool lazy; // reverse
	int size;
	node* lson, *rson;
	node* father;
};

node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

node *overroot;
#define ROOT (overroot->lson)

typedef int Type;
const int Left = 0, Right = 1;

int size(node* p) { return (p == nullptr) ? 0 : p->size; }
void update(node* p) {
	if (p == nullptr)
		return;
	p->size = size(p->lson) + size(p->rson) + 1;
}

node*& getson(node* p, Type type) {
	return (type == Left) ? p->lson : p->rson;
}

// <son> must have a father
Type sontype(node* son) {
	if (son == son->father->lson)
		return Left;
	else
		return Right;
}

void connect(node* son, node* father, Type sontype) {
	getson(father, sontype) = son;
	if (son != nullptr)
		son->father = father;
}

void pushdown(node* p) {
	if (p == nullptr)
		return;
	if (p->lazy) {
		swap(p->lson, p->rson);
		if (p->lson != nullptr)
			p->lson->lazy = !p->lson->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = !p->rson->lazy;
		p->lazy = false;
	}
}

// <p> must at least have a father
void rotateup(node* p) {
	Type t = sontype(p), fatype = sontype(p->father);
	node* fa = p->father, *grand = fa->father;
	node* b = getson(p, 1 - t);
	pushdown(fa);
	pushdown(p);
	if (grand != nullptr)
		connect(p, grand, fatype);
	connect(fa, p, 1 - t);
	connect(b, fa, t);
	update(fa);
	update(p);
}

// rotates <p> up until <p> is the son of <target>
void splay(node* p, node* target) {
	while (p->father != target && p->father->father != target) {
		//node* fa = p->father, *grand = p->father->father;
		if (sontype(p) == sontype(p->father))
			rotateup(p->father);
		else
			rotateup(p);
		rotateup(p);
		//if (grand->father == fa) {
		//	update(grand);
		//	update(fa);
		//	update(p);
		//}
		//else {
		//	update(fa);
		//	update(grand);
		//	update(p);
		//}
	}
	if (p->father->father == target) {
		//node* fa = p->father;
		rotateup(p);
		//update(fa);
		//update(p);
	}
}

void _build(int d[], int left, int right, node*& p, node* fa) {
	if (left > right)
		return;
	int mid = (left + right) / 2;

	p = ALLOCATE;
	p->father = fa;
	p->val = d[mid];
	p->id = mid - 1;

	_build(d, left, mid - 1, p->lson, p);
	_build(d, mid + 1, right, p->rson, p);
	update(p);
}

void build(int d[], int n) {
	overroot = ALLOCATE;
	overroot->val = -1; overroot->id = -1;
	_build(d, 1, n, overroot->lson, overroot);
	update(overroot);
}

node* findkth(int k, node* p = ROOT) {
	pushdown(p);
	if (size(p->lson) >= k)
		return findkth(k, p->lson);
	else if (size(p->lson) + 1 == k)
		return p;
	else if (size(p->lson) + 1 < k)
		return findkth(k - size(p->lson) - 1, p->rson);
	else
		return nullptr;
}

void reverse(int left, int right) {
	if (left > right)
		swap(left, right);
	node* lower = findkth(left), *upper = findkth(right + 2);
	splay(lower, overroot);
	splay(upper, lower);
	if (upper->lson != nullptr)
		upper->lson->lazy = !upper->lson->lazy;
}

void iterate(vector<int>& vec, node* p) {
	if (p == nullptr)
		return;
	pushdown(p);
	iterate(vec, p->lson);
	if (p->val != -1)
		vec.push_back(p->val);
	iterate(vec, p->rson);
}


int n, m;
int l, r;
vector<int> d;

int main(int argc, char* argv[]) {

	read(n); read(m);
	d.reserve(n + 3);
	d.push_back(-1);
	d.push_back(-1);
	for (int i = 1; i <= n; i++)
		d.push_back(i);
	d.push_back(-1);
	build(d.data(), n + 2);

	for (int i = 1; i <= m; i++) {
		read(l); read(r);
		reverse(l, r);
	}

	d.clear();
	iterate(d, ROOT);
	printf("%d", d[0]);
	for (int i = 1; i < d.size(); i++)
		printf(" %d", d[i]);
	printf("\n");

	return 0;
}

#endif

