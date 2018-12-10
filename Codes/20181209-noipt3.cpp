/*
 DOCUMENT NAME "20181209-noipt3.cpp"
 CREATION DATE 2018-12-09
 SIGNATURE CODE_20181209_NOIPT3
 COMMENT Ð¡Ææ»ØµØÇò (earth)
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181209_NOIPT3

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cctype>
#include <cstdio>
using namespace std;

#define FILENAME "earth"

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf( __VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
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

const int infinity = 1e8;
const int MaxN = 100;

int n, m;

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
}

int dis[MaxN], step[MaxN];

void dfs(int u = 1, int l = 0, int s = 0) {
	DEBUG("  dfs(u=%d, l=%d, s=%d)\n", u, l, s);
	dis[u] = l;
	step[u] = s;
	for (node* p = h[u]; p; p = p->next) {
		if (dis[p->v] <= -infinity) {
			dfs(p->v, l + p->len, s + 1);
		}
	}
}


int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	int t;
	read(t);
	while (t--) {
		memset(h, 0, sizeof(h));
		memtop = mem;

		read(n); read(m);
		for (int i = 1; i <= n; i++)
			dis[i] = -infinity;
		for (int i = 1; i <= m; i++) {
			int u, v, l;
			read(u); read(v); read(l);
			addedge(u, v, l);
		}

		PRINTARR("%d", dis, 1, n);
		dfs(1);
		PRINTARR("%d", dis, 1, n);
		if (dis[n] <= -infinity) {
			println(-1);
			DEBUG("Unreachable\n");
		} else {
			DEBUG("Reachable, dis[n]=%d, step[n]=%d\n", dis[n], step[n]);
			if (dis[n] >= 0)
				println(dis[n] % step[n]);
			else
				println(step[n] - (-dis[n]) % step[n]);
		}
	}






	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

