/*
DOCUMENT NAME "20180724-luogu3391.cpp"
CREATION DATE 2018-07-24
SIGNATURE CODE_20180724_LUOGU3391
COMMENT 【模板】文艺平衡树（Splay） / Splay
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180724_LUOGU3391

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MaxN = 100000 + 10;

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

int n, m;

struct node {
	int val;
	int size, lazy;
	node* lson, *rson;
	node* father;
};

node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)
node* overroot;
#define ROOT (overroot->lson)

typedef int type;
const type lson = 0, rson = 1;
type sontype(node* p) { return (p->father->lson == p) ? lson : rson; }
node*& son(node* p, type sontype) { return (sontype == lson) ? p->lson : p->rson; }

int size(node* p) { return (p == nullptr) ? 0 : p->size; }
void update(node* p) {
	p->size = 1 + size(p->lson) + size(p->rson);
}

void pushdown(node* p) {
	if (p == nullptr)
		return;
	if (p->lazy == 1) {
		swap(p->lson, p->rson);
		if (p->lson != nullptr)
			p->lson->lazy = 1 - p->lson->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = 1 - p->rson->lazy;
		p->lazy = 0;
	}
}

void connect(node* p, node* father, type connecttype) {
	if (father != nullptr)
		son(father, connecttype) = p;
	if (p != nullptr)
		p->father = father;
}

void rotate(node* p) {
	pushdown(p->father);
	pushdown(p);
	type t = sontype(p);
	node* b = son(p, 1 - t), *fa = p->father, *grandfa = p->father->father;
	if (grandfa != nullptr)
		connect(p, grandfa, sontype(fa));
	else
		p->father = nullptr;
	connect(fa, p, 1 - t);
	connect(b, fa, t);
	update(fa);
	update(p);
}

void splay(node* p, node* target) {
	while (p->father != target && p->father->father != target) {
		if (sontype(p) == sontype(p->father))
			rotate(p->father);
		else
			rotate(p);
		rotate(p);
	}
	if (p->father != target)
		rotate(p);
}

void _build(int d[], int left, int right, node*& p, node* fa) {
	if (left > right)
		return;
	int mid = (left + right) / 2;
	p = ALLOCATE;
	p->val = d[mid];
	p->father = fa;
	_build(d, left, mid - 1, p->lson, p);
	_build(d, mid + 1, right, p->rson, p);
	p->size = 1 + size(p->lson) + size(p->rson);
}

void build(int d[], int n) {
	overroot = ALLOCATE;
	overroot->val = d[0];
	_build(d, 1, n, ROOT, overroot);
	update(overroot);
}

node* getkth(int k, node* p = ROOT) {
	pushdown(p);
	if (k <= size(p->lson))
		return getkth(k, p->lson);
	else if (k == size(p->lson) + 1)
		return p;
	else if (k > size(p->lson) + 1)
		return getkth(k - (size(p->lson) + 1), p->rson);
}

void reverse(int left, int right) {
	if (left > right)
		swap(left, right);
	node* lp = getkth(left);
	node* rp = getkth(right + 2);
	splay(lp, overroot);
	splay(rp, lp);
	if (rp->lson != nullptr)
		rp->lson->lazy = 1 - rp->lson->lazy;
}

void print(node* p, vector<int>& ans) {
	if (p == nullptr)
		return;
	pushdown(p);
	print(p->lson, ans);
	if (p->val >= 0 && p->val <= MaxN)
		ans.push_back(p->val);
	print(p->rson, ans);
}

void printState(node* p) {
	if (p == nullptr)
		return;
	pushdown(p);
	if (p->lson != nullptr)
		printf("%d %d\n", p->val, p->lson->val);
	if (p->rson != nullptr)
		printf("%d %d\n", p->val, p->rson->val);
	printState(p->lson);
	printState(p->rson);
}

vector<int> d;
vector<int> ans;

int main(int argc, char* argv[]) {

	read(n, m);
	d.reserve(n + 3);
	d.push_back(-3);
	d.push_back(-1);
	for (int i = 1; i <= n; i++)
		d.push_back(i);
	d.push_back(-2);
	build(d.data(), n + 2);

	//printf("\n+---------- State %d ----------+\n", 0);
	//printState(overroot);

	int l, r;
	for (int i = 1; i <= m; i++) {
		read(l, r);
		reverse(l, r);
		//printf("\n+---------- State %d ----------+\n", i);
		//printState(overroot);
	}

	//printf("\n+---------- State %d ----------+\n", m + 1);
	//printState(overroot);

	print(overroot, ans);

	for (int i = 1; i <= ans.size(); i++)
		printf("%d ", ans[i - 1]);


	return 0;
}

#endif

