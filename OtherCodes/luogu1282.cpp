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
do{printf( ":");											\
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

const int infinity=1e5+10;
const int MaxN=1000+10,MaxD=2*MaxN*6+10;
const int offset=MaxN*6+5;

int n;
int a[MaxN],b[MaxN];

int dp[MaxN][MaxD];

template<typename Int>
Int iabs(Int x){
	return x<0?-x:x;
}


int main(int argc, char* argv[]) {
	
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);read(b[i]);
	}
	
	for(int i=0;i<=n;i++)
		for(int j=0;j<MaxD;j++)
			dp[i][j]=infinity;
	dp[0][offset]=0;

	for(int i=0;i<n;i++)
		for(int j=0;j<MaxD;j++)
			if(dp[i][j]<infinity){
				dp[i+1][j+a[i+1]-b[i+1]]=min(dp[i+1][j+a[i+1]-b[i+1]],dp[i][j]);
				dp[i+1][j+b[i+1]-a[i+1]]=min(dp[i+1][j+b[i+1]-a[i+1]],dp[i][j]+1);
			}

#ifdef D
	printf("boot");
	for(int i=0;i<=n;i++)
		printf("\t%d",i);
	printf("\n");
	for(int i=-5;i<=5;i++){
		printf("%3d",i);
		for(int j=0;j<=n;j++)
			printf("\t%d",dp[j][i+offset]);
		printf("\n");
	}
#endif
	
	int anscnt=-1,ansdiff=infinity;
	for(int j=0;j<MaxD;j++){
		if(dp[n][j]>=infinity)
			continue;
		int diff=iabs(j-offset);
		if(diff<ansdiff){
			ansdiff=diff;
			anscnt=dp[n][j];
		}else if(diff==ansdiff)
			anscnt=min(anscnt,dp[n][j]);
	}

	PRINTARR("%d",(dp[n]+offset),-6,13);
	printf("%d\n",anscnt);
	
	return 0;
}


