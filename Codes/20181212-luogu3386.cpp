/*
 DOCUMENT NAME "20181212-luogu3386.cpp"
 CREATION DATE 2018-12-12
 SIGNATURE CODE_20181212_LUOGU3386
 COMMENT P3386 ¡¾Ä£°å¡¿¶þ·ÖÍ¼Æ¥Åä
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181212_LUOGU3386

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
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

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}


const int MaxN = 2000 + 10, MaxM = 1000000 + 10;

int n0, m0, e;

struct node {
	int v;
	bool useable;
	node* next, *rev;
};

// L[1, n0]; R[n0+1, n0+m0];
node* h[2 * MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop);

int n;

bool used[MaxN];

bool dfs(int u, int from) {
	if (u > n0 && !used[u - n0]) {
		used[u - n0] = true;
		return true;
	}
	for (node* p = h[u]; p; p = p->next) {
		if (p->useable&&p->v != from) {
			ASSERT(!p->rev->useable);
			p->useable = false;
			p->rev->useable = true;
			if (dfs(p->v, u))
				return true;
			p->useable = true;
			p->rev->useable = false;
		}
	}
	return false;
}

void addedge(int u, int v) {
	v += n0;
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	node* pr = ALLOCATE;
	pr->v = u;
	pr->next = h[v];
	h[v] = pr;
	p->useable = true;
	p->rev = pr;
	pr->rev = p;
}


int main(int argc, char* argv[]) {

	read(n0); read(m0); read(e);
	for (int i = 1; i <= e; i++) {
		int u, v;
		read(u); read(v);
		if (v > m0)
			continue;
		addedge(u, v);
	}

	n = n0 + m0;

	int ans = 0;
	for (int i = 1; i <= n0; i++) {
		if (dfs(i, 0))
			ans++;
	}

	printf("%d\n", ans);

	return 0;
}

#endif

