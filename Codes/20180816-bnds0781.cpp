/*
DOCUMENT NAME "20180816-bnds0781.cpp"
CREATION DATE 2018-08-16
SIGNATURE CODE_20180816_BNDS0781
COMMENT [ZJOI2008]树的统计
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180816_BNDS0781

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;

constexpr int MaxN = 1e5 + 10, MaxM = 1e5 + 10;

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
int r;
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
		ll sum, max;
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
			p->sum = p->max = d[left];
		else {
			int mid = (left + right) / 2;
			build(left, mid, d, p->lson);
			build(mid + 1, right, d, p->rson);
			p->sum = (p->lson->sum + p->rson->sum);
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

	void change(int pos, ll val, node* p = root) {
		if (p->left == pos && p->right == pos) {
			p->max = p->sum = val;
			return;
		}
		if (p->lson->right >= pos)
			change(pos, val, p->lson);
		else if (p->rson->left <= pos)
			change(pos, val, p->rson);
		p->max = max(p->lson->max, p->rson->max);
		p->sum = p->lson->sum + p->rson->sum;
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

	void setval(int u, ll val) {
		segmenttree::change(dfn[u], val);
	}

	ll querysum(int u, int v) {
		ll sum = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]])
				swap(u, v);
			sum = (sum + segmenttree::querysum(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		}
		if (dep[u] < dep[v])
			swap(u, v);
		sum = (sum + segmenttree::querysum(dfn[v], dfn[u]));
		return sum;
	}

	ll querymax(int u, int v) {
		ll lmax = numeric_limits<ll>::min();
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]])
				swap(u, v);
			lmax = max(lmax, segmenttree::querymax(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		}
		if (dep[u] < dep[v])
			swap(u, v);
		lmax = max(lmax, segmenttree::querymax(dfn[v], dfn[u]));
		return lmax;
	}
}



int main(int argc, char* argv[]) {
	using namespace graph;
	using namespace hld;

	read(n);
	r = 1;
	int u, v;
	for (int i = 1; i < n; i++) {
		read(u, v);
		addedge(u, v);
	}
	for (int i = 1; i <= n; i++)
		read(d[i]);
	setup();

	read(m);
	ll t;
	string k;
	for (int i = 1; i <= m; i++) {
		read(k);
		if (k == "CHANGE") {
			read(u, t);
			setval(u, t);
		}
		else if (k == "QMAX") {
			read(u, v);
			printf("%lld\n", querymax(u, v));
		}
		else if (k == "QSUM") {
			read(u, v);
			printf("%lld\n", querysum(u, v));
		}
	}


	return 0;
}

#endif

