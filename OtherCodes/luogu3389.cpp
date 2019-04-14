#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

typedef long double ld;
const int MaxN=100+10;

int n;
ld a[MaxN][MaxN],b[MaxN];





int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			scanf("%Lf",&a[i][j]);
		scanf("%Lf",&b[i]);
	}

	bool ok=true;
	for(int i=1;i<=n;i++){
		if(fabs(a[i][i])<1e-5){
			ok=false;
			break;
		}
		b[i]/=a[i][i];
		for(int j=i+1;j<=n;j++)
			a[i][j]/=a[i][i];
		a[i][i]=1;
		for(int j=1;j<=n;j++){
			if(i==j)
				continue;
			ld f=a[j][i];
			b[j]-=f*b[i];
			for(int k=i;k<=n;k++)
				a[j][k]-=f*a[i][k];
		}
	}

	if(ok){
		for(int i=1;i<=n;i++)
			printf("%.2Lf\n",b[i]);
	}else
		printf("No Solution\n");




	return 0;
}


