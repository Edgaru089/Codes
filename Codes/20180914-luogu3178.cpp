/*
 DOCUMENT NAME "20180914-luogu3178.cpp"
 CREATION DATE 2018-09-14
 SIGNATURE CODE_20180914_LUOGU3178
 COMMENT P3178 [HAOI2015]树上操作 / 树链剖分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180914_LUOGU3178

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;
constexpr int MaxN = 100000 + 10, MaxM = 100000 + 10;

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

int n, m;
ll d[MaxN];

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

namespace segtree {
	struct node {
		int left, right;
		ll sum, lazy;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(ll* d = ::d, int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		p->lazy = 0;
		if (left == right) {
			p->lson = p->rson = nullptr;
			p->sum = d[left];
		}
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
		if (p->lazy != 0) {
			p->sum += p->lazy*(p->right - p->left + 1);
			if (p->lson != nullptr)
				p->lson->lazy += p->lazy;
			if (p->rson != nullptr)
				p->rson->lazy += p->lazy;
			p->lazy = 0;
		}
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

	void addseg(int left, int right, ll val, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazy += val;
			return;
		}
		if (p->lson->right >= right)
			addseg(left, right, val, p->lson);
		else if (p->rson->left <= left)
			addseg(left, right, val, p->rson);
		else {
			addseg(left, p->lson->right, val, p->lson);
			addseg(p->rson->left, right, val, p->rson);
		}
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}

	void addpnt(int id, ll val, node* p = root) {
		pushdown(p);
		if (p->left == p->right&&p->right == id) {
			p->sum += val;
			return;
		}
		if (p->lson->right >= id)
			addpnt(id, val, p->lson);
		else /* p->rson->left <= id */
			addpnt(id, val, p->rson);
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}
}

int dep[MaxN], ssize[MaxN], father[MaxN], heavy[MaxN];
void dfs1(int u, int from = 0, int step = 1) {
	ssize[u] = 1;
	father[u] = from;
	dep[u] = step;
	int heavysize = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs1(v, u, step + 1);
			ssize[u] += ssize[v];
			if (heavysize < ssize[v]) {
				heavysize = ssize[v];
				heavy[u] = v;
			}
		}
	}
}

int sstime, dfn[MaxN];
int top[MaxN];
void dfs2(int u, int t) {
	dfn[u] = ++sstime;
	top[u] = t;
	if (heavy[u] != 0)
		dfs2(heavy[u], t);
	for (node* p = h[u]; p != nullptr; p = p->next) {
		if (p->v != father[u] && p->v != heavy[u])
			dfs2(p->v, p->v);
	}
}

ll dfnd[MaxN];
void build(int root) {
	dfs1(root);
	dfs2(root, root);
	for (int i = 1; i <= n; i++)
		dfnd[dfn[i]] = d[i];
	segtree::build(dfnd);
}

void addpnt(int id, ll val) {
	segtree::addpnt(dfn[id], val);
}

void addsubtree(int id, ll val) {
	segtree::addseg(dfn[id], dfn[id] + ssize[id] - 1, val);
}

ll queryroute(int id) {
	ll ans = 0;
	while (id != 0) {
		ans += segtree::query(dfn[top[id]], dfn[id]);
		id = father[top[id]];
	}
	return ans;
}




int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		read(u, v);
		addedge(u, v);
	}

	build(1);

	for (int i = 1; i <= m; i++) {
		int k, x, a;
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
			printf("%lld\n", queryroute(x));
		}
	}

	return 0;
}

#endif

