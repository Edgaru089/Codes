/*
DOCUMENT NAME "20180809-bnds0735.cpp"
CREATION DATE 2018-08-09
SIGNATURE CODE_20180809_BNDS0735
COMMENT [HEOI2016/TJOI2016]排序 / luogu2824 / 线段树+二分答案
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180809_BNDS0735

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 30000 + 10, MaxM = 30000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;
int a[MaxN];
struct op {
	int what;
	int l, r;
};
op p[MaxM];
int q;

struct node {
	int left, right;
	int lazy, sum;
	node* lson, *rson;
};

node *root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int seq[], int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->lazy = -1;
	if (left == right) {
		p->lson = p->rson = nullptr;
		p->sum = seq[left];
	}
	else {
		int mid = (left + right) / 2;
		build(seq, left, mid, p->lson);
		build(seq, mid + 1, right, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}
}

void pushdown(node* p) {
	if (p == nullptr || p->lazy == -1)
		return;
	p->sum = p->lazy*(p->right - p->left + 1);
	if (p->lson != nullptr)
		p->lson->lazy = p->lazy;
	if (p->rson != nullptr)
		p->rson->lazy = p->lazy;
	p->lazy = -1;
}

void change(int left, int right, int val, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazy = val;
		return;
	}
	if (p->lson->right >= right)
		change(left, right, val, p->lson);
	else if (p->rson->left <= left)
		change(left, right, val, p->rson);
	else {
		change(left, p->lson->right, val, p->lson);
		change(p->rson->left, right, val, p->rson);
	}
	pushdown(p->lson);
	pushdown(p->rson);
	p->sum = p->lson->sum + p->rson->sum;
}

int query(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->sum;
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return (query(left, p->lson->right, p->lson) +
				query(p->rson->left, right, p->rson));
}

int val[MaxN];
bool check(int x) {
	for (int i = 1; i <= n; i++) {
		if (a[i] >= x)
			val[i] = 1;
		else
			val[i] = 0;
	}
	memtop = mem;
	root = nullptr;
	build(val);
	for (int i = 1; i <= m; i++) {
		int cnt = query(p[i].l, p[i].r);
		if (p[i].what == 0) { // ascending
			if (cnt > 0)
				change(p[i].r - cnt + 1, p[i].r, 1);
			if (cnt < p[i].r - p[i].l + 1)
				change(p[i].l, p[i].r - cnt, 0);
		}
		else if (p[i].what == 1) { // descending
			if (cnt > 0)
				change(p[i].l, p[i].l + cnt - 1, 1);
			if (cnt < p[i].r - p[i].l + 1)
				change(p[i].l + cnt, p[i].r, 0);
		}
	}
	return val[q];
}


int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= m; i++)
		read(p[i].what, p[i].l, p[i].r);
	read(q);

	int l=1, r=n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}

	if (check(l))
		printf("%d\n", l);
	else
		printf("%d\n", r);


	return 0;
}

#endif

