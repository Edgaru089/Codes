/*
DOCUMENT NAME "20180805-luogu3178.cpp"
CREATION DATE 2018-08-05
SIGNATURE CODE_20180805_LUOGU3178
COMMENT [HAOI2015]树上操作 / 树链剖分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180805_LUOGU3178

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;

#define ALLOCATE (++memtop)

constexpr int MaxN = 100000 + 10, MaxM = 100000 + 10;
constexpr ll infininty = 1e14;

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;
ll d[MaxN];

namespace graph {
	struct node {
		int v;
		node* next;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;

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

namespace segtree {
	struct node {
		ll sum, lazy;
		int left, right;
		node* lson, *rson;
	};

	node* root;
	node mem[3 * MaxN], *memtop = mem;

	void build(ll d[], int left, int right, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->sum = d[left];
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->sum = p->lson->sum + p->rson->sum;
		}
	}

	void pushdown(node* p) {
		if (p == nullptr)
			return;
		if (p->lazy == 0)
			return;
		p->sum += p->lazy*(p->right - p->left + 1);
		if (p->lson != nullptr)
			p->lson->lazy += p->lazy;
		if (p->rson != nullptr)
			p->rson->lazy += p->lazy;
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
					query(p->rson->left, right, p->rson));
	}

	void add(int left, int right, ll val, node* p = root) {
		pushdown(p);
		pushdown(p->lson);
		pushdown(p->rson);
		if (p->left == left && p->right == right) {
			p->lazy += val;
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
		p->sum = p->lson->sum + p->rson->sum;
	}
}


namespace hld {
	using namespace graph;

	int father[MaxN], size[MaxN], heavy[MaxN];
	int dfn[MaxN], stime, top[MaxN];
	ll dfnd[MaxN];

	void dfs1(int u = 1, int fa = 0) {
		if (size[u] != 0)
			return;
		father[u] = fa;
		size[u] = 1;
		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != fa) {
				dfs1(v, u);
				size[u] += size[v];
				if (size[v] > maxsize) {
					maxsize = size[v];
					maxid = v;
				}
			}
		}
		heavy[u] = maxid;
	}

	void dfs2(int u = 1, int top = 1) {
		dfn[u] = ++stime;
		hld::top[u] = top;
		if (heavy[u] != 0)
			dfs2(heavy[u], top);
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u] && v != heavy[u])
				dfs2(v, v);
		}
	}

	void build() {
		dfs1();
		dfs2();
		for (int i = 1; i <= n; i++)
			dfnd[dfn[i]] = d[i];
		segtree::build(dfnd, 1, n);
	}

	void addpnt(int id, ll val) {
		segtree::add(dfn[id], dfn[id], val);
	}

	void addsubtree(int id, ll val) {
		segtree::add(dfn[id], dfn[id] + size[id] - 1, val);
	}

	ll query(int u) {
		ll ans = 0;
		while (u != 0) {
			ans += segtree::query(dfn[top[u]], dfn[u]);
			u = father[top[u]];
		}
		return ans;
	}
}


int main(int argc, char* argv[]) {
	using namespace graph;
	using namespace hld;

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	for (int i = 1; i <= n - 1; i++)
		addedge(read(), read());

	build();

	for (int i = 1; i <= m; i++) {
		int k, x;
		ll a;
		read(k);
		if (k == 1) {
			read(x, a);
			addpnt(x, a);
		}
		else if (k == 2) {
			read(x, a);
			addsubtree(x, a);
		}
		else if (k == 3) {
			read(x);
			printf("%lld\n", query(x));
		}
	}

	return 0;
}

#endif

