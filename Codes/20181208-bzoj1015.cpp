/*
 DOCUMENT NAME "20181208-bzoj1015.cpp"
 CREATION DATE 2018-12-08
 SIGNATURE CODE_20181208_BZOJ1015
 COMMENT 1015: [JSOI2008]–««Ú¥Û’Ωstarwar
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181208_BZOJ1015

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

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

const int MaxM = 200000 + 10, MaxN = 2 * MaxM;

int n, m;
int x[MaxM], y[MaxM];
int k;
int t[MaxN];
bool down[MaxN];
int ans[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
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

int p[MaxN];

int setfind(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = setfind(p[x]);
}

void setunion(int x, int y) {
	x = setfind(x);
	y = setfind(y);
	if (x != y) {
		p[x] += p[y];
		p[y] = x;
	}
}

int cnt;


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= m; i++) {
		read(x[i]); read(y[i]);
		x[i]++; y[i]++;
		addedge(x[i], y[i]);
	}
	read(k);
	for (int i = 1; i <= k; i++) {
		read(t[i]);
		t[i]++;
		down[t[i]] = true;
	}

	memset(p, -1, sizeof(p));
	for (int i = 1; i <= m; i++) {
		if (!down[x[i]] && !down[y[i]])
			setunion(x[i], y[i]);
	}

	PRINTARR("%d", down, 1, n);
	PRINTARR("%d", p, 1, n);

	cnt = 0;
	for (int i = 1; i <= n; i++)
		if (!down[i] && p[i] < 0)
			cnt++;

	for (int i = k; i >= 1; i--) {
		ans[i] = cnt;
		int u = t[i];
		cnt++;
		down[u] = false;
		for (node* p = h[t[i]]; p; p = p->next) {
			int v = p->v;
			if (!down[v] && setfind(u) != setfind(v)) {
				setunion(u, v);
				cnt--;
			}
		}
	}
	ans[0] = cnt;

	for (int i = 0; i <= k; i++)
		printf("%d\n", ans[i]);

	return 0;
}

#endif

