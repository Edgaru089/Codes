#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
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

const int MaxN=1e5+10;
int n;
int a[MaxN];
int maxval,segcnt[MaxN];

int main(int argc, char* argv[]) {
	
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		maxval=max(maxval,a[i]);
		if(i>1&&a[i]==a[i-1])
			segcnt[i]=segcnt[i-1]+1;
		else
			segcnt[i]=1;
	}

	DEBUG("maxval=%d\n",maxval);
	PRINTARR("%d",segcnt,1,n);
	
	int ans=0;
	for(int i=1;i<=n;i++)
		if(a[i]==maxval)
			ans=max(ans,segcnt[i]);
	printf("%d\n",ans);
	
	return 0;
}


