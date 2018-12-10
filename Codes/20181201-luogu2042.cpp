/*
 DOCUMENT NAME "20181201-luogu2042.cpp"
 CREATION DATE 2018-12-01
 SIGNATURE CODE_20181201_LUOGU2042
 COMMENT [NOI2005] Î¬»¤ÊýÁÐ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181201_LUOGU2042

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <stack>
#include <algorithm>
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

template<>
void read<string>(string& str) {
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
}

typedef long long ll;

const int infinity = 1e8;
const int MaxN = 4000000 + 10, MaxM = 20000 + 10;

int n, m;
ll d[MaxN];

int tot;
ll c[MaxN];

struct node {
	ll val, max, sum;
	int size;
	int lazyset;
	bool lazyswap;
	node* lson, *rson;
	node* father;
};

node* overroot;
#define ROOT (overroot->lson)
node mem[MaxN], *memtop = mem;

stack<node*> gc;

node* allocate() {
	node* p;
	if (!gc.empty()) {
		p = gc.top();
		gc.pop();
		memset(p, 0, sizeof(node));
	} else
		p = ++memtop;
	p->lazyset = -infinity;
	return p;
}

void recycle(node* p) {
	gc.push(p);
}

int ssize(node* p) {
	if (p)
		return p->size;
	else
		return 0;
}

ll ssum(node* p) {
	if (p)
		return p->sum;
	else
		return 0;
}

ll smax(node* p) {
	if (p)
		return p->max;
	else
		return 0;
}

void pushdown(node* p) {
	if (!p)
		return;
	if (p->lazyset != -infinity) {
		p->val = p->lazyset;
		if (p->lson)
			p->lson->lazyset = p->lazyset;
		if (p->rson)
			p->rson->lazyset = p->lazyset;
		p->sum = (ll)p->size*p->lazyset;
		p->max = max(0ll, p->sum);
		p->lazyset = -infinity;
	}
	if (p->lazyswap) {
		swap(p->lson, p->rson);
		if (p->lson)
			p->lson->lazyswap = !p->lson->lazyswap;
		if (p->rson)
			p->rson->lazyswap = !p->rson->lazyswap;
		p->lazyswap = false;
	}
}

void update(node* p) {
	if (p) {
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = p->val + ssum(p->lson) + ssum(p->rson);
		p->max = max(0ll, p->val);
		p->max = max(p->max, smax(p->lson));
		p->max = max(p->max, smax(p->rson));
		p->max = max(p->max, smax(p->lson) + p->val);
		p->max = max(p->max, smax(p->rson) + p->val);
		p->max = max(p->max, smax(p->lson) + smax(p->rson));
		p->max = max(p->max, smax(p->lson) + p->val + smax(p->rson));
		p->size = ssize(p->lson) + ssize(p->rson) + 1;
	}
}

typedef unsigned char sontype;
const sontype lson = 0, rson = 1;
sontype tell(node* p) { return p->father&&p->father->lson == p ? lson : rson; }
node*& get(node* father, sontype type) { return type == lson ? father->lson : father->rson; }
void connect(node* father, node* son, sontype type) {
	if (father)
		get(father, type) = son;
	if (son)
		son->father = father;
}

void rotate(node* p) {
	sontype t = tell(p);
	node* fa = p->father, *b = get(p, 1 - t);
	connect(fa->father, p, tell(fa));
	connect(p, fa, 1 - t);
	connect(fa, b, t);
	update(fa);
	update(p);
}

void pushchain(node* p, node* target) {
	if (p->father != target)
		pushchain(p->father, target);
	pushdown(p);
}

void splay(node* p, node* target) {
	pushchain(p, target);
	while (p->father != target) {
		if (p->father->father != target)
			if (tell(p) == tell(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}


void build(int left = 1, int right = n, node*& p = ROOT, node* fa = overroot) {
	if (left > right)
		return;
	int mid = (left + right) / 2;
	p = allocate();
	p->val = d[mid];
	p->father = fa;
	build(left, mid - 1, p->lson, p);
	build(mid + 1, right, p->rson, p);
	update(p);
}

node* getkth(int k, node* p = ROOT) {
	pushdown(p);
	if (ssize(p->lson) >= k)
		return getkth(k, p->lson);
	else if (k == ssize(p->lson) + 1)
		return p;
	else
		return getkth(k - ssize(p->lson) - 1, p->rson);
}

node* makeseq(int l = 1, int r = tot, node* fa = 0, ll c[] = ::c) {
	if (l > r)
		return 0;
	int mid = (l + r) / 2;
	node* p = allocate();
	p->val = c[mid];
	p->father = fa;
	p->lson = makeseq(l, mid - 1, p, c);
	p->rson = makeseq(mid + 1, r, p, c);
	update(p);
	return p;
}

void _insert(node*& target, sontype from, node* p) {
	if (!target)
		connect(target->father, p, from);
	else {
		_insert(target->lson, lson, p);
		update(target);
	}
}

void insertafter(int kth, int tot, ll c[]) {
	node* after = getkth(kth + 1);
	_insert(after->rson, rson, makeseq(1, tot, 0, c));
	while (after) {
		update(after);
		after = after->father;
	}
}

void _destroysubtree(node* p) {
	if (!p)
		return;
	_destroysubtree(p->lson);
	_destroysubtree(p->rson);
	gc.push(p);
}

void deletesequence(int begin, int len) {
	node* l = getkth(begin), *r = getkth(begin + len + 1);
	splay(l, overroot);
	splay(r, l);
	_destroysubtree(r->lson);
	r->lson = 0;
	update(r);
	update(l);
}

void makesame(int begin, int len, int val) {
	node* l = getkth(begin), *r = getkth(begin + len + 1);
	splay(l, overroot);
	splay(r, l);
	r->lson->lazyset = val;
	pushdown(r->lson);
	update(r);
	update(l);
}

void reverse(int begin, int len) {
	node* l = getkth(begin), *r = getkth(begin + len + 1);
	splay(l, overroot);
	splay(r, l);
	r->lson->lazyswap = true;
}

ll getsum(int begin, int len) {
	node* l = getkth(begin), *r = getkth(begin + len + 1);
	splay(l, overroot);
	splay(r, l);
	pushdown(r->lson);
	return r->lson->sum;
}

ll maxsum() {
	return ROOT->max;
}



int main(int argc, char* argv[]) {

	read(n); read(m);

	overroot = allocate();

	n += 2;
	d[1] = d[n] = 0;
	for (int i = 2; i <= n - 1; i++) {
		read(d[i]);
	}

	build();

	string command;
	for (int i = 1; i <= m; i++) {
		read(command);
		if (command[0] == 'I') { // INSERT
			int pos;
			read(pos);
			read(tot);
			for (int i = 1; i <= tot; i++)
				read(c[i]);
			insertafter(pos, tot, c);
		} else if (command[0] == 'D') { // DELETE
			int pos, tot;
			read(pos);
			read(tot);
			deletesequence(pos, tot);
		} else if (command[0] == 'M'&&command[2] == 'K') { // MAKE-SAME
			int pos, len, c;
			read(pos);
			read(len);
			read(c);
			makesame(pos, len, c);
		} else if (command[0] == 'R') { // REVERSE
			int pos, len;
			read(pos);
			read(len);
			reverse(pos, len);
		} else if (command[0] == 'G') { // GET-SUM
			int pos, len;
			read(pos);
			read(len);
			printf("%lld\n", getsum(pos, len));
		} else { // MAX-SUM
			printf("%lld\n", maxsum());
		}
	}


	return 0;
}

#endif

