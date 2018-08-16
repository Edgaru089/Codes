/*
DOCUMENT NAME "20180813-bnds0767.cpp"
CREATION DATE 2018-08-13
SIGNATURE CODE_20180813_BNDS0767
COMMENT 线段树模板1 - 区间加法+区间求和
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180813_BNDS0767

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 100000 + 10, Mod = 1000000007;

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

int n, m;
int d[MaxN];
int k, x, y, z;

struct node {
	int sum, lazy;
	int left, right;
	node* lson, *rson;
};

node* root;
node mem[4 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->sum = d[left] % Mod;
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->sum = (p->lson->sum + p->rson->sum) % Mod;
	}
}

void pushdown(node* p) {
	if (p->lazy == 0)
		return;
	p->sum = (p->sum + (long long)p->lazy*(p->right - p->left + 1) % Mod) % Mod;
	if (p->lson != nullptr)
		p->lson->lazy = (p->lson->lazy + p->lazy) % Mod;
	if (p->rson != nullptr)
		p->rson->lazy = (p->rson->lazy + p->lazy) % Mod;
	p->lazy = 0;
}

void add(int left, int right, int val, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right) {
		p->lazy = (p->lazy + val) % Mod;
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

int query(int left, int right, node* p = root) {
	pushdown(p);
	if (p->left == left && p->right == right)
		return p->sum;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return (query(left, p->lson->right, p->lson) +
				query(p->rson->left, right, p->rson)) % Mod;
}


int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);

	build();

	for (int i = 1; i <= m; i++) {
		read(k);
		if (k == 1) {
			read(x, y, k);
			add(x, y, k%Mod);
		}
		else if (k == 2) {
			read(x, y);
			printf("%d\n", query(x, y));
		}
	}

	return 0;
}

#endif

