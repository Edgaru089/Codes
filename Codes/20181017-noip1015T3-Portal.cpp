/*
 DOCUMENT NAME "20181017-noip1015T3-Portal.cpp"
 CREATION DATE 2018-10-17
 SIGNATURE CODE_20181017_NOIP1015T3_PORTAL
 COMMENT 10月15日模拟赛T3 传送门 portal.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181017_NOIP1015T3_PORTAL

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "portal"

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

typedef long long ll;
const int MaxN = 1000000 + 10;

template<typename ValType>
void updatemax(ValType& val, const ValType& newval) {
	val = max(val, newval);
}

int n;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
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

ll maxchain[MaxN];
void dfs(int u, int from) {
	ll maxval = 0;
	for (node* p = h[u]; p; p = p->next) {
		if (p->v != from) {
			dfs(p->v, u);
			maxval = max(maxval, maxchain[p->v] + p->len);
		}
	}
	maxchain[u] = maxval;
}

ll dfs2(int u, int from) {
	ll maxans = 0;
	for (node* p = h[u]; p; p = p->next) {
		if (p->v != from) {
			ll maxsub = 0;
			// place a portal here
			updatemax(maxsub, maxchain[p->v] + p->len);
			// recurse
			updatemax(maxsub, dfs2(p->v, u));
			maxans += maxsub;
		}
	}
	return maxans;
}






int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	read(n);
	int u, v, l;
	ll sum = 0;
	for (int i = 1; i <= n - 1; i++) {
		read(u); read(v); read(l);
		addedge(u, v, l);
		sum += l;
	}

	dfs(1, 0);

	println(2 * sum - dfs2(1, 0));




	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

