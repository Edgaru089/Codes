/*
DOCUMENT CODE "20180623-luogu3834.cpp"
CREATION DATE 2018-06-23
SIGNATURE CODE_20180623_LUOGU3834
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180623_LUOGU3834

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int Max = 400000 + 10;

int n, m;

struct Value {
	int val;
	int idPrev;
	int idDiscrete;
};
Value d[Max];

int discreteValBack[Max];

int read() {
	char c;
	int val = 0;

	while (!isdigit(c = getchar()));

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	return val;
}

int read(int& val) {
	return val = read();
}


struct node {
	int sum;
	int left, right;
	node* lson, *rson;
};

node mem[5000000];
int top;
node* allocate() { return &mem[++top]; }

node* root[Max];
int verCount = 0;

void _build(int left, int right, node*& p) {
	p = allocate();
	p->left = left;
	p->right = right;
	p->sum = 0;
	if (left == right)
		p->lson = p->rson = nullptr;
	else {
		int mid = (left + right) / 2;
		_build(left, mid, p->lson);
		_build(mid + 1, right, p->rson);
	}
}

void build(int size) {
	verCount = 1;
	_build(1, size, root[0]);
}

void _addPoint(int point, int val, node*& p, node* prev) {
	p = allocate();
	p->left = prev->left;
	p->right = prev->right;
	p->sum = prev->sum;
	p->lson = prev->lson;
	p->rson = prev->rson;
	if (p->left != point || p->right != point)
		if (point <= p->lson->right)
			_addPoint(point, val, p->lson, prev->lson);
		else if (point >= p->rson->left)
			_addPoint(point, val, p->rson, prev->rson);
	p->sum += val;
}

// RETURN: Version id
int addPoint(int point, int val) {
	_addPoint(point, val, root[verCount], root[verCount - 1]);
	return verCount++;
}


int _getKth(int left, int right, int k, node* pleft, node* pright) {
	if (left == right)
		return discreteValBack[left];
	int cntLeft = pright->lson->sum - pleft->lson->sum;
	if (cntLeft >= k)
		return _getKth(left, pleft->lson->right, k, pleft->lson, pright->lson);
	else
		return _getKth(pleft->rson->left, right, k - cntLeft, pleft->rson, pright->rson);
}

int getKth(int left, int right, int k) {
	return _getKth(1, n, k, root[left - 1], root[right]);
}


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(d[i].val);
		d[i].idPrev = i;
	}

	sort(d + 1, d + n + 1, [](const Value& x, const Value& y)->bool {
		return x.val < y.val;
	});
	for (int i = 1; i <= n; i++) {
		d[i].idDiscrete = i;
		discreteValBack[i] = d[i].val;
	}
	sort(d + 1, d + n + 1, [](const Value& x, const Value& y)->bool {
		return x.idPrev < y.idPrev;
	});

	build(n);

	for (int i = 1; i <= n; i++) {
		addPoint(d[i].idDiscrete, 1);
	}


	int l, r, k;
	for (int i = 1; i <= m; i++) {
		read(l); read(r); read(k);
		printf("%d\n", getKth(l, r, k));
	}

	return 0;
}

#endif

