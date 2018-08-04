/*
DOCUMENT NAME "20180724-luogu2146.cpp"
CREATION DATE 2018-07-24
SIGNATURE CODE_20180724_LUOGU2146
COMMENT [NOI2015]软件包管理器 / 树链剖分套线段树
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180724_LUOGU2146

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 100000 + 10;

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

void read(string& str) {
	str.clear();
	char c;
	while (isblank(c = getchar()) || iscntrl(c));
	do {
		str.push_back(c);
	} while (!isblank(c = getchar()) && !iscntrl(c));
	ungetc(c, stdin);
}

int n;

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
		int sum, lazy;
		int left, right;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right) {
			p->sum = 0;
			p->lazy = -1;
			p->lson = p->rson = nullptr;
		}
		else {
			p->lazy = -1;
			int mid = (left + right) / 2;
			build(left, mid, p->lson);
			build(mid + 1, right, p->rson);
			//p->sum = p->lson->sum + p->rson->sum;
			p->sum = 0;
		}
	}

	void pushdown(node* p) {
		if (p == nullptr || p->lazy == -1)
			return;
		p->sum = (p->right - p->left + 1)*p->lazy;
		if (p->lson != nullptr)
			p->lson->lazy = p->lazy;
		if (p->rson != nullptr)
			p->rson->lazy = p->lazy;
		p->lazy = -1;
	}

	void set(int left, int right, int val, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazy = val;
			return;
		}
		if (p->lson->right >= right)
			set(left, right, val, p->lson);
		else if (p->rson->left <= left)
			set(left, right, val, p->rson);
		else {
			set(left, p->lson->right, val, p->lson);
			set(p->rson->left, right, val, p->rson);
		}
		pushdown(p);
		pushdown(p->lson);
		pushdown(p->rson);
		p->sum = p->lson->sum + p->rson->sum;
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
					query(p->rson->left, right, p->rson));
	}
}

namespace hld {
	using namespace graph;
	int size[MaxN], father[MaxN], heavy[MaxN];
	int stime, dfn[MaxN], top[MaxN];

	void dfs1(int u, int fa) {
		father[u] = fa;
		size[u] = 1;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != fa) {
				dfs1(v, u);
				size[u] += size[v];
			}
		}
		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != fa) {
				if (maxsize < size[v]) {
					maxsize = size[v];
					maxid = v;
				}
			}
		}
		heavy[u] = maxid;
	}

	void dfs2(int u, int top) {
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

	void init() {
		dfs1(1, 0);
		dfs2(1, 1);
		segmenttree::build();
	}

	int install(int x) {
		int ans = 0;
		while (top[x] != 1) {
			ans += dfn[x] - dfn[top[x]] + 1 - segmenttree::query(dfn[top[x]], dfn[x]);
			segmenttree::set(dfn[top[x]], dfn[x], 1);
			x = father[top[x]];
		}
		ans += dfn[x] - dfn[top[x]] + 1 - segmenttree::query(dfn[top[x]], dfn[x]);
		segmenttree::set(dfn[top[x]], dfn[x], 1);
		return ans;
	}

	int uninstall(int x) {
		int ans = segmenttree::query(dfn[x], dfn[x] + size[x] - 1);
		segmenttree::set(dfn[x], dfn[x] + size[x] - 1, 0);
		return ans;
	}
}


int m;

int main(int argc, char* argv[]) {
	using namespace graph;
	using namespace hld;

	read(n);
	int x;
	for (int i = 2; i <= n; i++) {
		read(x);
		addedge(i, x + 1);
	}

	init();

	read(m);
	string str;
	for (int i = 1; i <= m; i++) {
		read(str);
		read(x);
		if (str == "install")
			printf("%d\n", install(x + 1));
		else if (str == "uninstall")
			printf("%d\n", uninstall(x + 1));
	}

	return 0;
}

#endif

