/*
 DOCUMENT NAME "20180914-luogu2590.cpp"
 CREATION DATE 2018-09-14
 SIGNATURE CODE_20180914_LUOGU2590
 COMMENT P2590 [ZJOI2008]树的统计 / 树剖
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180914_LUOGU2590

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;
constexpr int infinity = 1e8;
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
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
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
		ll sum, max;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(ll* d = ::d, int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right) {
			p->lson = p->rson = nullptr;
			p->sum = p->max = d[left];
		}
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->sum = p->lson->sum + p->rson->sum;
			p->max = max(p->lson->max, p->rson->max);
		}
	}

	ll querysum(int left, int right, node* p = root) {
		if (p->left == left && p->right == right)
			return p->sum;
		if (p->lson->right >= right)
			return querysum(left, right, p->lson);
		else if (p->rson->left <= left)
			return querysum(left, right, p->rson);
		else
			return (querysum(left, p->lson->right, p->lson) +
					querysum(p->rson->left, right, p->rson));
	}

	ll querymax(int left, int right, node* p = root) {
		if (p->left == left && p->right == right)
			return p->max;
		if (p->lson->right >= right)
			return querymax(left, right, p->lson);
		else if (p->rson->left <= left)
			return querymax(left, right, p->rson);
		else
			return max(querymax(left, p->lson->right, p->lson),
					   querymax(p->rson->left, right, p->rson));
	}

	void changepnt(int id, ll val, node* p = root) {
		if (p->left == p->right&&p->right == id) {
			p->sum = p->max = val;
			return;
		}
		if (p->lson->right >= id)
			changepnt(id, val, p->lson);
		else /* p->rson->left <= id */
			changepnt(id, val, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
		p->max = max(p->lson->max, p->rson->max);
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

void changepnt(int id, ll val) {
	segtree::changepnt(dfn[id], val);
}

ll querylcamax(int u, int v) {
	ll ans = -infinity;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			ans = max(ans, segtree::querymax(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		}
		else {
			ans = max(ans, segtree::querymax(dfn[top[v]], dfn[v]));
			v = father[top[v]];
		}
	}
	if (dfn[u] < dfn[v])
		return max(ans, segtree::querymax(dfn[u], dfn[v]));
	else
		return max(ans, segtree::querymax(dfn[v], dfn[u]));
}

ll querylcasum(int u, int v) {
	ll ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			ans += segtree::querysum(dfn[top[u]], dfn[u]);
			u = father[top[u]];
		}
		else {
			ans += segtree::querysum(dfn[top[v]], dfn[v]);
			v = father[top[v]];
		}
	}
	if (dfn[u] < dfn[v])
		return ans + segtree::querysum(dfn[u], dfn[v]);
	else
		return ans + segtree::querysum(dfn[v], dfn[u]);
}



int main(int argc, char* argv[]) {

	read(n);

	int a, b;
	for (int i = 1; i < n; i++) {
		read(a, b);
		addedge(a, b);
	}
	for (int i = 1; i <= n; i++)
		read(d[i]);

	build(1);

	string s;
	int x, y;
	read(m);
	for (int i = 1; i <= m; i++) {
		read(s, x, y);
		if (s[1] == 'H') // CHANGE
			changepnt(x, y);
		else if (s[1] == 'M') // QMAX
			printf("%lld\n", querylcamax(x, y));
		else if (s[1] == 'S') // QSUM
			printf("%lld\n", querylcasum(x, y));
	}

	return 0;
}

#endif

