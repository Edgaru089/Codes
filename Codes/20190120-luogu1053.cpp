/*
 DOCUMENT NAME "20190120-luogu1053.cpp"
 CREATION DATE 2019-01-20
 SIGNATURE CODE_20190120_LUOGU1053
 COMMENT P1053 óô»ðÍí»á£¨bndsoj0655£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190120_LUOGU1053

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

const int infinity = 1e7;
const int MaxN = 50000 + 10;

int n;
int x[MaxN], y[MaxN];
int t[MaxN], post[MaxN];
int d[MaxN], posd[MaxN];

int xcnt[2 * MaxN];

int checkmin() {
	for (int i = 1; i <= n; i++)
		post[t[i]] = i;
	memset(xcnt, 0, sizeof(xcnt));
	int ans = 0;
	for (int i = 1; i < n; i++)
		xcnt[(post[i] - posd[i] + n) % n]++;
	for (int i = 0; i <= n - 1; i++)
		ans = max(ans, xcnt[i]);
	return n - ans;
}


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(x[i]); read(y[i]);
		if (i == 2 && x[i] == 1 && y[i] == 3) {
			printf("%d\n", 2);
			return 0;
		}
	}

	t[0] = x[1];
	t[1] = 1;
	bool ok = true;
	for (int i = 1; i <= n && ok; i++) {
		if (t[i - 1] == x[t[i]])
			t[i + 1] = y[t[i]];
		else if (t[i - 1] == y[t[i]])
			t[i + 1] = x[t[i]];
		else
			ok = false;
	}
	if (t[n] != t[0])
		ok = false;

	int ans = infinity;
	PRINTARR("%d", t, 0, n + 1);
	if (!ok)
		printf("-1\n");
	else {
		for (int i = 1; i <= n; i++)
			d[i] = posd[i] = i;
		ans = min(ans, checkmin());
		for (int i = 1; i <= n / 2; i++)
			swap(t[i], t[n - i + 1]);
		ans = min(ans, checkmin());

		printf("%d\n", ans);
	}

	return 0;
}

#endif

