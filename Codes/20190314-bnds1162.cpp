/*
 DOCUMENT NAME "20190314-bnds1162.cpp"
 CREATION DATE 2019-03-14
 SIGNATURE CODE_20190314_BNDS1162
 COMMENT A. 2019-3-10noip模拟测验（一）-小胖的疑惑
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190314_BNDS1162

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
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

typedef long long ll;
const int MaxN = 100 + 10;

int n;
int x[MaxN], y[MaxN];

int xt[MaxN], yt[MaxN];

ll tmp[MaxN*MaxN][MaxN];
bool used[MaxN*MaxN];

vector<pair<int, int> > pnts;

ll getdist(int x, int y, int k, int id = 0) {
	if (!used[id]) {
		for (int i = 1; i <= n; i++)
			tmp[id][i] = abs(x - ::x[i]) + abs(y - ::y[i]);
		sort(tmp[id] + 1, tmp[id] + n + 1);
		for (int i = 2; i <= n; i++)
			tmp[id][i] += tmp[id][i - 1];
	}
	used[id] = true;
	return tmp[id][k];
}



int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(x[i]);
		read(y[i]);
		xt[i] = x[i];
		yt[i] = y[i];
	}

	sort(xt + 1, xt + n + 1);
	sort(yt + 1, yt + n + 1);

	for (int i = 1; i <= n; i++)
		if (i == 1 || xt[i] != xt[i - 1])
			for (int j = 1; j <= n; j++)
				if (j == 1 || yt[j] != yt[j - 1])
					pnts.push_back(make_pair(xt[i], yt[j]));
#ifdef D
	for (auto x : pnts) {
		printf("  %d %d\n", x.first, x.second);
	}
#endif

	for (int k = 1; k <= n; k++) {
		ll ans = 1e15;
		int id = 1;
		for (auto x : pnts) {
			int i = x.first, j = x.second;
			ll a = getdist(i, j, k, id);
			ans = min(ans, a);
			id++;
		}
		printf("%lld\n", ans);
	}



	return 0;
}



#endif

