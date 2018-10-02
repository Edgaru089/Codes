/*
 DOCUMENT NAME "20180926-bnds0770.cpp"
 CREATION DATE 2018-09-26
 SIGNATURE CODE_20180926_BNDS0770
 COMMENT #770. Ð£Ô°ÍâµÄÊ÷
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180926_BNDS0770

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 1e5 + 10;

int n, m;

struct seginfo {
	seginfo() { lcolor = rcolor = segcnt = 0; }
	seginfo(int col) { lcolor = rcolor = col; segcnt = 1; }
	seginfo(const seginfo& left, const seginfo& right) {
		lcolor = left.lcolor;
		rcolor = right.rcolor;
		segcnt = left.segcnt + right.segcnt;
		if (left.rcolor == right.lcolor)
			segcnt--;
	}
	int lcolor, rcolor;
	int segcnt;
};

struct node {
	int left, right;
	int lazy;
	seginfo s;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int d[], int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->lazy = 0;
	if (left == right)
		p->s = seginfo(d[left]);
	else {
		int mid = (left + right) / 2;
		build(d, left, mid, p->lson);
		build(d, mid + 1, right, p->rson);
		p->s = seginfo(p->lson->s, p->rson->s);
	}
}

void pushdown(node* p) {
	if (p != nullptr && p->lazy != 0) {
		p->s = seginfo(p->lazy);
		if (p->lson != nullptr)
			p->lson->lazy = p->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = p->lazy;
		p->lazy = 0;
	}
}

void change(int left, int right, int c, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazy = c;
		return;
	}
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->lson->right >= right)
		change(left, right, c, p->lson);
	else if (p->rson->left <= left)
		change(left, right, c, p->rson);
	else {
		change(left, p->lson->right, c, p->lson);
		change(p->rson->left, right, c, p->rson);
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	p->s = seginfo(p->lson->s, p->rson->s);
}

seginfo query(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->s;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return seginfo(query(left, p->lson->right, p->lson),
					   query(p->rson->left, right, p->rson));
}


int main(int argc, char* argv[]) {

	return 0;
}

#endif

