/*
 DOCUMENT NAME "20181012-luogu3369.cpp"
 CREATION DATE 2018-10-12
 SIGNATURE CODE_20181012_LUOGU3369
 COMMENT ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181012_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

typedef long long ll;
const int MaxN = 1000000 + 10;

void read(int& val) {
	val = 0;
	int c;
	bool inv = false;;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

int n, k, x;

struct node {
	int val, cnt;
	int size;
	node* lson, *rson;
	node* father;
};

node* overroot;
#define ROOT (overroot->lson)
node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

node* wantSplay;

typedef int sontype;
const sontype lson = 0, rson = 1;
sontype tell(node* son) { return son->father->lson == son ? lson : rson; }
node*& get(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}
int size(node* p) {
	if (p)
		return p->size;
	else
		return 0;
}

void update(node* p) {
	p->size = p->cnt + size(p->lson) + size(p->rson);
}

void rotate(node* p) {
	sontype t = tell(p);
	node* f = p->father, *b = get(p, 1 - t);
	connect(f->father, p, tell(f));
	connect(p, f, 1 - t);
	connect(f, b, t);
	update(f);
	update(p);
}

void splay(node* p, node* target = overroot) {
	while (p->father != target) {
		if (p->father->father != target)
			if (tell(p) == tell(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}

void insert(int val, node*& p = ROOT, node* father = overroot) {
	if (!p) {
		p = ALLOCATE;
		p->val = val;
		p->cnt = p->size = 1;
		p->father = father;
		splay(p);
	} else {
		p->size++;
		if (p->val == val) {
			p->cnt++;
			splay(p);
		} else if (val < p->val)
			insert(val, p->lson, p);
		else /* val > p->val */
			insert(val, p->rson, p);
	}
}

void _destroy(node* p) {
	splay(p);
	if (!p->lson)
		connect(p->father, p->rson, tell(p));
	else {
		node* cur = p->lson, *prev = 0;
		while (cur->rson) {
			prev = cur;
			cur = cur->rson;
		}
		connect(cur->father, cur->lson, tell(cur));
		connect(p->father, cur, tell(p));
		if (p->lson != cur)
			connect(cur, p->lson, lson);
		connect(cur, p->rson, rson);
		if (!prev)
			prev = cur;
		while (prev) {
			update(prev);
			prev = prev->father;
		}
	}
}

void erase(int val, node* p = ROOT) {
	p->size--;
	if (p->val == val) {
		p->cnt--;
		if (p->cnt == 0)
			_destroy(p);
		else
			splay(p);
	} else if (val < p->val) {
		erase(val, p->lson);
	} else /* val > p->val */ {
		erase(val, p->rson);
	}
}

int getrank(int val, node* p = ROOT) {
	if (p)
		wantSplay = p;
	if (!p)
		return 1;
	else if (p->val == val)
		return size(p->lson) + 1;
	else if (val < p->val)
		return getrank(val, p->lson);
	else /* val > p->val */
		return getrank(val, p->rson) + size(p->lson) + p->cnt;
}

int getkth(int k, node* p = ROOT) {
	if (p)
		wantSplay = p;
	if (k <= size(p->lson))
		return getkth(k, p->lson);
	else if (k <= size(p->lson) + p->cnt)
		return p->val;
	else
		return getkth(k - size(p->lson) - p->cnt, p->rson);
}

node* getnode(int val, node* p = ROOT) {
	if (p)
		wantSplay = p;
	if (!p || p->val == val)
		return p;
	else if (val < p->val)
		return getnode(val, p->lson);
	else /* val > p->val */
		return getnode(val, p->rson) + size(p->lson) + p->cnt;
}

int getprev(int val, node* p = ROOT) {
	int ans = -1e8;
	while (p) {
		wantSplay = p;
		if (p->val < val)
			ans = max(ans, p->val);
		if (val <= p->val)
			p = p->lson;
		else /* val > p->val */
			p = p->rson;
	}
	return ans;
}

int getnext(int val, node* p = ROOT) {
	int ans = 1e8;
	while (p) {
		wantSplay = p;
		if (p->val > val)
			ans = min(ans, p->val);
		if (val < p->val)
			p = p->lson;
		else /* val >= p->val */
			p = p->rson;
	}
	return ans;
}



int main(int argc, char* argv[]) {

	overroot = ALLOCATE;

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
		if (wantSplay) {
			splay(wantSplay);
			wantSplay = 0;
		}
	}


	return 0;
}

#endif

