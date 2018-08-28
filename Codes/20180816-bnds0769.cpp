/*
DOCUMENT NAME "20180816-bnds0769.cpp"
CREATION DATE 2018-08-16
SIGNATURE CODE_20180816_BNDS0769
COMMENT 线段树模板3-区间加法+区间最值
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180816_BNDS0769

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int MaxN = 100000 + 10;

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
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
int d[MaxN];

struct node {
	int max, min, lazy;
	int left, right;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->min = p->max = d[left];
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->max = max(p->lson->max, p->rson->max);
		p->min = min(p->lson->min, p->rson->min);
	}
}

void pushdown(node* p) {
	if (p == nullptr || p->lazy == 0)
		return;
	p->max += p->lazy;
	p->min += p->lazy;
	if (p->lson != nullptr)
		p->lson->lazy += p->lazy;
	if (p->rson != nullptr)
		p->rson->lazy += p->lazy;
	p->lazy = 0;
}

void add(int left, int right, int val, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazy += val;
		return;
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->lson->right >= right)
		add(left, right, val, p->lson);
	else if (p->rson->left <= left)
		add(left, right, val, p->rson);
	else {
		add(left, p->lson->right, val, p->lson);
		add(p->rson->left, right, val, p->rson);
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	p->max = max(p->lson->max, p->rson->max);
	p->min = min(p->lson->min, p->rson->min);
}

int querymax(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->max;
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->lson->right >= right)
		return querymax(left, right, p->lson);
	else if (p->rson->left <= left)
		return querymax(left, right, p->rson);
	else
		return max(querymax(left, p->lson->right, p->lson),
				   querymax(p->rson->left, right, p->rson));
}

int querymin(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->min;
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->lson->right >= right)
		return querymin(left, right, p->lson);
	else if (p->rson->left <= left)
		return querymin(left, right, p->rson);
	else
		return min(querymin(left, p->lson->right, p->lson),
				   querymin(p->rson->left, right, p->rson));
}


int m;
int x, a, b, c;

int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	build();
	for (int i = 1; i <= m; i++) {
		read(x);
		if (x == 1) {
			read(a, b, c);
			add(a, b, c);
		}
		else if (x == 2) {
			read(a, b);
			printf("%d\n", querymax(a, b));
		}
		else if (x == 3) {
			read(a, b);
			printf("%d\n", querymin(a, b));
		}
	}

	return 0;
}

#endif

