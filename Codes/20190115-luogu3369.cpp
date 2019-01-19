/*
 DOCUMENT NAME "20190115-luogu3369.cpp"
 CREATION DATE 2019-01-15
 SIGNATURE CODE_20190115_LUOGU3369
 COMMENT P3369 ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / FHQ Treap
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190115_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int infinity = 1e8;
const int MaxN = 100000 + 10;

int n, m;
int k, x;

struct node {
	int val, cnt;
	int key, size;
	node* lson, *rson;
//	node* fa;
};

node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

node* root;

stack<node*> recycle;
node* allocate(int val) {
	node* p;
	if (!recycle.empty()) {
		p = recycle.top();
		recycle.pop();
	} else
		p = ALLOCATE;
	p->cnt = 1;
	p->val = val;
	p->key = rand();
	return p;
}

void dispose(node* p) {
	memset(p, 0, sizeof(node));
	recycle.push(p);
}

int cntof(node* p) { return p ? p->cnt : 0; }
int ssizeof(node* p) { return p ? p->size : 0; }

void update(node* p) {
	if (p)
		p->size = ssizeof(p->lson) + p->cnt + ssizeof(p->rson);
}

node* merge(node* x, node* y) {
	if (!x || !y)
		return x ? x : y;
	if (x->val > y->val)
		swap(x, y);
	if (x->key < y->key) {
		x->rson = merge(x->rson, y);
		update(x);
		return x;
	} else {
		y->lson = merge(y->lson, x);
		update(y);
		return y;
	}
}

void splitval(node* p, int val, node*& left, node*& right) {
	if (!p)
		left = right = 0;
	else {
		if (p->val <= val) {
			left = p;
			splitval(p->rson, val, p->rson, right);
		} else { /* p->val > val */
			right = p;
			splitval(p->lson, val, left, p->lson);
		}
		update(p);
	}
}

void insert(int val) {
	node* x, *p, *y, *t;
	splitval(root, val - 1, x, t);
	splitval(t, val, p, y);
	if (!p)
		p = allocate(val);
	else
		p->cnt++;
	root = merge(merge(x, allocate(val)), y);
}

void erase(int val) {
	node* x, *p, *y, *t;
	splitval(root, val - 1, x, t);
	splitval(t, val, p, y);
	p->cnt--;
	p->size--;
	if (!p->cnt) {
		dispose(p);
		p = 0;
	}
	root = merge(merge(x, p), y);
}

int getkth(int k, node* p = root) {
	if (ssizeof(p->lson) >= k)
		return getkth(k, p->lson);
	else if (ssizeof(p->lson) + p->cnt >= k)
		return p->val;
	else
		return getkth(k - ssizeof(p->lson) - p->cnt, p->rson);
}

int getprev(int val, node* p = root) {
	int ans = -infinity;
	while (p) {
		if (p->val < val) {
			ans = max(ans, p->val);
			p = p->rson;
		} else /* p->val >= val */ {
			p = p->lson;
		}
	}
	return ans;
}

int getnext(int val, node* p = root) {
	int ans = infinity;
	while (p) {
		if (p->val <= val) {
			p = p->rson;
		} else /* p->val > val */ {
			ans = min(ans, p->val);
			p = p->lson;
		}
	}
	return ans;
}

int getlesscnt(int val, node* p = root) {
	if (!p)
		return 0;
	if (val < p->val)
		return getlesscnt(val, p->lson);
	else if (val == p->val)
		return ssizeof(p->lson);
	else /* val > p->val */
		return ssizeof(p->lson) + p->cnt + getlesscnt(val, p->rson);
}


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(k); read(x);
		switch (k) {
			case 1:
				insert(x);
				break;
			case 2:
				erase(x);
				break;
			case 3:
				printf("%d\n", getlesscnt(x) + 1);
				break;
			case 4:
				printf("%d\n", getkth(x));
				break;
			case 5:
				printf("%d\n", getprev(x));
				break;
			case 6:
				printf("%d\n", getnext(x));
				break;
		}
	}

	return 0;
}

#endif

