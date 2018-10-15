/*
 DOCUMENT NAME "20181010-luogu3834.cpp"
 CREATION DATE 2018-10-10
 SIGNATURE CODE_20181010_LUOGU3834
 COMMENT 【模板】可持久化线段树 1（主席树）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181010_LUOGU3834

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;

const int MaxN = 2e5 + 10, MaxM = 2e5;

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

struct valtype {
	int val, id;
};

struct valcmp {
	bool operator () (const valtype& x, const valtype& y) const {
		return x.val < y.val;
	}
};

valtype d[MaxN];
int dis[MaxN], vals[MaxN];

struct node {
	int left, right;
	int sum;
	node* lson, *rson;
};

node* roots[MaxM];
int vercnt = 1;
node mem[2 * MaxN + 50 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = roots[0]) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->sum = 0;
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
	}
}

void _insert(int pos, int val, node* prev, node*& cur) {
	cur = ALLOCATE;
	memcpy(cur, prev, sizeof(node));
	if (prev->left == prev->right&&prev->right == pos) {
		cur->sum = val;
		return;
	}
	if (prev->lson->right >= pos)
		_insert(pos, val, prev->lson, cur->lson);
	else /* prev->rson->left <= pos */
		_insert(pos, val, prev->rson, cur->rson);
	cur->sum = cur->lson->sum + cur->rson->sum;
}

void insert(int pos, int val)
{ node* prev = roots[vercnt - 1]; _insert(pos, val, prev, roots[vercnt++]); }


// (l, r]
int _query(int k, node* l, node* r) {
	if (l->left == l->right)
		return l->left;
	if (r->lson->sum - l->lson->sum >= k)
		return _query(k, l->lson, r->lson);
	else
		return _query(k - (r->lson->sum - l->lson->sum), l->rson, r->rson);
}

// [l, r]
int querykth(int l, int r, int k) {
	return vals[_query(k, roots[l - 1], roots[r])];
}






int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(d[i].val);
		d[i].id = i;
	}

	sort(d + 1, d + n + 1, valcmp());

	for (int i = 1; i <= n; i++) {
		dis[d[i].id] = i;
		vals[i] = d[i].val;
	}

	build();
	for (int i = 1; i <= n; i++)
		insert(dis[i], 1);

	for (int i = 1; i <= m; i++) {
		int l, r, k;
		read(l); read(r); read(k);
		printf("%d\n", querykth(l, r, k));
	}


	return 0;
}

#endif

