#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
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

const int MaxN=1e5+10,MaxLogN=17+2;

int n,m;
int a[MaxN];

int logn;
int st[MaxN][MaxLogN];



int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(a[i]);

	for (int i = 1; i <= n; i++)
		st[i][0]=a[i];

	logn = floor(log2(n));
	DEBUG("logn=%d\n",logn);
	for (int j = 1; j <= logn; j++)
		for (int i = 1; i <= n; i++) 
			if(i+(1<<j)-1<=n)
				st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	PRINTARR("%d",st[1],1,n);
	PRINTARR("%d",st[2],1,n);

	for(int i=1;i<=m;i++){
		int l,r;
		read(l);read(r);
		int loglen=floor(log2(r-l+1));
		printf("%d\n",max(st[l][loglen],st[r-(1<<loglen)+1][loglen]));
	}

	return 0;
}


