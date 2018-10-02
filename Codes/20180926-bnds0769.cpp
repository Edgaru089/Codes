/*
 DOCUMENT NAME "20180926-bnds0769.cpp"
 CREATION DATE 2018-09-26
 SIGNATURE CODE_20180926_BNDS0769
 COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180926_BNDS0769

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MaxN = 100000 + 10, MaxM = MaxN;

template<typename IntType = int>
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
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<>
char read<char>() {
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	return c;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;
ll d[MaxN];

struct node {
	int left, right;
	ll max, min, lazy;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->max = p->min = d[left];
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->max = max(p->lson->max, p->rson->max);
		p->min = min(p->lson->min, p->rson->min);
	}
}

void pushdown(node* p) {
	if (p && p->lazy != 0) {
		p->max += p->lazy;
		p->min += p->lazy;
		if (p->lson)
			p->lson->lazy += p->lazy;
		if (p->rson)
			p->rson->lazy += p->lazy;
		p->lazy = 0;
	}
}

ll querymax(int left, int right, node* p = root) {
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->left == left && p->right == right)
		return p->max;
	if (p->lson->right >= right)
		return querymax(left, right, p->lson);
	else if (p->rson->left <= left)
		return querymax(left, right, p->rson);
	else
		return max(querymax(left, p->lson->right, p->lson),
				   querymax(p->rson->left, right, p->rson));
}

ll querymin(int left, int right, node* p = root) {
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if (p->left == left && p->right == right)
		return p->min;
	if (p->lson->right >= right)
		return querymin(left, right, p->lson);
	else if (p->rson->left <= left)
		return querymin(left, right, p->rson);
	else
		return min(querymin(left, p->lson->right, p->lson),
				   querymin(p->rson->left, right, p->rson));
}

void add(int left, int right, ll val, node* p = root) {
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



int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	build();
	for (int i = 1; i <= m; i++) {
		int k, x, y;
		ll p;
		read(k, x, y);
		switch (k) {
			case 1:
				read(p);
				add(x, y, p);
				break;
			case 2:
				printf("%lld\n", querymax(x, y));
				break;
			case 3:
				printf("%lld\n", querymin(x, y));
				break;
		}
	}

	return 0;
}

#endif

