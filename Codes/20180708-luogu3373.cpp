/*
DOCUMENT NAME "20180708-luogu3373.cpp"
CREATION DATE 2018-07-08
SIGNATURE CODE_20180708_LUOGU3373
COMMENT ¡¾Ä£°å¡¿Ïß¶ÎÊ÷ 2
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180708_LUOGU3373

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

typedef long long ll;

const int MaxN = 100000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 3) + (val << 1) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

template<typename IntType>
IntType read(IntType& x) { return x = read<IntType>(); }


struct node {
	ll sum;
	ll lazyadd, lazymult;
	int left, right;
	node* lson, *rson;
};

int n, m;
ll Mod;
ll d[MaxN];

node* root;
node mem[MaxN * 2], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->lazyadd = 0;
	p->lazymult = 1;
	p->lson = p->rson = nullptr;
	if (left == right)
		p->sum = d[left];
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->sum = (p->lson->sum + p->rson->sum) % Mod;
	}
}

void pushdown(node* p) {
	if (p == nullptr)
		return;
	if (p->lazyadd == 0 && p->lazymult == 1)
		return;
	p->sum = (p->sum*p->lazymult + p->lazyadd*(p->right - p->left + 1)) % Mod;
	if (p->lson != nullptr) {
		p->lson->lazyadd = (p->lson->lazyadd*p->lazymult + p->lazyadd) % Mod;
		p->lson->lazymult *= p->lazymult;
		p->lson->lazymult %= Mod;
	}
	if (p->rson != nullptr) {
		p->rson->lazyadd = (p->rson->lazyadd*p->lazymult + p->lazyadd) % Mod;
		p->rson->lazymult *= p->lazymult;
		p->rson->lazymult %= Mod;
	}
	p->lazyadd = 0;
	p->lazymult = 1;
}

void multply(int left, int right, ll val, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazyadd *= val;
		p->lazymult *= val;
		p->lazyadd %= Mod;
		p->lazymult %= Mod;
		return;
	}
	if (p->lson->right >= right)
		multply(left, right, val, p->lson);
	else if (p->rson->left <= left)
		multply(left, right, val, p->rson);
	else {
		multply(left, p->lson->right, val, p->lson);
		multply(p->rson->left, right, val, p->rson);
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	p->sum = (p->lson->sum + p->rson->sum) % Mod;
}

void add(int left, int right, ll val, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazyadd += val;
		p->lazyadd %= Mod;
		return;
	}
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
	p->sum = (p->lson->sum + p->rson->sum) % Mod;
}

ll query(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->sum;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return (query(left, p->lson->right, p->lson) + query(p->rson->left, right, p->rson)) % Mod;
}


int main(int argc, char* argv[]) {

	read(n); read(m); read(Mod);
	for (int i = 1; i <= n; i++) {
		read(d[i]);
		d[i] %= Mod;
	}
	build();
	int op;
	int x, y;
	ll k;
	for (int i = 1; i <= m; i++) {
		read(op);
		if (op == 1) {
			read(x); read(y); read(k);
			multply(x, y, k%Mod);
		}
		else if (op == 2) {
			read(x); read(y); read(k);
			add(x, y, k%Mod);
		}
		else if (op == 3) {
			read(x); read(y);
			printf("%lld\n", query(x, y));
		}
	}

	return 0;
}

#endif

