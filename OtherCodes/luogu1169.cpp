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

const int MaxN=2000+10;

int n,m;

int a[MaxN][MaxN];
int lreach[MaxN][MaxN],treach[MaxN][MaxN],rreach[MaxN][MaxN];
int sq[MaxN][MaxN],rqh[MaxN][MaxN];



int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(a[i][j]);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			lreach[i][j]=1;
			if(j>1&&a[i][j]!=a[i][j-1])
				lreach[i][j]=lreach[i][j-1]+1;
			treach[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--){
			rreach[i][j]=1;
			if(j<m&&a[i][j]!=a[i][j+1])
				rreach[i][j]=rreach[i][j+1]+1;
		}
	
	int sqans=1,rqans=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i>1&&a[i][j]!=a[i-1][j]){
				lreach[i][j]=min(lreach[i][j],lreach[i-1][j]);
				rreach[i][j]=min(rreach[i][j],rreach[i-1][j]);
				treach[i][j]=treach[i-1][j]+1;
			}
			int width=lreach[i][j]+rreach[i][j]-1;
			int height=treach[i][j];
			sqans=max(sqans,min(width,height)*min(width,height));
			rqans=max(rqans,width*height);
		}
	}

	printf("%d\n%d\n",sqans,rqans);
	
	return 0;
}


