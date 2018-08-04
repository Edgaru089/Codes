/*
DOCUMENT NAME "20180727-luogu3865.cpp"
CREATION DATE 2018-07-27
SIGNATURE CODE_20180727_LUOGU3865
COMMENT 【模板】ST表 / 线段树水掉
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180727_LUOGU3865

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

constexpr int MaxN = 1e5 + 10, MaxM = 1e6 + 10;

constexpr int buffersize = 100 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	return ans;
}

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

int n, m;
int d[MaxN];
int l, r;

struct node {
	int max;
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
	if (left == right) {
		p->max = d[left];
	}
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->max = max(p->lson->max, p->rson->max);
	}
}

int query(int left, int right, node* p = root) {
	if (p->left == left && p->right == right) {
		return p->max;
	}
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return max(query(left, p->lson->right, p->lson),
				   query(p->rson->left, right, p->rson));
}



int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	build();
	for (int i = 1; i <= m; i++) {
		read(l, r);
		printf("%d\n", query(l, r));
	}

	return 0;
}

#endif

