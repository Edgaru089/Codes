/*
 DOCUMENT NAME "20180909-now172A.cpp"
 CREATION DATE 2018-09-09
 SIGNATURE CODE_20180909_NOW172A
 COMMENT A-中位数 / 我为什么要写主席树啊qwq
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180909_NOW172A

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 1e5 + 10, MaxA = 1e9 + 10;

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

struct wid {
	int val, id;
};

int n, len;
int aval[MaxN];
wid a[MaxN];
int disid[MaxN];    // original id -> discretilized val
int disrevid[MaxN]; // discretilized val -> original id

struct node {
	int sum;
	int left, right;
	node* lson, *rson;
};

node* root[MaxN];
node mem[5 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root[0]) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->lson = p->rson = nullptr;
	if (left == right)
		p->sum = 0;
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->sum = 0;
	}
}

void addpnt(int pos, int val, node* prev, node*& thisver) {
	thisver = ALLOCATE;
	thisver->left = prev->left;
	thisver->right = prev->right;
	thisver->lson = prev->lson;
	thisver->rson = prev->rson;
	thisver->sum = prev->sum;
	if (prev->left == prev->right&&prev->right == pos)
		thisver->sum += val;
	else {
		if (prev->lson->right >= pos)
			addpnt(pos, val, prev->lson, thisver->lson);
		else /* p->rson->left <= pos */
			addpnt(pos, val, prev->rson, thisver->rson);
		thisver->sum = thisver->lson->sum + thisver->rson->sum;
	}
}

void addval(int disval, int i) {
	addpnt(disval, 1, root[i - 1], root[i]);
}

int querysum(int left, int right, node* lver, node* rver) {
	if (lver->left == left && lver->right == right)
		return rver->sum - lver->sum;
	if (lver->lson->right >= right)
		return querysum(left, right, lver->lson, rver->lson);
	else if (lver->rson->left <= left)
		return querysum(left, right, lver->rson, rver->rson);
	else
		return(
			querysum(left, lver->lson->right, lver->lson, rver->lson) +
			querysum(lver->rson->left, right, lver->rson, rver->rson));
}

int queryless(int l, int r, int disvalk) {
	return querysum(1, disvalk - 1, root[l - 1], root[r]);
}
int querygreater(int l, int r, int disvalk) {
	return querysum(disvalk + 1, n, root[l - 1], root[r]);
}

int _querykth(int k, node* lver, node* rver) {
	if (lver->left == lver->right)
		return lver->left;
	if (rver->lson->sum - lver->lson->sum >= k)
		return _querykth(k, lver->lson, rver->lson);
	else /* rson */
		return _querykth(k - rver->lson->sum + lver->lson->sum, lver->rson, rver->rson);
}
int querykth(int l, int r, int k) {
	return _querykth(k, root[l - 1], root[r]);
}

int getk(int l, int r) {
	int s = r - l + 1;
	int x;
	if (s % 2 == 1)
		x = (s + 1) / 2;
	else
		x = s / 2;
	return x;
}

int main(int argc, char* argv[]) {

	read(n, len);
	for (int i = 1; i <= n; i++) {
		read(a[i].val);
		aval[i] = a[i].val;
		a[i].id = i;
	}

	sort(a + 1, a + n + 1, [](const wid& x, const wid& y) {
		return x.val < y.val;
	});

	for (int i = 1; i <= n; i++) {
		disid[a[i].id] = i;
		disrevid[i] = a[i].id;
	}

	build();
	for (int i = 1; i <= n; i++)
		addval(disid[i], i);

	int ans = 0;
	for (int l = 1; l <= n - len + 1; l++)
		for (int r = l + len - 1; r <= n; r++)
			ans = max(ans, aval[disrevid[querykth(l, r, getk(l, r))]]);

	printf("%d\n", ans);

	return 0;
}

#endif

