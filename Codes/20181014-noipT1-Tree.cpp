/*
 DOCUMENT NAME "20181014-noipT1-Tree.cpp"
 CREATION DATE 2018-10-14
 SIGNATURE CODE_20181014_NOIPT1_TREE
 COMMENT tree.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181014_NOIPT1_TREE

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "tree"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
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

template<>
inline void read<char*>(char*& x) {
	char* p = x;
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		*(p++) = c;
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
}

char bufferwrite[buffersize], *writetop = bufferwrite;
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

const int MaxN = 100000 + 10, MaxC = 100000 + 10;
const int Mod = 100000007;

int n;
int u, v, l;
long long lsum;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

int r;
int cnt[MaxN];

void addedge(int u, int v, int l) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = l;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->len = l;
	p->next = h[v];
	h[v] = p;
}

int father[MaxN];
bool valid[MaxN];
void dfs0(int u = r, int from = 0) {
	father[u] = from;
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from)
			dfs0(v, u);
	}
}

long long ans = 0;
int dfs1(int u) {
	long long mmax = 0, lmax = 0;
	for (node* p = h[u]; p; p = p->next) {
		if (p->v != father[u]) {
			int q = dfs1(p->v) + p->len;
			if (q > mmax) {
				lmax = mmax;
				mmax = q;
			} else if (q > lmax)
				lmax = q;
		}
	}
	ans = max(ans, mmax + lmax);
	return mmax;
}




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "w");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(n);
	for (int i = 1; i <= n - 1; i++) {
		read(u); read(v); read(l);
		addedge(u, v, l);
		cnt[u]++;
		cnt[v]++;
		lsum = (lsum + l) % Mod;
	}

	for (int i = 1; i <= n; i++) {
		if (cnt[i] > 2)
			r = i;
		else
			valid[i] = true;
	}

	if (!r) {
		println(lsum % Mod);
	} else {
		dfs0(r);
		dfs1(r);
		println((2 * lsum - ans + Mod) % Mod);
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

