/*
DOCUMENT NAME "20180816-luogu3369.cpp"
CREATION DATE 2018-08-16
SIGNATURE CODE_20180816_LUOGU3369
COMMENT ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / Splay
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180816_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10;

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
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

typedef int sontype;
const int lson = 0, rson = 1, unknown = -1;
#define OTHER(type) (1 - type)

struct node {
	int val, cnt;
	int size;
	node* lson, *rson;
	node* father;
	node*& son(sontype type) { return type == ::lson ? lson : rson; }
	sontype tellwhich(node* son) {
		if (son == lson)
			return ::lson;
		else if (son == rson)
			return ::rson;
		else
			return unknown;
	}
};

int ssize(node* p) { return p == nullptr ? 0 : p->size; }
#define UPDATE_SIZE(p) p->size=ssize(p->lson)+ssize(p->rson)+p->cnt

node* overroot;
#define ROOT (overroot->lson)
node mem[20 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)
void connect(node* father, node* son, sontype type) {
	assert(type != unknown);
	if (father != nullptr)
		father->son(type) = son;
	if (son != nullptr)
		son->father = father;
}

void rotateup(node* p) {
	assert(p->father != nullptr);
	sontype sonp = p->father->tellwhich(p);
	assert(sonp != unknown);
	node* f = p->father, *gf = p->father->father;
	node* b = p->son(OTHER(sonp));
	connect(gf, p, gf->tellwhich(f));
	connect(p, f, OTHER(sonp));
	connect(f, b, sonp);
	UPDATE_SIZE(f);
	UPDATE_SIZE(p);
}

// Splay p up until p is a son of target
void splay(node* p, node* target = overroot) {
	while (p->father != target && p->father->father != target) {
		if (p->father->tellwhich(p) == p->father->father->tellwhich(p->father))
			rotateup(p->father);
		else
			rotateup(p);
		rotateup(p);
	}
	if (p->father->father == target)
		rotateup(p);
}

node* wantSplayNode = nullptr;

void insert(int val, node*& p = ROOT, node* fa = overroot) {
	if (p == nullptr) {
		p = ALLOCATE;
		p->val = val;
		p->father = fa;
		p->cnt = 1;
		p->size = 1;
		splay(p);
	}
	else {
		p->size++;
		if (val < p->val)
			insert(val, p->lson, p);
		else if (val == p->val) {
			p->cnt++;
			splay(p);
		}
		else // val > p->val
			insert(val, p->rson, p);
	}
}

void output(node* p = overroot) {
	if (p->lson != nullptr) {
		cout << p->val << " " << p->lson->val << endl;
		output(p->lson);
	}
	if (p->rson != nullptr) {
		cout << p->val << " " << p->rson->val << endl;
		output(p->rson);
	}
}

void _destroy(node* p) {
	splay(p);
	assert(p->father == overroot);
	if (p->lson == nullptr) {
		connect(p->father, p->rson, p->father->tellwhich(p));
		UPDATE_SIZE(p->father);
		// delete p;
	}
	else {
		node* target = p->lson;
		node* prev = nullptr;
		while (target->rson != nullptr) {
			prev = target;
			target = target->rson;
		}
		assert(target->rson == nullptr);
		assert(target->father != overroot);
		connect(target->father, target->lson, target->father->tellwhich(target));
		connect(p->father, target, p->father->tellwhich(p));
		if (target != p->lson)
			connect(target, p->lson, lson);
		else
			connect(target, target->lson, lson);
		connect(target, p->rson, rson);
		if (prev == nullptr)
			prev = target;
		while (prev != nullptr) {
			UPDATE_SIZE(prev);
			prev = prev->father;
		}
		// delete p;
	}
}

void erase(int val, node* p = ROOT) {
	if (val < p->val)
		erase(val, p->lson);
	else if (val > p->val)
		erase(val, p->rson);
	else { // val == p->val
		if (p->cnt > 1)
			p->cnt--;
		else
			_destroy(p);
	}
	UPDATE_SIZE(p);
}

int getrank(int val, node* p = ROOT, node* from = overroot) {
	if (p == nullptr) {
		wantSplayNode = from;
		return 1;
	}
	else if (val < p->val)
		return getrank(val, p->lson, p);
	else if (val == p->val) {
		wantSplayNode = p;
		return ssize(p->lson) + 1;
	}
	else //val > p->val
		return ssize(p->lson) + p->cnt + getrank(val, p->rson, p);
}

int getkth(int rank, node* p = ROOT) {
	assert(p != nullptr);
	if (rank <= ssize(p->lson))
		return getkth(rank, p->lson);
	else if (rank <= ssize(p->lson) + p->cnt) // implict: rank > p->lson->size
		return p->val;
	else // rank > p->lson->size + p->size
		return getkth(rank - ssize(p->lson) - p->cnt, p->rson);
}

int getprecessor(int val) {
	node* p = ROOT;
	int ans = -infinity;
	while (p != nullptr) {
		if (p->val < val)
			ans = max(ans, p->val);
		if (val <= p->val)
			p = p->lson;
		else // val > p->val
			p = p->rson;
	}
	return ans;
}

int getsuccessor(int val) {
	node* p = ROOT;
	int ans = infinity;
	while (p != nullptr) {
		if (p->val > val)
			ans = min(ans, p->val);
		if (val < p->val)
			p = p->lson;
		else // val >= p->val
			p = p->rson;
	}
	return ans;
}

int n;
int k, x;

int main(int argc, char* argv[]) {
	overroot = ALLOCATE;

	read(n);
	for (int i = 1; i <= n; i++) {
		read(k, x);
		if (k == 1)
			insert(x);
		else if (k == 2)
			erase(x);
		else if (k == 3)
			printf("%d\n", getrank(x));
		else if (k == 4)
			printf("%d\n", getkth(x));
		else if (k == 5)
			printf("%d\n", getprecessor(x));
		else if (k == 6)
			printf("%d\n", getsuccessor(x));
		if (wantSplayNode != nullptr) {
			splay(wantSplayNode);
			wantSplayNode = nullptr;
		}
	}

	return 0;
}

#endif

