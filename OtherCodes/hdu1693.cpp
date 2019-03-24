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

const int MaxN=13,MaxM=13;

int n,m;
int dp[MaxN][MaxM][1<<MaxN];
bool flag[MaxN][MaxM];





int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int a;
			read(a);
			flag[i][j]=(int)a;
		}

	dp[1][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			for(int s=0;s<=(1<<(n+1))-1;s++){
				int l=s&(1<<(j-1)),r=s&(1<<j);
				if(l&&r)
					dp[i][j+1][s^((1<<(j-1))|(1<<j))]+=dp[i][j][s];
				else if(!l&&r){
					dp[i][j+1][s^((1<<(j-1))|(1<<j))]+=dp[i][j][s];
					dp[i][j+1][s]+=dp[i][j][s];
				}else if(l&&!r){
					dp[i][j+1][s^((1<<(j-1))|(1<<j))]+=dp[i][j][s];
					dp[i][j+1][s]+=dp[i][j][s];
				}else
					dp[i][j+1][s^((1<<(j-1))|(1<<j))]+=dp[i][j][s];
			}
		for(int s=0;s<=(1<<(n+1))-1;s++)
			if(!(s&(1<<m)))
				dp[i+1][0][s<<1]=dp[i][m][s];
	}

	printf("%d\n",dp[n][m][0]);


	return 0;
}


