/*
DOCUMENT NAME "20180816-bnds0782.cpp"
CREATION DATE 2018-08-16
SIGNATURE CODE_20180816_BNDS0782
COMMENT [模板]树链剖分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180816_BNDS0782

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 1e5 + 10;
#define ALLOCATE (++memtop)

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, root, mod;
int d[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;

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


namespace segtree {
	struct node {
		int sum, lazy;
		int left, right;
		node* lson, *rson;
	};

	node* root;
	node mem[3 * MaxN], *memtop = mem;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->sum = d[left] % mod;
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->sum = (p->lson->sum + p->rson->sum) % mod;
		}
	}

	void pushdown(node* p) {
		if (p->lazy == 0)
			return;
		p->sum = (p->sum + (long long)p->lazy*(p->right - p->left + 1) % mod) % mod;
		if (p->lson != nullptr)
			p->lson->lazy = (p->lson->lazy + p->lazy) % mod;
		if (p->rson != nullptr)
			p->rson->lazy = (p->rson->lazy + p->lazy) % mod;
		p->lazy = 0;
	}

	void add(int left, int right, int val, node* p = root) {
		if (p->left == left && p->right == right) {
			p->lazy = (p->lazy + val) % mod;
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
					query(p->rson->left, right, p->rson)) % mod;
	}
}


int ssize[MaxN], father[MaxN], dep[MaxN], heavy[MaxN];
void dfs1(int u = root, int from = 0, int step = 1) {
	father[u] = from;
	ssize[u] = 1;
	dep[u] = step;
	int maxsize = 0, maxid = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs1(v, u, step + 1);
			ssize[u] += ssize[v];
			if (ssize[v] > maxsize) {
				maxsize = ssize[v];
				maxid = v;
			}
		}
	}
	heavy[u] = maxid;
}

int dfn[MaxN], sstime, top[MaxN];
void dfs2(int u = root, int t = root) {
	dfn[u] = ++sstime;
	top[u] = t;
	if (heavy[u] != 0)
		dfs2(heavy[u], t);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavy[u])
			dfs2(v, v);
	}
}

int ddfn[MaxN];
void build() {
	dfs1();
	dfs2();
	for (int i = 1; i <= n; i++)
		ddfn[dfn[i]] = d[i] % mod;
	segtree::build(ddfn);
}

void addlca(int u, int v, int val) {
	val %= mod;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		segtree::add(dfn[top[u]], dfn[u], val);
		u = father[top[u]];
	}
	if (dep[u] > dep[v])
		segtree::add(dfn[dep[v]], dfn[dep[u]], val);
	else
		segtree::add(dfn[dep[u]], dfn[dep[v]], val);
}

int querylca(int u, int v) {
	int sum = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		sum += segtree::query(dfn[top[u]], dfn[u]);
		sum %= mod;
		u = father[top[u]];
	}
	if (dep[u] > dep[v])
		sum += segtree::query(dfn[dep[v]], dfn[dep[u]]);
	else
		sum += segtree::query(dfn[dep[u]], dfn[dep[v]]);
	return sum % mod;
}

void addsubtree(int u, int val) {
	segtree::add(dfn[u], dfn[u] + ssize[u] - 1, val%mod);
}

int querysubtree(int u) {
	return segtree::query(dfn[u], dfn[u] + ssize[u] - 1)%mod;
}

int m;
int k, x, y, z;

int main(int argc, char* argv[]) {

	read(n, m, root, mod);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());
	build();
	for (int i = 1; i <= m; i++) {
		read(k);
		if (k == 1) {
			read(x, y, z);
			addlca(x, y, z);
		}
		else if (k == 2) {
			read(x, y);
			printf("%d\n", querylca(x, y));
		}
		else if (k == 3) {
			read(x, z);
			addsubtree(x, z);
		}
		else if (k == 4) {
			read(x);
			printf("%d\n", querysubtree(x));
		}
	}

	return 0;
}

#endif

