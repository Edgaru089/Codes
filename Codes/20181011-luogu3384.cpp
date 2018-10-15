/*
 DOCUMENT NAME "20181011-luogu3384.cpp"
 CREATION DATE 2018-10-11
 SIGNATURE CODE_20181011_LUOGU3384
 COMMENT ¡¾Ä£°å¡¿Ê÷Á´ÆÊ·Ö
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181011_LUOGU3384

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

const int MaxN = 1e5 + 10, MaxM = 1e5 + 10;

void read(int& val) {
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

int n, m, r, p;
int d[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}

int dep[MaxN], ssize[MaxN], father[MaxN], heavy[MaxN];
void dfs1(int u, int step, int from) {
	dep[u] = step;
	ssize[u] = 1;
	father[u] = from;
	int maxsize = 0;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs1(v, step + 1, u);
			ssize[u] += ssize[v];
			if (maxsize < ssize[v]) {
				maxsize = ssize[v];
				heavy[u] = v;
			}
		}
	}
}

int dfn[MaxN], top[MaxN], sstime;
void dfs2(int u, int t) {
	dfn[u] = ++sstime;
	top[u] = t;
	if (heavy[u])
		dfs2(heavy[u], t);
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavy[u])
			dfs2(v, v);
	}
}


namespace segtree {
	struct node {
		int left, right;
		int sum, lazy;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->sum = d[left];
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->sum = (p->lson->sum + p->rson->sum) % ::p;
		}
	}

	void pushdown(node* p) {
		if (p&&p->lazy) {
			p->sum += (p->right - p->left + 1)*p->lazy;
			p->sum %= ::p;
			if (p->lson)
				p->lson->lazy += p->lazy;
			if (p->rson)
				p->rson->lazy += p->lazy;
			p->lazy = 0;
		}
	}

	void add(int left, int right, int val, node* p = root) {
		assert(left <= right);
		assert(p->left <= left);
		assert(p->right >= right);
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazy += val;
			p->lazy %= ::p;
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
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = (p->lson->sum + p->rson->sum) % ::p;
	}

	int query(int left, int right, node* p = root) {
		assert(left <= right);
		assert(p->left <= left);
		assert(p->right >= right);
		pushdown(p);
		if (p->left == left && p->right == right)
			return p->sum;
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return (query(left, p->lson->right, p->lson) +
					query(p->rson->left, right, p->rson)) % ::p;
	}
}

int dfnd[MaxN];
void build() {
	dfs1(r, 1, 0);
	dfs2(r, r);
	for (int i = 1; i <= n; i++)
		dfnd[dfn[i]] = d[i];
	segtree::build(dfnd);
}

void addchain(int u, int v, int val) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			segtree::add(dfn[top[u]], dfn[u], val);
			u = father[top[u]];
		} else {
			segtree::add(dfn[top[v]], dfn[v], val);
			v = father[top[v]];
		}
	}
	segtree::add(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), val);
}

int querychain(int u, int v) {
	int sum = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			sum += segtree::query(dfn[top[u]], dfn[u]);
			sum %= p;
			u = father[top[u]];
		} else {
			sum += segtree::query(dfn[top[v]], dfn[v]);
			sum %= p;
			v = father[top[v]];
		}
	}
	sum += segtree::query(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]));
	sum %= p;
	return sum;
}

void addsubtree(int u, int val) {
	segtree::add(dfn[u], dfn[u] + ssize[u] - 1, val);
}

int querysubtree(int u) {
	return segtree::query(dfn[u], dfn[u] + ssize[u] - 1);
}




int main(int argc, char* argv[]) {

	read(n); read(m); read(r); read(p);
	for (int i = 1; i <= n; i++) {
		read(d[i]);
		d[i] %= p;
	}
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		read(u); read(v);
		addedge(u, v);
	}

	build();

	int k, x, y, z;
	for (int i = 1; i <= m; i++) {
		read(k);
		switch (k) {
			case 1:
				read(x); read(y); read(z);
				addchain(x, y, z);
				break;
			case 2:
				read(x); read(y);
				printf("%d\n", querychain(x, y));
				break;
			case 3:
				read(x); read(z);
				addsubtree(x, z);
				break;
			case 4:
				read(x);
				printf("%d\n", querysubtree(x));
				break;
		}
	}


	return 0;
}

#endif

