/*
DOCUMENT NAME "20180704-luogu3369.cpp"
CREATION DATE 2018-07-04
SIGNATURE CODE_20180704_LUOGU3369
COMMENT ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / Splay
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180704_LUOGU3369

#define SPLAY_ON_INSERT
#define SPLAY_ON_ERASE
#define SPLAY_ON_FIND_KTH_VAL

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 100000 + 10;

int read() {
	char c;
	int val = 0;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

int read(int& x) { return x = read(); }


struct node {
	int val, valcnt;
	int size;
	node* lson, *rson;
	node* father;
};

node mem[MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

node* overroot;
#define ROOT (overroot->lson)

typedef int Type;
const int Left = 0, Right = 1;
node*& getson(node* father, Type type) { return (type == Left) ? father->lson : father->rson; }
Type sontype(node* son) { return (son->father->lson == son) ? Left : Right; }
void connect(node* father, node* son, Type sontype) {
	getson(father, sontype) = son;
	if (son != nullptr)
		son->father = father;
}

int size(node* p) { return (p == nullptr) ? 0 : p->size; }
void update(node* p) {
	p->size = size(p->lson) + size(p->rson) + p->valcnt;
}

void rotate(node* p) {
	Type t = sontype(p), fatype = sontype(p->father);
	node* fa = p->father, *grand = p->father->father, *b = getson(p, 1 - t);
	if (grand != nullptr)
		connect(grand, p, fatype);
	connect(p, fa, 1 - t);
	connect(fa, b, t);
	update(fa);
	update(p);
}

void splay(node* p, node* target = overroot) {
	while (p->father != target && p->father->father != target) {
		if (sontype(p) == sontype(p->father))
			rotate(p->father);
		else
			rotate(p);
		rotate(p);
	}
	if (p->father->father == target)
		rotate(p);
}

node* _insert(int val, node*& p = ROOT, node* fa = overroot) {
	if (p == nullptr) {
		p = ALLOCATE;
		p->val = val;
		p->valcnt = 1;
		p->lson = p->rson = nullptr;
		p->size = 1;
		p->father = fa;
		return p;
	}
	else {
		node* ret = nullptr;
		if (val < p->val)
			ret = _insert(val, p->lson, p);
		else if (val == p->val) {
			p->valcnt++;
			ret = p;
		}
		else if (val > p->val)
			ret = _insert(val, p->rson, p);
		update(p);
		return ret;
	}
}

void insert(int val) {
	node* p = _insert(val);
#ifdef SPLAY_ON_INSERT
	splay(p);
#endif
}

node* findval(int val, node* p = ROOT) {
	if (val < p->val)
		return findval(val, p->lson);
	else if (val == p->val)
		return p;
	else if (val > p->val)
		return findval(val, p->rson);
	else
		return nullptr; // never executes
}

//void erase(int val) {
//	node* p = findval(val);
//	p->valcnt--;
//	if (p->valcnt == 0) {
//		while (p->lson != nullptr || p->rson != nullptr) {
//			if (p->lson != nullptr)
//				rotate(p->lson);
//			else if (p->rson != nullptr)
//				rotate(p->rson);
//		}
//		Type t = sontype(p);
//		node* fa = p->father;
//		getson(fa, t) = nullptr;
//#ifdef SPLAY_ON_ERASE
//		splay(fa);
//#endif
//	}
//	else {
//#ifdef SPLAY_ON_ERASE
//		splay(p);
//#endif
//	}
//}

node* _getkth(int k, node* p = ROOT) {
	if (size(p->lson) >= k)
		return _getkth(k, p->lson);
	else if (size(p->lson) < k&&k <= size(p->lson) + p->valcnt)
		return p;
	else if (k > size(p->lson) + p->valcnt)
		return _getkth(k - size(p->lson) - p->valcnt, p->rson);
	else
		return nullptr; // never executes
}

int getkth(int k) {
	node* p = _getkth(k);
	int val = p->val;
#ifdef SPLAY_ON_FIND_KTH_VAL
	splay(p);
#endif
	return val;
}

void erase(int val) {
	node* p = findval(val);
	p->valcnt--;
	splay(p);
	if (p->valcnt == 0) {
		if (p->lson == nullptr) {
			connect(overroot, p->rson, Left);
		}
		else {
			node* nr = p->lson;
			while (nr->rson != nullptr)
				nr = nr->rson;
			splay(nr, p);
			connect(nr, p->rson, Right);
			connect(overroot, nr, Left);
			update(nr);
		}
	}
}

pair<int, node*> getrank(int val, node* p = ROOT) {
	if (p == nullptr)
		return make_pair(1, nullptr);
	else if (val < p->val)
		return getrank(val, p->lson);
	else if (val == p->val)
		return make_pair(size(p->lson) + 1, p);
	else if (val > p->val) {
		auto ans = getrank(val, p->rson);
		return make_pair(ans.first + size(p->lson) + p->valcnt, ans.second);
	}
	else
		return make_pair(0, nullptr); // never executes
}

int n;
int opt, x;

int main(int argc, char* argv[]) {

	overroot = ALLOCATE;

	read(n);
	for (int i = 1; i <= n; i++) {
		read(opt); read(x);
		if (opt == 1)
			insert(x);
		else if (opt == 2)
			erase(x);
		else if (opt == 3)
			printf("%d\n", getrank(x).first);
		else if (opt == 4)
			printf("%d\n", getkth(x));
		else if (opt == 5)
			printf("%d\n", getkth(getrank(x).first - 1));
		else if (opt == 6) {
			auto ans = getrank(x);
			int l = ans.first;
			if (ans.second != nullptr)
				l += ans.second->valcnt;
			printf("%d\n", getkth(l));
		}
	}

	return 0;
}

#endif

