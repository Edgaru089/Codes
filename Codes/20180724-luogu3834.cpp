/*
DOCUMENT NAME "20180724-luogu3834.cpp"
CREATION DATE 2018-07-24
SIGNATURE CODE_20180724_LUOGU3834
COMMENT 【模板】可持久化线段树 1（主席树）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180724_LUOGU3834

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

constexpr int MaxN = 2e5 + 10, MaxM = 2e5 + 10;

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

int n, m;

struct node {
	int val, size;
	int left, right;
	node* lson, *rson;
};

node* root[MaxN];
int vercnt = 1;
node mem[35 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root[0]) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->val = 0;
	p->size = 0;
	p->lson = p->rson = nullptr;
	if (left != right) {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
	}
}

void _addpnt(int pos, int val, node*& cur, node* prev) {
	cur = ALLOCATE;
	cur->left = prev->left;
	cur->right = prev->right;
	cur->size = prev->size;
	cur->lson = prev->lson;
	cur->rson = prev->rson;
	if (prev->left == prev->right) {
		cur->val = val;
		cur->size = 1;
		return;
	}
	if (prev->lson->right >= pos)
		_addpnt(pos, val, cur->lson, prev->lson);
	else if (prev->rson->left <= pos)
		_addpnt(pos, val, cur->rson, prev->rson);
	cur->size = cur->lson->size + cur->rson->size;
}

int addpnt(int pos, int val) {
	_addpnt(pos, val, root[vercnt], root[vercnt - 1]);
	vercnt++;
	return vercnt - 1;
}

int _get(int left, int right, int k, node* lver, node* rver) {
	if (lver->left == lver->right)
		return rver->val;
	int leftcnt = rver->lson->size - lver->lson->size;
	if (leftcnt >= k)
		return _get(left, lver->lson->right, k, lver->lson, rver->lson);
	else
		return _get(lver->rson->left, right, k - leftcnt, lver->rson, rver->rson);
}

int getkth(int left, int right, int k) {
	return _get(1, n, k, root[left - 1], root[right]);
}

typedef tuple<int, int, int> tint;
vector<tint> vec;

int main(int argc, char* argv[]) {

	read(n, m);
	int x;
	for (int i = 1; i <= n; i++)
		vec.push_back(make_tuple(read(), i, 0));

	sort(vec.begin(), vec.end());
	for (int i = 1; i <= n; i++) {
		get<2>(vec[i - 1]) = i;
	}
	sort(vec.begin(), vec.end(), [](const tint& x, const tint& y) {
		return get<1>(x) < get<1>(y);
	});

	build();
	for (int i = 1; i <= n; i++) {
		addpnt(get<2>(vec[i - 1]), get<0>(vec[i - 1]));
	}

	int l, r, k;
	for (int i = 1; i <= m; i++) {
		read(l, r, k);
		printf("%d\n", getkth(l, r, k));
	}

	return 0;
}

#endif

