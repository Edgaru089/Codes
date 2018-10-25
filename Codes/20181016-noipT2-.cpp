/*
 DOCUMENT NAME "20181016-noipT2-.cpp"
 CREATION DATE 2018-10-16
 SIGNATURE CODE_20181016_NOIPT2_
 COMMENT ¿ª»Ä£¨¿¼ÍêÐ´µÄ£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181016_NOIPT2_

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "kaihuang"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

const int MaxN = 100000 + 10;

int n, q;
int d[MaxN];
string str;
int k, x, w;
int ks[MaxN];

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

int dep[MaxN], father[MaxN], ssize[MaxN], heavy[MaxN];
void dfs1(int u, int from, int step) {
	father[u] = from;
	ssize[u] = 1;
	dep[u] = step;
	int maxsize = 0;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from) {
			dfs1(v, u, step + 1);
			ssize[u] += ssize[v];
			if (ssize[v] > maxsize) {
				maxsize = ssize[v];
				heavy[u] = v;
			}
		}
	}
}

int sstime, dfn[MaxN], top[MaxN];
void dfs2(int u, int t) {
	dfn[u] = ++sstime;
	top[u] = t;
	if (heavy[u])
		dfs2(heavy[u], t);
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != father[u] && v != heavy[u]) {
			dfs2(v, v);
		}
	}
}

namespace segtree {
	struct node {
		int left, right;
		node* lson, *rson;
		int sum;
		bool flag;
		int lazyflag;
		int flagsum;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		p->lazyflag = -1;
		if (left == right) {
			p->sum = d[left];
		} else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->sum = p->lson->sum + p->rson->sum;
		}
	}

	void pushdown(node* p) {
		if (p->lazyflag >= 0) {
			p->flag = p->lazyflag;
			p->flagsum = p->sum*(int)p->flag;
			if (p->lson)
				p->lson->lazyflag = p->lazyflag;
			if (p->rson)
				p->rson->lazyflag = p->lazyflag;
			p->lazyflag = -1;
		}
	}

	void changepnt(int pos, int val, node* p = root) {
		if (p->left == p->right&&p->right == pos) {
			p->sum = val;
			return;
		}
		if (p->lson->right >= pos)
			changepnt(pos, val, p->lson);
		else /* p->rson->left <= pos */
			changepnt(pos, val, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}

	int query(int left, int right, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right)
			return p->flagsum;
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return (query(left, p->lson->right, p->lson) +
					query(p->rson->left, right, p->rson));
	}

	void changeflag(int left, int right, bool val, node* p = root) {
		pushdown(p);
		if (p->left == left && p->right == right) {
			p->lazyflag = val;
			return;
		}
		if (p->lson->right >= right)
			changeflag(left, right, val, p->lson);
		else if (p->rson->left <= left)
			changeflag(left, right, val, p->rson);
		else {
			changeflag(left, p->lson->right, val, p->lson);
			changeflag(p->rson->left, right, val, p->rson);
		}
		pushdown(p->lson);
		pushdown(p->rson);
		pushdown(p);
		p->flagsum = p->lson->flagsum + p->rson->flagsum;
	}
}

int dfnd[MaxN];
void build() {
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++)
		dfnd[dfn[i]] = d[i];
	segtree::build(dfnd);
}

bool cmp(int x, int y) {
	return dfn[x] > dfn[y];
}

int query() {
	sort(ks + 1, ks + k + 1, cmp);
	segtree::changeflag(1, n, false);
	long long sum = 0;
	for (int i = 1; i <= k; i++) {
		int u = ks[i], v = ks[i + 1];
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				segtree::changeflag(dfn[top[u]], dfn[u], true);
				u = father[top[u]];
			} else {
				segtree::changeflag(dfn[top[v]], dfn[v], true);
				v = father[top[v]];
			}
		}
		segtree::changeflag(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), true);
	}
	return segtree::query(1, n);
}

void change(int x, int w) {
	segtree::changepnt(dfn[x], w);
}




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, bufferreadsize, in);

	read(n); read(q);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		read(u); read(v);
		addedge(u, v);
	}

	build();

	for (int i = 1; i <= q; i++) {
		read(str);
		if (str == "Q") {
			k = 0;
			while (x = read<int>())
				ks[++k] = x;
			println(query());
		} else {
			read(x); read(w);
			change(x, w);
		}
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

