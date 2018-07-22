/*
DOCUMENT NAME "20180718-noi2018-return.cpp"
CREATION DATE 2018-07-18
SIGNATURE CODE_20180718_NOI2018_RETURN
COMMENT µÚÒ»ÊÔ ¹é³Ì£¨return£©
*/

/*
INPUT
1
4 3
1 2 50 1
2 3 100 2
3 4 50 1
5 0 2
3 0
2 1
4 1
3 1
3 2
OUTPUT
0
50
200
50
150

INPUT
1
5 5
1 2 1 2
2 3 1 2
4 3 1 2
5 3 1 2
1 5 2 1
4 1 3
5 1
5 2
2 0
4 0
OUTPUT
0
2
3
1
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180718_NOI2018_RETURN

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const string programId = "return";

const int MaxN = 200000 + 10, MaxM = 400000 + 10;
//const int MaxN = 1500 + 10, MaxM = 2000 + 10;

#define GETCHAR (getchar())

template<typename IntType>
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

int n, m;
int q, k, s;

namespace graph {
	struct node {
		int v;
		int l, a;
		node* next;
	};

	node* h[MaxN];
	node mem[MaxM * 2], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, int len, int at) {
		node* p = ALLOCATE;
		p->v = v;
		p->l = len;
		p->a = at;
		p->next = h[u];
		h[u] = p;
		p = ALLOCATE;
		p->v = u;
		p->l = len;
		p->a = at;
		p->next = h[v];
		h[v] = p;
	}
}

namespace unionfindset {
	int p[MaxN];

	int find(int u) {
		if (p[u] < 0)
			return u;
		else
			return p[u] = find(p[u]);
	}

	void _union(int x, int y) {
		x = find(x);
		y = find(y);
		p[x] += p[y];
		p[y] = x;
	}
}

namespace kruskal {
	struct edge {
		int u, v;
		int l, a;
	};

	edge e[MaxM];

	bool compare(const edge& a, const edge& b) {
		return a.a > b.a;
	}

	void run() {
		sort(e + 1, e + m + 1, compare);

		int cnt = n;
		for (int i = 1; i <= m && cnt > 1; i++) {
			int u = e[i].u, v = e[i].v, l = e[i].l, a = e[i].a;
			if (unionfindset::find(u) != unionfindset::find(v)) {
				unionfindset::_union(u, v);
				graph::addedge(u, v, l, a);
			}
		}
	}
}

class segtree {
public:
	struct node {
		int left, right;
		int min, sum;
		node* lson, *rson;
	};
	node* root;
	node mem[2 * MaxN], *memtop;

	segtree() { memtop = mem; }

	void build(int d[], int left, int right, node*& p) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right) {
			p->min = p->sum = d[left];
			p->lson = p->rson = NULL;
		}
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->min = min(p->lson->min, p->rson->min);
			p->sum = p->lson->sum + p->rson->sum;
		}
	}

	int queryid(int k, int left, int right, node* p) {
		if (left == p->left&&right == p->right) {
			if (left == right)
				if (k >= p->min)
					return left;
				else
					return 0;
			else if (p->lson->min <= k && p->rson->min <= k)
				return queryid(k, p->rson->left, p->rson->right, p->rson);
			else if (p->lson->min <= k)
				return queryid(k, p->lson->left, p->lson->right, p->lson);
			else if (p->rson->min <= k)
				return queryid(k, p->rson->left, p->rson->right, p->rson);
			else
				return 0;
		}
		else if (p->lson->right >= right)
			return queryid(k, left, right, p->lson);
		else if (p->rson->left <= left)
			return queryid(k, left, right, p->rson);
		else
			return max(queryid(k, left, p->lson->right, p->lson),
					   queryid(k, p->rson->left, right, p->rson));
	}

	int querysum(int left, int right, node* p) {
		if (left == p->left&&right == p->right)
			return p->sum;
		else if (p->lson->right >= right)
			return querysum(left, right, p->lson);
		else if (p->rson->left <= left)
			return querysum(left, right, p->rson);
		else
			return (querysum(left, p->lson->right, p->lson) +
					querysum(p->rson->left, right, p->rson));
	}
};

namespace hld {
	using namespace graph;
	int root = 1;
	int size[MaxN], fa[MaxN], dep[MaxN], heavyson[MaxN];
	int top[MaxN], stime, dfn[MaxN];

	int dat[MaxN], dlen[MaxN];
	int conv_dat[MaxN], conv_dlen[MaxN];

	segtree at, len;

	void dfs1(int u = root, int dep = 1) {
		size[u] = 1;
		hld::dep[u] = dep;
		for (node* p = h[u]; p != NULL; p = p->next) {
			int v = p->v;
			if (v != fa[u]) {
				fa[v] = u;
				dat[v] = p->a;
				dlen[v] = p->l;
				dfs1(v, dep + 1);
				size[u] += size[v];
			}
		}

		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != NULL; p = p->next) {
			int v = p->v;
			if (v != fa[u])
				if (maxsize < size[v]) {
					maxsize = size[v];
					maxid = v;
				}
		}
		heavyson[u] = maxid;
	}

	void dfs2(int u = root, int top = root) {
		dfn[u] = ++stime;
		hld::top[u] = top;
		if (heavyson[u] != 0)
			dfs2(heavyson[u], top);
		for (node* p = h[u]; p != NULL; p = p->next) {
			int v = p->v;
			if (v != fa[u] && v != heavyson[u])
				dfs2(v, v);
		}
	}

	void build() {
		dfs1();
		dfs2();
		dat[root] = s + 1;
		dlen[root] = 0;
		for (int i = 1; i <= n; i++) {
			conv_dat[dfn[i]] = dat[i];
			conv_dlen[dfn[i]] = dlen[i];
		}
		at.build(conv_dat, 1, n, at.root);
		len.build(conv_dlen, 1, n, len.root);
	}

	const int hascar = 1, nocar = 2;
	int query(int pos, int water) {
		int state = hascar;
		int sum = 0;
		while (pos != 0) {
			int id = 0;
			if (state == hascar) {
				id = at.queryid(water, dfn[top[pos]], pos, at.root);
				if (id != 0) {
					state = nocar;
					pos = id;
				}
			}
			if (state == nocar) {
				sum += len.querysum(dfn[top[pos]], dfn[pos], len.root);
			}

			pos = fa[top[pos]];
		}
		return sum;
	}
}

int main(int argc, char* argv[]) {
#ifndef LOCAL
	string inname = programId + ".in", outname = programId + ".out";
	freopen(inname.c_str(), "r", stdin);
	freopen(outname.c_str(), "w", stdout);
#endif

	int t;
	read(t);

	while (t--) {
		memset(unionfindset::p, -1, sizeof(unionfindset::p));
		memset(graph::h, 0, sizeof(graph::h));
		graph::memtop = graph::mem;
		hld::stime = 0;
		hld::at.memtop = hld::at.mem;
		hld::len.memtop = hld::len.mem;

		read(n); read(m);
		for (int i = 1; i <= m; i++) {
			read(kruskal::e[i].u);
			read(kruskal::e[i].v);
			read(kruskal::e[i].l);
			read(kruskal::e[i].a);
		}
		read(q); read(k); read(s);

		kruskal::run();
		hld::build();

		int lastans = 0;
		for (int i = 1; i <= q; i++) {
			int v0, p0;
			read(v0); read(p0);
			int v = (v0 + k * lastans - 1) % n + 1;
			int p = (p0 + k * lastans) % (s + 1);
			printf("%d\n", lastans = hld::query(v, p));
		}
	}
	return 0;
}

#endif

