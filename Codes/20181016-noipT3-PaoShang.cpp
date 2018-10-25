/*
 DOCUMENT NAME "20181016-noipT3-PaoShang.cpp"
 CREATION DATE 2018-10-16
 SIGNATURE CODE_20181016_NOIPT3_PAOSHANG
 COMMENT paoshang.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181016_NOIPT3_PAOSHANG

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

#define FILENAME "paoshang"

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

int n, m, q;
int u, v;
int d[MaxN];
string str;
int x, y;

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
		int max, maxpos, min;
	};

	node* root;
	node mem[2 * MaxN], *memtop = mem;

	void build(int d[], int left = 1, int right = n, node*& p = root) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		if (left == right) {
			p->max = p->min = d[left];
		} else {
			int mid = (left + right) / 2;
			build(d, left, mid, p->lson);
			build(d, mid + 1, right, p->rson);
			p->max = max(p->lson->max, p->rson->max);
			p->min = min(p->lson->min, p->rson->min);
		}
	}

	void changepnt(int pos, int val, node* p = root) {
		if (p->left == p->right&&p->right == pos) {
			p->max = p->min = val;
			return;
		}
		if (p->lson->right >= pos)
			changepnt(pos, val, p->lson);
		else /* p->rson->left <= pos */
			changepnt(pos, val, p->rson);
		p->max = max(p->lson->max, p->rson->max);
		p->min = min(p->lson->min, p->rson->min);
	}

	int querymax(int left, int right, node* p = root) {
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

	int querymin(int left, int right, node* p = root) {
		if (p->left == left && p->right == right)
			return p->min;
		if (p->lson->right >= right)
			return querymin(left, right, p->lson);
		else if (p->rson->left <= left)
			return querymin(left, right, p->rson);
		else
			return min(querymin(left, p->lson->right, p->lson),
					   querymin(p->rson->left, right, p->rson));
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

int query(int u, int v) {
	int maxval = 0, minval = 1e8;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			maxval = max(maxval, segtree::querymax(dfn[top[u]], dfn[u]));
			minval = min(minval, segtree::querymin(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		} else {
			maxval = max(maxval, segtree::querymax(dfn[top[v]], dfn[v]));
			minval = min(minval, segtree::querymin(dfn[top[v]], dfn[v]));
			v = father[top[v]];
		}
	}
	maxval = max(maxval, segtree::querymax(min(dfn[u], dfn[v]), max(dfn[u], dfn[v])));
	minval = min(minval, segtree::querymin(min(dfn[u], dfn[v]), max(dfn[u], dfn[v])));
	return maxval - minval;
}

void change(int u, int t) {
	segtree::changepnt(dfn[u], t);
}



int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, bufferreadsize, in);

	read(n); read(m);
	assert(m == n - 1);
	for (int i = 1; i <= n; i++)
		read(d[i]);
	for (int i = 1; i <= m; i++) {
		read(u); read(v);
		addedge(u, v);
	}
	build();
	read(q);
	for (int i = 1; i <= q; i++) {
		read(str);
		read(u);
		read(v);
		if (str == "Q") {
			println(query(u, v));
		} else {
			change(u, v);
		}
	}


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

