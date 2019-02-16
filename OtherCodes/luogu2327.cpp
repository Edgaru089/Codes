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

const int MaxN=10000+10;

int n;

int ans;
bool flag;
int x[MaxN];
int a[MaxN];


int main(int argc, char* argv[]) {
	
	read(n);
	for(int i=1;i<=n;i++)
		read(x[i]);
	
	a[1]=1;
	flag=true;
	for(int i=2;i<=n&&flag;i++){
		a[i]=x[i-1]-a[i-2]-a[i-1];
		if(a[i]>1||a[i]<0)
			flag=false;
	}
	if(x[n]!=a[n]+a[n-1])
		flag=false;
	if(flag)
		ans++;
	a[1]=0;
	flag=true;
	for(int i=2;i<=n&&flag;i++){
		a[i]=x[i-1]-a[i-2]-a[i-1];
		if(a[i]>1||a[i]<0)
			flag=false;
	}
	if(x[n]!=a[n]+a[n-1])
		flag=false;
	if(flag)
		ans++;
	
	printf("%d\n",ans);
	
	return 0;
}


