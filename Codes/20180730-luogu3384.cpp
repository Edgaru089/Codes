/*
DOCUMENT NAME "20180730-luogu3384.cpp"
CREATION DATE 2018-07-30
SIGNATURE CODE_20180730_LUOGU3384
COMMENT ¡¾Ä£°å¡¿Ê÷Á´ÆÊ·Ö
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180730_LUOGU3384

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;

constexpr int MaxN = 1e5 + 10, MaxM = 1e5 + 10;

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
int r;
ll mod;
ll d[MaxN];


namespace graph {
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
}

namespace segmenttree {
	struct node {
		ll sum, lazy;
		int left, right;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int left, int right, ll d[], node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->sum = d[left] % mod;
		else {
			int mid = (left + right) / 2;
			build(left, mid, d, p->lson);
			build(mid + 1, right, d, p->rson);
			p->sum = (p->lson->sum + p->rson->sum) % mod;
		}
	}

	void pushdown(node* p) {
		if (p == nullptr)
			return;
		if (p->lazy == 0)
			return;
		p->sum += p->lazy*(p->right - p->left + 1) % mod;
		if (p->lson != nullptr)
			p->lson->lazy = (p->lson->lazy + p->lazy) % mod;
		if (p->rson != nullptr)
			p->rson->lazy = (p->rson->lazy + p->lazy) % mod;
		p->lazy = 0;
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

	void add(int left, int right, ll val, node* p = root) {
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
}

namespace hld {
	using namespace graph;
	int size[MaxN], dep[MaxN], father[MaxN], heavy[MaxN];
	int top[MaxN], dfn[MaxN], stime;
	ll dfnd[MaxN];

	void dfs1(int u = r, int from = 0, int step = 1) {
		father[u] = from;
		dep[u] = step;
		size[u] = 1;
		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u]) {
				dfs1(v, u, step + 1);
				size[u] += size[v];
				if (size[v] > maxsize) {
					maxsize = size[v];
					maxid = v;
				}
			}
		}
		heavy[u] = maxid;
	}

	void dfs2(int u = r, int t = r) {
		dfn[u] = ++stime;
		top[u] = t;
		if (heavy[u] != 0)
			dfs2(heavy[u], t);
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u] && v != heavy[u])
				dfs2(v, v);
		}
	}

	void setup() {
		dfs1();
		dfs2();
		for (int i = 1; i <= n; i++)
			dfnd[dfn[i]] = d[i];
		segmenttree::build(1, n, dfnd);
	}

	void addlca(int u, int v, ll val) {
		val %= mod;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]])
				swap(u, v);
			segmenttree::add(dfn[top[u]], dfn[u], val);
			u = father[top[u]];
		}
		if (dep[u] < dep[v])
			swap(u, v);
		segmenttree::add(dfn[v], dfn[u], val);
	}

	ll querylca(int u, int v) {
		ll sum = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]])
				swap(u, v);
			sum = (sum + segmenttree::query(dfn[top[u]], dfn[u])) % mod;
			u = father[top[u]];
		}
		if (dep[u] < dep[v])
			swap(u, v);
		sum = (sum + segmenttree::query(dfn[v], dfn[u])) % mod;
		return sum;
	}

	void addsubtree(int u, ll val) {
		segmenttree::add(dfn[u], dfn[u] + size[u] - 1, val%mod);
	}

	ll querysubtree(int u) {
		return segmenttree::query(dfn[u], dfn[u] + size[u] - 1);
	}
}



int main(int argc, char* argv[]) {
	using namespace graph;
	using namespace hld;

	read(n, m, r, mod);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	int u, v;
	for (int i = 1; i < n; i++) {
		read(u, v);
		addedge(u, v);
	}

	setup();

	int k, x, y;
	ll z;
	for (int i = 1; i <= m; i++) {
		read(k);
		if (k == 1) {
			read(x, y, z);
			addlca(x, y, z);
		}
		else if (k == 2) {
			read(x, y);
			printf("%lld\n", querylca(x, y) % mod);
		}
		else if (k == 3) {
			read(x, z);
			addsubtree(x, z);
		}
		else if (k == 4) {
			read(x);
			printf("%lld\n", querysubtree(x) % mod);
		}
	}

	return 0;
}

#endif

