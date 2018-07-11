/*
DOCUMENT NAME "20180710-luogu1967.cpp"
CREATION DATE 2018-07-10
SIGNATURE CODE_20180710_LUOGU1967
COMMENT 货车运输 / 最大生成树+树链剖分LCA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180710_LUOGU1967

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 10000 + 10, MaxM = 50000 + 10, MaxQ = 30000 + 10;

int n, m, q;


namespace Set {
	int p[MaxN];

	int Find(int x) {
		if (p[x] < 0)
			return x;
		else
			return p[x] = Find(p[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		p[x] += p[y];
		p[y] = x;
	}
}


namespace Graph {
	struct node {
		int v, len;
		node* next;
	};

	node* h[MaxN];
	node nodemem[MaxM * 2], *memtop = nodemem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, int len) {
		node* p = ALLOCATE;
		p->v = v;
		p->len = len;
		p->next = h[u];
		h[u] = p;
		p = ALLOCATE;
		p->v = u;
		p->len = len;
		p->next = h[v];
		h[v] = p;
	}
}


namespace Kruskal {
	struct edge {
		int u, v;
		int len;
	};

	edge e[MaxM];

	void kruskal() {
		sort(e + 1, e + m + 1, [](edge x, edge y)->bool {
			return x.len > y.len;
		});

		int cnt = 0;
		for (int i = 1; i <= m && cnt < n - 1; i++) {
			int u = e[i].u, v = e[i].v, len = e[i].len;
			if (Set::Find(u) != Set::Find(v)) {
				Set::Union(u, v);
				Graph::addedge(u, v, len);
				cnt++;
			}
		}
	}
}


namespace SegmentTree {
	struct node {
		int min;
		int left, right;
		node* lson, *rson;
	};

	node mem[MaxN * 2], *memtop = mem;
	node* root;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right)
			p->min = d[left];
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->min = min(p->lson->min, p->rson->min);
		}
	}

	int query(int left, int right, node* p = root) {
		if (right < left)
			return infinity;
		if (p->left == left && p->right == right)
			return p->min;
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return min(query(left, p->lson->right, p->lson),
					   query(p->rson->left, right, p->rson));
	}
}


namespace HLD {
	using namespace Graph;
	using SegmentTree::build;
	using SegmentTree::query;

	int root = 1;
	int size[MaxN], father[MaxN], dep[MaxN];
	int heavy[MaxN], top[MaxN], stime, dfn[MaxN];
	int d[MaxN], ddfn[MaxN];

	void dfs1(int u = root, int step = 1, int fa = 0) {
		father[u] = fa;
		dep[u] = step;
		size[u] = 1;

		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != fa) {
				d[v] = p->len;
				dfs1(v, step + 1, u);
				size[u] += size[v];
				if (maxsize < size[v]) {
					maxsize = size[v];
					maxid = v;
				}
			}
		}
		heavy[u] = maxid;
	}

	void dfs2(int u = root, int t = root) {
		top[u] = t;
		dfn[u] = ++stime;
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
		d[root] = infinity;
		for (int i = 1; i <= n; i++)
			ddfn[dfn[i]] = d[i];
		build(ddfn);
	}

	int queryLCAMin(int x, int y) {
		if (Set::Find(x) != Set::Find(y))
			return -1;
		int Min = infinity;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]])
				swap(x, y);
			Min = min(Min, query(dfn[top[x]], dfn[x]));
			x = father[top[x]];
		}
		if (dfn[x] > dfn[y])
			swap(x, y);
		if (x != y)
			Min = min(Min, query(dfn[x] + 1, dfn[y]));
		return Min;
	}
}



int main(int argc, char* argv[]) {

	memset(Set::p, -1, sizeof(Set::p));

	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> Kruskal::e[i].u >> Kruskal::e[i].v >> Kruskal::e[i].len;
	Kruskal::kruskal();
	HLD::setup();
	cin >> q;
	int a, b;
	for (int i = 1; i <= q; i++) {
		cin >> a >> b;
		cout << HLD::queryLCAMin(a, b) << endl;
	}

	return 0;
}

#endif

