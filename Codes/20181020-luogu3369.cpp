/*
 DOCUMENT NAME "20181020-luogu3369.cpp"
 CREATION DATE 2018-10-20
 SIGNATURE CODE_20181020_LUOGU3369
 COMMENT P3369 ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / Treap
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181020_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>
using namespace std;

const int MaxN = 1e5 + 10;

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

struct node {
	int val, key;
	int cnt, size;
	node* lson, *rson;
	node* father;
};


node* root;
node mem[MaxN * 2], *memtop = mem;
#define ALLOCATE (++memtop)

typedef int sontype;
const sontype lson = 0, rson = 1;
node*& get(node* father, sontype t) { return t == lson ? father->lson : father->rson; }
sontype tell(node* son) { return (!son->father || son->father->lson == son) ? lson : rson; }
void connect(node* father, node* son, sontype t) {
	if (father)
		get(father, t) = son;
	if (son)
		son->father = father;
}

int nodesize(node* p) { return !p ? 0 : p->size; }
void update(node* p) {
	p->size = nodesize(p->lson) + nodesize(p->rson) + p->cnt;
}

void rotate(node* p) {
	sontype t = tell(p);
	node* fa = p->father, *b = get(p, 1 - t);
	connect(fa->father, p, tell(fa));
	connect(p, fa, 1 - t);
	connect(fa, b, t);
	update(fa);
	update(p);
	if (!p->father)
		root = p;
}

void adjust(node* p) {
	while (p->father && p->father->key > p->key)
		rotate(p);
}

void insert(int x, node*& p = root, node* from = 0) {
	if (!p) {
		p = ALLOCATE;
		p->father = from;
		p->val = x;
		p->cnt = p->size = 1;
		p->key = rand();
		if (from && p->key < from->key)
			adjust(p);
	} else {
		p->size++;
		if (p->val == x)
			p->cnt++;
		else if (x < p->val)
			insert(x, p->lson, p);
		else /* x > p->val */
			insert(x, p->rson, p);
	}
}

void destroy(node* p) {
	while (p->lson&&p->rson) {
		if (p->lson->key < p->rson->key) {
			if (p == root)
				root = p->lson;
			rotate(p->lson);
		} else {
			if (p == root)
				root = p->rson;
			rotate(p->rson);
		}
	}
	if (p == root) {
		root = (p->lson ? p->lson : p->rson);
		if (p->lson || p->rson)
			(p->lson ? p->lson : p->rson)->father = 0;
	} else
		connect(p->father, (p->lson ? p->lson : p->rson), tell(p));
}

node* wantDestroy = 0;

void erase(int val, node* p = root) {
	p->size--;
	if (p->val == val) {
		p->cnt--;
		if (!p->cnt)
			destroy(p);
	} else {
		if (val < p->val)
			erase(val, p->lson);
		else /* val > p->val */
			erase(val, p->rson);
	}
}

int getrank(int val, node* p = root) {
	if (!p)
		return 1;
	else if (val < p->val)
		return getrank(val, p->lson);
	else if (val == p->val)
		return nodesize(p->lson) + 1;
	else /* val > p->val */
		return nodesize(p->lson) + p->cnt + getrank(val, p->rson);
}

int getkth(int k, node* p = root) {
	if (k <= nodesize(p->lson))
		return getkth(k, p->lson);
	else if (k <= nodesize(p->lson) + p->cnt)
		return p->val;
	else /* k > nodesize(p->lson) + p->cnt */
		return getkth(k - nodesize(p->lson) - p->cnt, p->rson);
}

int getprev(int val, node* p = root) {
	int maxval = -1e8;
	while (p) {
		if (val <= p->val)
			p = p->lson;
		else { /* val > p->val */
			maxval = max(maxval, p->val);
			p = p->rson;
		}
	}
	return maxval;
}

int getnext(int val, node* p = root) {
	int minval = 1e8;
	while (p) {
		if (val < p->val) {
			if (val != p->val)
				minval = min(minval, p->val);
			p = p->lson;
		} else /* val >= p->val */
			p = p->rson;
	}
	return minval;
}

int n;
int opt, x;


int main(int argc, char* argv[]) {

	srand(time(0));

	read(n);
	for (int i = 1; i <= n; i++) {
		read(opt); read(x);
		switch (opt) {
			case 1:
				insert(x);
				break;
			case 2:
				erase(x);
				break;
			case 3:
				printf("%d\n", getrank(x));
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

