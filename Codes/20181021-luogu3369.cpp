/*
 DOCUMENT NAME "20181021-luogu3369.cpp"
 CREATION DATE 2018-10-21
 SIGNATURE CODE_20181021_LUOGU3369
 COMMENT P3369 【模板】普通平衡树 / Treap（再写一遍）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181021_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdio>
using namespace std;

const int MaxN = 100000 + 10;

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
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

typedef int sontype;
const sontype lson = 0, rson = 1;
sontype tell(node* son) { return (!son->father || son->father->lson == son) ? lson : rson; }
node*& get(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}

int size(node* p) { return p ? p->size : 0; }
void update(node* p) {
	p->size = size(p->lson) + size(p->rson) + p->cnt;
}

void rotate(node* p) {
	if (!p->father)
		return;
	sontype t = tell(p);
	node* f = p->father, *b = get(p, 1 - t);
	connect(f->father, p, tell(f));
	connect(p, f, 1 - t);
	connect(f, b, t);
	update(f);
	update(p);
	if (!p->father)
		root = p;
}

void adjust(node* p) {
	while (p->father&&p->father->key > p->key)
		rotate(p);
}

void insert(int val, node*& p = root, node* from = 0) {
	if (!p) {
		p = ALLOCATE;
		p->father = from;
		p->val = val;
		p->key = rand();
		p->cnt = p->size = 1;
		if (from&&p->key < from->key)
			adjust(p);
	} else {
		p->size++;
		if (val < p->val)
			insert(val, p->lson, p);
		else if (val == p->val)
			p->cnt++;
		else /* val > p->val */
			insert(val, p->rson, p);
	}
}

void destroy(node* p) {
	while (p->lson&&p->rson)
		if (p->lson->val < p->rson->val)
			rotate(p->lson);
		else
			rotate(p->rson);
	if (p == root)
		root = (p->lson ? p->lson : p->rson);
	connect(p->father, (p->lson ? p->lson : p->rson), tell(p));
}


void erase(int val, node* p = root) {
	p->size--;
	if (val < p->val)
		erase(val, p->lson);
	else if (val == p->val) {
		p->cnt--;
		if (!p->cnt)
			destroy(p);
	} else /* val > p->val */
		erase(val, p->rson);
}

int getrank(int val, node* p = root) {
	if (!p)
		return 1;
	else if (val < p->val)
		return getrank(val, p->lson);
	else if (val == p->val)
		return size(p->lson) + 1;
	else /* val > p->val */
		return getrank(val, p->rson) + size(p->lson) + p->cnt;
}

int getkth(int k, node* p = root) {
	if (k <= size(p->lson))
		return getkth(k, p->lson);
	else if (k <= size(p->lson) + p->cnt)
		return p->val;
	else
		return getkth(k - size(p->lson) - p->cnt, p->rson);
}

int getprev(int val, node* p = root) {
	int ans = -1e8;
	while (p) {
		if (val <= p->val)
			p = p->lson;
		else { /* val > p->val */
			ans = max(ans, p->val);
			p = p->rson;
		}
	}
	return ans;
}

int getnext(int val, node* p = root) {
	int ans = 1e8;
	while (p) {
		if (val < p->val) {
			ans = min(ans, p->val);
			p = p->lson;
		} else /* val >= p->val */
			p = p->rson;
	}
	return ans;
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

