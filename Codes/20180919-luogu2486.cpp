/*
 DOCUMENT NAME "20180919-luogu2486.cpp"
 CREATION DATE 2018-09-19
 SIGNATURE CODE_20180919_LUOGU2486
 COMMENT P2486 [SDOI2011]È¾É« / Ê÷ÆÊ+Ïß¶ÎÊ÷Ï¹¸ã
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180919_LUOGU2486

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const int MaxN = 1e5 + 10, MaxM = 1e5 + 10;

template<typename IntType = int>
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
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m;

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

int father[MaxN], ssize[MaxN], dep[MaxN], heavy[MaxN];
void dfs1(int u, int from = 0, int step = 1) {
	father[u] = from;
	ssize[u] = 1;
	dep[u] = step;
	int maxsize = 0;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (v != father[u]) {
			dfs1(v, u, step + 1);
			if (maxsize < ssize[v]) {
				maxsize = ssize[v];
				heavy[u] = v;
			}
		}
	}
}

int dfn[MaxN], sstime, top[MaxN];
void dfs2(int u, int t) {
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


namespace segtree {
	struct seginfo {
		seginfo() { lcolor = rcolor = segcnt = 0; }
		seginfo(int col) { lcolor = rcolor = col; segcnt = 1; }
		seginfo(const seginfo& left, const seginfo& right) {
			lcolor = left.lcolor;
			rcolor = right.rcolor;
			segcnt = left.segcnt + right.segcnt;
			if (left.rcolor == right.lcolor)
				segcnt--;
		}
		int lcolor, rcolor;
		int segcnt;
	};

	struct node {
		int left, right;
		int lazy;
		seginfo s;
		node* lson, *rson;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		p->lazy = 0;
		if (left == right)
			p->s = seginfo(d[left]);
		else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->s = seginfo(p->lson->s, p->rson->s);
		}
	}

	void pushdown(node* p) {
		if (p != nullptr && p->lazy != 0) {
			p->s = seginfo(p->lazy);
			if (p->lson != nullptr)
				p->lson->lazy = p->lazy;
			if (p->rson != nullptr)
				p->rson->lazy = p->lazy;
			p->lazy = 0;
		}
	}

	void change(int left, int right, int c, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazy = c;
			return;
		}
		pushdown(p->lson);
		pushdown(p->rson);
		if (p->lson->right >= right)
			change(left, right, c, p->lson);
		else if (p->rson->left <= left)
			change(left, right, c, p->rson);
		else {
			change(left, p->lson->right, c, p->lson);
			change(p->rson->left, right, c, p->rson);
		}
		pushdown(p);
		pushdown(p->lson);
		pushdown(p->rson);
		p->s = seginfo(p->lson->s, p->rson->s);
	}

	seginfo query(int left, int right, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right)
			return p->s;
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return seginfo(query(left, p->lson->right, p->lson),
						   query(p->rson->left, right, p->rson));
	}
}
using segtree::seginfo;

int d[MaxN];
int ddfn[MaxN];
void build() {
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
		ddfn[dfn[i]] = d[i];
	segtree::build(ddfn);
}

void change(int u, int v, int c) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			segtree::change(dfn[top[u]], dfn[u], c);
			u = father[top[u]];
		}
		else {
			segtree::change(dfn[top[v]], dfn[v], c);
			v = father[top[v]];
		}
	}
	if (dep[u] > dep[v])
		segtree::change(dfn[v], dfn[u], c);
	else
		segtree::change(dfn[u], dfn[v], c);
}

segtree::seginfo query(int u, int v) {
	seginfo su = seginfo(), sv = seginfo();
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			su = seginfo(su, segtree::query(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		}
		else {
			sv = seginfo(sv, segtree::query(dfn[top[v]], dfn[v]));
			v = father[top[v]];
		}
	}
	if (dep[u] > dep[v])
		su = seginfo(su, segtree::query(dfn[v], dfn[u]));
	else
		sv = seginfo(sv, segtree::query(dfn[u], dfn[v]));
	return seginfo(sv, su);
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

	build();

	string comm;
	int a, b, c;
	for (int i = 1; i <= m; i++) {
		read(comm);
		if (comm == "C") {
			read(a, b, c);
			change(a, b, c);
		}
		else if (comm == "Q") {
			read(a, b);
			printf("%d\n", query(a, b).segcnt);
		}
	}

	return 0;
}

#endif

