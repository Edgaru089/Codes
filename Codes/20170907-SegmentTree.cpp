/*
DOCUMENT CODE "SegmentTree.cpp"
CREATION DATE 2017-09-07
SIGNATURE CODE_20170907_SEGMENTTREE
TOPIC 可持久化线段树?
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20170907_SEGMENTTREE

#include <cstdlib>
#include <iostream>
using namespace std;

struct st {
	int sum, lazy;
	int left, right;
	st* lson, *rson, *prever;
};

st* root[1001];
int thisver;

st pool[100001];
int top;

void build(st*& p, int left, int right) {
	p = &pool[++top];
	if (left == right) {
		p->left = p->right = left;
		p->lson = p->rson = NULL;
		p->sum = 0;
		p->lazy = 0;
	}
	else {
		int mid = (left + right) / 2;
		p->left = left;
		p->right = right;
		build(p->lson, left, mid);
		build(p->rson, mid + 1, right);
		p->sum = p->lson->sum + p->rson->sum; // Should be zero; left for backward-compatibility
		p->lazy = 0;
	}
}

void change(int left, int right, int add, st* basep = root[thisver], st*& p = root[thisver + 1]) {
	p = &pool[++top];
	p->prever = basep;
	p->lazy = basep->lazy;
	p->left = basep->left;
	p->right = basep->right;

	if (left == basep->left&&right == basep->right) {
		p->lazy += add;
		return;
	}

	if (basep->lson->right >= right)
		change(left, right, add, basep->lson, p->lson);
	else if (basep->rson->left <= left)
		change(left, right, add, basep->rson, p->rson);
	else {
		change(left, basep->lson->right, add, basep->lson, p->lson);
		change(basep->rson->left, right, add, basep->rson, p->rson);
	}

	p->sum = p->lson->sum + p->lson->lazy*(p->lson->right - p->lson->left + 1)
		+ p->rson->sum + p->rson->lazy*(p->rson->right - p->rson->left + 1);
}

int query(int left, int right, st* p = root[thisver]) {
	if (left == p->left&&right == p->right)
		return p->sum + p->lazy*(p->right - p->left + 1);

	if (p->lson->right >= right)
		return query(left, right, p->lson) + p->lazy*(p->right - p->left + 1);
	else if (p->rson->left <= left)
		return query(left, right, p->rson) + p->lazy*(p->right - p->left + 1);
	else
		return query(left, p->lson->right, p->lson)
		+ query(p->rson->left, right, p->rson)
		+ p->lazy*(p->right - p->left + 1);
}

int main(int argc, char* argv[]) {




	return 0;
}

#endif
