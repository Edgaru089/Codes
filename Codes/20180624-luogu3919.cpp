/*
DOCUMENT CODE "20180624-luogu3919.cpp"
CREATION DATE 2018-06-24
SIGNATURE CODE_20180624_LUOGU3919
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180624_LUOGU3919

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int Max = 1000000 + 10;

int n, m;
int d[Max];

inline int read() {
	char c;
	int val = 0;
	bool negative = false;

	while (!isdigit(c = getchar()))
		if (c == '-')
			negative = true;

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	if (negative)
		return -val;
	else
		return val;
}

inline int read(int& val) {
	return val = read();
}


struct node {
	int left, right;
	int val;
	node* lson, *rson;
};

node mem[Max * 20];
int top;
node* allocate() { return &mem[++top]; }

node* root[Max];
int verCount = 0;

void _build(int left, int right, node*& p) {
	p = allocate();
	p->left = left;
	p->right = right;
	if (left == right) {
		p->lson = p->rson = nullptr;
		p->val = d[left];
	}
	else {
		int mid = (left + right) / 2;
		_build(left, mid, p->lson);
		_build(mid + 1, right, p->rson);
	}
}

inline void build(int size) {
	verCount = 1;
	_build(1, size, root[0]);
}

void _changePoint(int point, int val, node*& p, node* prev) {
	p = allocate();
	p->left = prev->left;
	p->right = prev->right;
	p->lson = prev->lson;
	p->rson = prev->rson;
	if (p->left != point || p->right != point) {
		if (point <= p->lson->right)
			_changePoint(point, val, p->lson, prev->lson);
		else if (point >= p->rson->left)
			_changePoint(point, val, p->rson, prev->rson);
	}
	else {
		p->val = val;
	}
}

// RETURN: Version id
inline void changePoint(int point, int val, int verFrom) {
	_changePoint(point, val, root[verCount], root[verFrom]);
	verCount++;
}

int _queryPosition(int point, node* p) {
	if (p->left == p->right)
		return p->val;
	else {
		if (p->lson->right >= point)
			return _queryPosition(point, p->lson);
		else if (p->rson->left <= point)
			return _queryPosition(point, p->rson);
		else
			return -1;
	}
}

inline int queryPosition(int pos, int verFrom) {
	root[verCount] = root[verFrom];
	verCount++;
	return _queryPosition(pos, root[verFrom]);
}



int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	build(n);
	for (int i = 1; i <= m; i++) {
		int v, c, loc, val;
		read(v); read(c);
		if (c == 1) {
			read(loc); read(val);
			changePoint(loc, val, v);
		}
		else if (c == 2) {
			read(loc);
			printf("%d\n", queryPosition(loc, v));
		}
	}


	return 0;
}

#endif

