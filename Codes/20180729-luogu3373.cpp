/*
DOCUMENT NAME "20180729-luogu3373.cpp"
CREATION DATE 2018-07-29
SIGNATURE CODE_20180729_LUOGU3373
COMMENT ¡¾Ä£°å¡¿Ïß¶ÎÊ÷ 2
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180729_LUOGU3373

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;

constexpr int MaxN = 100000 + 10, MaxM = 100000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }


int n, m;
ll mod;
ll d[MaxN];

struct node {
	ll sum;
	ll lazyadd, lazymul;
	int left, right;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->lazyadd = 0;
	p->lazymul = 1;
	if (left == right)
		p->sum = d[left];
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->sum = (p->lson->sum + p->rson->sum) % mod;
	}
}

void pushdown(node* p) {
	if (p == nullptr)
		return;
	if (p->lazyadd == 0 && p->lazymul == 1)
		return;
	p->sum = (p->sum*p->lazymul + p->lazyadd*(p->right - p->left + 1)) % mod;
	if (p->lson != nullptr) {
		p->lson->lazyadd = (p->lson->lazyadd*p->lazymul + p->lazyadd) % mod;
		p->lson->lazymul *= p->lazymul;
		p->lson->lazymul %= mod;
	}
	if (p->rson != nullptr) {
		p->rson->lazyadd = (p->rson->lazyadd*p->lazymul + p->lazyadd) % mod;
		p->rson->lazymul *= p->lazymul;
		p->rson->lazymul %= mod;
	}
	p->lazyadd = 0;
	p->lazymul = 1;
}

void multiply(int left, int right, ll val, node* p = root) {
	if (p->left == left && p->right == right) {
		p->lazyadd *= val;
		p->lazymul *= val;
		p->lazyadd %= mod;
		p->lazymul %= mod;
		return;
	}
	pushdown(p);
	if (p->lson->right >= right)
		multiply(left, right, val, p->lson);
	else if (p->rson->left <= left)
		multiply(left, right, val, p->rson);
	else {
		multiply(left, p->lson->right, val, p->lson);
		multiply(p->rson->left, right, val, p->rson);
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	p->sum = (p->lson->sum + p->rson->sum) % mod;
}

void add(int left, int right, ll val, node* p = root) {
	if (p->left == left && p->right == right) {
		p->lazyadd += val;
		p->lazyadd %= mod;
		return;
	}
	pushdown(p);
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
	p->sum = (p->lson->sum + p->rson->sum) % mod;
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
		return (query(left, p->lson->right, p->lson) +
				query(p->rson->left, right, p->rson)) % mod;
}



int main(int argc, char* argv[]) {

	read(n, m, mod);
	for (int i = 1; i <= n; i++)
		read(d[i]);

	build();

	int o, x, y;
	ll k;
	for (int i = 1; i <= m; i++) {
		read(o);
		if (o == 1) {
			read(x, y, k);
			multiply(x, y, k%mod);
		}
		else if (o == 2) {
			read(x, y, k);
			add(x, y, k%mod);
		}
		else if (o == 3) {
			read(x, y);
			printf("%lld\n", query(x, y));
		}
	}

	return 0;
}

#endif

