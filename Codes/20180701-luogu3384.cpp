/*
DOCUMENT NAME "20180701-luogu3384.cpp"
CREATION DATE 2018-07-01
SIGNATURE CODE_20180701_LUOGU3384
COMMENT ¡¾Ä£°å¡¿Ê÷Á´ÆÊ·Ö
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180701_LUOGU3384

#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

const int infinity = 1e8;
const int MaxN = 100000 + 10, MaxM = 2 * MaxN + 10;

int n, m;
int mod;

ll d[MaxN];

namespace SegmentTree {

	struct node {
		int left, right;
		long long sum;
		long long lazy;
		node* lson, *rson;
	};

	node mem[200050];
	int top;
	node* root;

	node* allocate() { return &mem[++top]; }


	void _build(long long d[], node*& p, int left, int right) {
		p = allocate();
		p->left = left;
		p->right = right;
		p->lazy = 0;
		if (left == right) {
			p->sum = d[left];
			p->lson = p->rson = nullptr;
		}
		else {
			int mid = (left + right) / 2;
			_build(d, p->lson, left, mid);
			_build(d, p->rson, mid + 1, right);
			p->sum = p->lson->sum + p->rson->sum;
		}
	}

	void pushDown(node* p) {
		if (p == nullptr)
			return;
		if (p->lazy == 0)
			return;
		p->sum += p->lazy*(p->right - p->left + 1);
		p->sum %= mod;
		if (p->lson != nullptr) {
			p->lson->lazy += p->lazy;
			p->lson->lazy %= mod;
		}
		if (p->rson != nullptr) {
			p->rson->lazy += p->lazy;
			p->rson->lazy %= mod;
		}
		p->lazy = 0;
	}

	void _add(int left, int right, long long val, node* p) {
		pushDown(p);
		if (p->left == left && p->right == right) {
			p->lazy += val;
			return;
		}
		if (p->lson->right >= right)
			_add(left, right, val, p->lson);
		else if (p->rson->left <= left)
			_add(left, right, val, p->rson);
		else {
			_add(left, p->lson->right, val, p->lson);
			_add(p->rson->left, right, val, p->rson);
		}
		pushDown(p);
		pushDown(p->lson);
		pushDown(p->rson);
		p->sum = (p->lson->sum + p->rson->sum) % mod;
	}

	long long _query(int left, int right, node* p) {
		pushDown(p);
		pushDown(p->lson);
		pushDown(p->rson);
		if (p->left == left && p->right == right)
			return p->sum;
		if (p->lson->right >= right)
			return _query(left, right, p->lson);
		else if (p->rson->left <= left)
			return _query(left, right, p->rson);
		else
			return (_query(left, p->lson->right, p->lson) + _query(p->rson->left, right, p->rson)) % mod;
	}

	void build(long long d[], int n) {
		_build(d, root, 1, n);
	}

	void add(int left, int right, int val) {
		_add(left, right, val % mod, root);
	}

	long long query(int left, int right) {
		return _query(left, right, root) % mod;
	}
}

namespace Graph {
	struct node {
		int v;
		node* next;
	};

	node* h[MaxN];
	node mem[MaxN * 2], *top = mem;
#define ALLOCATE (++top)

	int root;
	int dep[MaxN], father[MaxN];
	int subsize[MaxN]; // Size of subtree

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

	void dfs(int u = root, int from = 0, int step = 1) {
		father[u] = from;
		dep[u] = step;
		subsize[u] = 1;
		for (node* p = h[u]; p != nullptr; p = p->next)
			if (dep[p->v] == 0) {
				dfs(p->v, u, step + 1);
				subsize[u] += subsize[p->v];
			}
	}
}

namespace Algorithm {
	using namespace Graph;

	int stime = 0;
	int dfn[MaxN], heavyson[MaxN];
	int top[MaxN];
	ll d2[MaxN];

	void _dfs1(int u = root) {
		if (u == 0)
			return;
		int maxsize = 0, maxid = 0;
		if (h[u]->next == nullptr&&u != root)
			return;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v == father[u])
				continue;
			if (maxsize < subsize[v]) {
				maxsize = subsize[v];
				maxid = v;
			}
		}
		heavyson[u] = maxid;
		for (node* p = h[u]; p != nullptr; p = p->next)
			if (p->v != father[u])
				_dfs1(p->v);
	}

	void _dfs2(int u = root, int mtop = root) {
		dfn[u] = ++stime;
		top[u] = mtop;
		if (h[u]->next == nullptr&&u != root)
			return;
		if (heavyson[u] != 0)
			_dfs2(heavyson[u], mtop);
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u] && v != heavyson[u])
				_dfs2(v, v);
		}
	}

	void build() {
		top[root] = root;
		_dfs1();
		_dfs2();
		for (int i = 1; i <= n; i++)
			d2[dfn[i]] = d[i];
		SegmentTree::build(d2, n);
	}

	void addSection(int x, int y, int val) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]])
				swap(x, y);
			SegmentTree::add(dfn[top[x]], dfn[x], val);
			x = father[top[x]];
		}
		if (dep[x] > dep[y])
			swap(x, y);
		SegmentTree::add(dfn[x], dfn[y], val);
	}

	ll querySection(int x, int y) {
		ll sum = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]])
				swap(x, y);
			sum += SegmentTree::query(dfn[top[x]], dfn[x]);
			sum %= mod;
			x = father[top[x]];
		}
		if (dep[x] > dep[x])
			swap(x, y);
		sum += SegmentTree::query(dfn[x], dfn[y]);
		return sum % mod;
	}

	void addSubtree(int r, int val) {
		SegmentTree::add(dfn[r], dfn[r] + subsize[r] - 1, val);
	}

	ll querySubtree(int t) {
		return SegmentTree::query(dfn[t], dfn[t] + subsize[t] - 1) % mod;
	}
}


int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	int r;
	cin >> n >> m >> r >> mod;
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	int u, v;
	for (int i = 1; i <= n - 1; i++) {
		cin >> u >> v;
		Graph::addedge(u, v);
	}

	Graph::root = r;
	Graph::dfs();
	Algorithm::build();

	int op, x, y, z;
	for (int i = 1; i <= m; i++) {
		cin >> op;
		if (op == 1) {
			cin >> x >> y >> z;
			Algorithm::addSection(x, y, z);
		}
		else if (op == 2) {
			cin >> x >> y;
			cout << Algorithm::querySection(x, y) << endl;
		}
		else if (op == 3) {
			cin >> x >> z;
			Algorithm::addSubtree(x, z);
		}
		else if (op == 4) {
			cin >> x;
			cout << Algorithm::querySubtree(x) << endl;
		}
	}

	return 0;
}

#endif

